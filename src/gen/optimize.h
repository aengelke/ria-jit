//
// Created by Flo Schmidt on 12.09.20.
//

#ifndef DYNAMICBINARYTRANSLATORRISCV64_X86_64_OPTIMIZE_H
#define DYNAMICBINARYTRANSLATORRISCV64_X86_64_OPTIMIZE_H

#include <util/typedefs.h>
#include <main/context.h>

void optimize_patterns(t_risc_instr *block_cache, int len);

void translate_pattern_emit(t_risc_instr *instr, const register_info *r_info);

typedef enum {
    DONT_CARE = 33,

    // -> same as rs[x] at pattern position h1
    rs1_h1,
    rs2_h1,
    rd_h1,
    rs1_h2,
    rs2_h2,
    rd_h2,
    not_rd_h1,
} t_risc_reg_meta;

typedef struct {
    unsigned short mnem;
    unsigned short rs1;
    unsigned short rs2;
    unsigned short rd;
    unsigned int h1;
    unsigned int h2;
    unsigned short imm;
    int imm_value;  //0: DONT_CARE  1: imm_value  2: imm patt. pos imm_value

} pattern_element;

typedef struct {
    const pattern_element * const elements;
    int len;
    //equivalent x86 code ...
    void (* emitter)(const t_risc_instr *, const register_info *);
} pattern;

#endif //DYNAMICBINARYTRANSLATORRISCV64_X86_64_OPTIMIZE_H
