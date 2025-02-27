//
// Created by flo on 02.05.20.
//

/**
 * This cache stores the translated code blocks.
 * After the table is initialized, the RISC-V program address of the basic block is added to the cache,
 * together with the starting address of the function in memory that translates that block.
 * Calls will happen according to the sequence
 *  1. encounter a RISC-V address in execution
 *  2. check if program cache contains that address (via lookup_cache_entry())
 *      --> if UNSEEN_CODE: nullptr return indicates that this block is not present.
 *          3. translate the block and place the address returned by the translator.cpp's finalize_block()
 *             into the cache together with that blocks RISC-V address.
 *      --> else: we have seen this code before
 *          3. the cache returns a void* to the translated block in memory. cast that to a function pointer and
 *             call it in order to execute the cached function.
 */

#include <stddef.h>
#include "cache.h"
#include <env/flags.h>
#include <util/log.h>
#include <common.h>
#include <linux/mman.h>
#include <env/opt.h>
#include <env/exit.h>
#include <util/tools/profile.h>

#define INITIAL_SIZE 8192
#define SMALLTLB 0x20

///position where direct jump to next block can be inserted
volatile uint8_t *chain_end = NULL;
volatile uint32_t chain_type = 0;

//cache table
t_cache_entry *cache_table = NULL;
size_t table_size = INITIAL_SIZE;
size_t count_entries = 0;

// fast lookup
t_cache_entry *tlb;
// size of the tlb
size_t tlb_size = SMALLTLB;

/**
 * Initializes the hash table array.
 */
void init_hash_table(void) {
    log_cache("Initializing cache table for size %lu...\n", table_size);

    //allocate memory for our table (MAP_ANONYMOUS --> initialize to zero)
    cache_table = mmap(NULL, table_size * sizeof(t_cache_entry), PROT_READ | PROT_WRITE,
                       MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    //check for heap memory allocation fail
    if (BAD_ADDR(cache_table)) {
        dprintf(2, "Bad. Cache memory allocation failed.");
        panic(FAIL_HEAP_ALLOC);
    }

    tlb = mmap(NULL, tlb_size * sizeof(t_cache_entry), PROT_READ | PROT_WRITE,
               MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    //check for heap memory allocation fail
    if (tlb == NULL) {
        dprintf(2, "Bad. TLB memory allocation failed.");
        panic(FAIL_HEAP_ALLOC);
    }
}

inline size_t hash(t_risc_addr risc_addr) {
    return (risc_addr >> 2u) & (table_size - 1);
}

inline size_t smallhash(t_risc_addr risc_addr) {
    return (risc_addr >> 3u) & (SMALLTLB - 1);
}

/**
 * Find the hash table index for the passed address.
 * @param risc_addr RISC-V code address to lookup_cache_entry in hash table
 * @return table index for either the address in question or the next available field
 */
size_t find_lin_slot(t_risc_addr risc_addr) {
    size_t index = hash(risc_addr);

    //linearly probe for key or empty field
    while (cache_table[index].cache_loc != 0 && cache_table[index].risc_addr != risc_addr) {
        //cyclically increment to find available slots
        index = (index + 1) & (table_size - 1);
    }

    return index;
}

void set_tlb(t_risc_addr risc_addr, t_cache_loc cacheLoc) {
    size_t smallHash = smallhash(risc_addr);
    tlb[smallHash].risc_addr = risc_addr;
    tlb[smallHash].cache_loc = cacheLoc;
}

/**
 * Lookup the cache location of a given RISC-V instruction address.
 * @param risc_addr the RISC-V instruction address.
 * @return code cache address of that instruction, or NULL if nonexistent
 */
t_cache_loc lookup_cache_entry(t_risc_addr risc_addr) {
    if (flag_do_profile) profile_cache_access();

    size_t smallHash = smallhash(risc_addr);
    if (tlb[smallHash].risc_addr == risc_addr) {
        return tlb[smallHash].cache_loc;
    }
    size_t index = find_lin_slot(risc_addr);

    if (cache_table[index].cache_loc != 0) {
        //value is cached and exists
        set_tlb(risc_addr, cache_table[index].cache_loc);
        return cache_table[index].cache_loc;
    } else {
        //value does not exist
        return UNSEEN_CODE;
    }
}

void set_cache_entry(t_risc_addr risc_addr, t_cache_loc cache_loc) {
    size_t index = find_lin_slot(risc_addr);
    if (perfFd >= 0) {
        dprintf(perfFd, "%lx %lx src_0x%lx\n", (uintptr_t) cache_loc, 4096lu, risc_addr);
    }
    //reallocate if we have filled more than half of the available space
    if (count_entries >= table_size >> 1) {
        //double the table size
        table_size <<= 1u;
        log_cache("Doubling table size to %lu and reallocating...\n", table_size);

        //allocate new heap space for the cache table and copy over the values we have saved
        t_cache_entry *copy_buf = mmap(NULL, table_size * sizeof(t_cache_entry), PROT_READ | PROT_WRITE,
                                       MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

        //check heap allocation
        if (BAD_ADDR(copy_buf)) {
            dprintf(2, "Bad. Memory allocation failed.\n");
            panic(FAIL_HEAP_ALLOC);
        }

        //set cache table to new buffer in order to use the existing methods for insertion
        t_cache_entry *old_table = cache_table;
        cache_table = copy_buf;

        count_entries = 0;

        bool oldLogCache = flag_log_cache;
        flag_log_cache = false;
        //rehash all the old values
        for (size_t i = 0; i < table_size >> 1u; i++) {
            if (old_table[i].cache_loc != 0) {
                //rehash this new value
                //this will fill the tlb with undefined hits
                set_cache_entry(old_table[i].risc_addr, old_table[i].cache_loc);
            }
        }

        flag_log_cache = oldLogCache;
        print_values();

        //free and reset originally allocated space
        munmap(old_table, (table_size >> 1u) * sizeof(t_cache_entry));

        //find index again
        index = find_lin_slot(risc_addr);
    }

    //if we already have a value there, update it
    if (cache_table[index].cache_loc != 0) {
        //update value in table
        cache_table[index].cache_loc = cache_loc;
        set_tlb(risc_addr, cache_loc);
        return;
    }

    //insert value into the table if we have not seen it before
    cache_table[index].cache_loc = cache_loc;
    cache_table[index].risc_addr = risc_addr;
    count_entries++;

    set_tlb(risc_addr, cache_loc);

    //print entries
    if (flag_log_cache) {
        print_values();
    }
}

/**
 * Print out the hash table contents.
 */
void print_values(void) {
    if (!flag_log_cache) return;
    log_cache("Cache updated.\n");
    if (flag_log_cache_contents) {
        log_cache("New contents.\n");
    }
    size_t blocks = 0;
    for (size_t i = 0; i < table_size; ++i) { //potentially better way to do this?
        if (cache_table[i].cache_loc != 0) {
            blocks++;
            if (flag_log_cache_contents) {
                log_cache("cache[%lu]: block address %p at cache loc %p\n", i, (void *) cache_table[i].risc_addr,
                          cache_table[i].cache_loc);
            }
        }
    }
    log_cache("Now contains %lu block(s).\n", blocks);
}

size_t get_cache_entry_count(void) {
    return count_entries;
}
