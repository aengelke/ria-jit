//
// Created by flo on 21.05.20.
//

#include "translate_other.h"
#include <runtime/emulateEcall.h>

/**
* Translate the FENCE instruction.
* Description
* @param instr the RISC-V instruction to translate
* @param r_info the runtime register mapping (RISC-V -> x86)
*/
void translate_FENCE(const t_risc_instr *instr, const register_info *r_info) {
    log_general("Ignored FENCE...\n"); //just ignore for now
}

/**
* Translate the ECALL instruction.
* Makes a system call to the execution environment.
* @param instr the RISC-V instruction to translate
* @param r_info the runtime register mapping (RISC-V -> x86)
*/
void translate_ECALL(const t_risc_instr *instr, const register_info *r_info, const context_info *c_info) {
    //see https://stackoverflow.com/questions/59800430/risc-v-ecall-syscall-calling-convention-on-pk-linux
    log_asm_out("Translate ECALL...\n");

    invalidateAllReplacements(r_info);
    //emit c_info->save_context();
    err |= fe_enc64(&current, FE_CALL, (intptr_t) c_info->save_context);
    //emit emulate_ecall(instr->addr, r_info->base);
    err |= fe_enc64(&current, FE_MOV64ri, FE_DI, instr->addr);
    err |= fe_enc64(&current, FE_MOV64ri, FE_SI, r_info->base);
    typedef void emulate(t_risc_addr addr, t_risc_reg_val *registerValues);
    emulate *em = &emulate_ecall;
    err |= fe_enc64(&current, FE_CALL, (uintptr_t) em);
    //emit c_info->load_execute_save_context(*, false); //* means value does not matter, false means load without execute
    err |= fe_enc64(&current, FE_XOR32rr, FE_SI, FE_SI);
    err |= fe_enc64(&current, FE_CALL, (intptr_t) c_info->load_execute_save_context);
}

/**
* Translate the EBREAK instruction.
* Description
* @param instr the RISC-V instruction to translate
* @param r_info the runtime register mapping (RISC-V -> x86)
*/
void translate_EBREAK(const t_risc_instr *instr, const register_info *r_info) {
    critical_not_yet_implemented("Invalid EBREAK translation call");
}

/**
* Translate the FENCE_I instruction.
* Description
* @param instr the RISC-V instruction to translate
* @param r_info the runtime register mapping (RISC-V -> x86)
*/
void translate_FENCE_I(const t_risc_instr *instr, const register_info *r_info) {
    critical_not_yet_implemented("Invalid FENCE_I translation call");
}
