//
// Created by jhne on 10/3/20.
//

#include <gen/instr/patterns.h>
#include <gen/translate.h>
#include <util/typedefs.h>
#include <util/util.h>


/**
 * how to create a pattern:
 *
 * ----1: elements:-----
 * Element fields:
 *  mnem : mnem
 *  rs1, rs2, rd :
 *      rs1_h1 means, that rs1 of the instruction
 *      has to be the same as in the instruction at
 *      the position stored in h1. (block_cache[pattern_start + h1]).
 *      rs2, rd work the same. all are also available with h2.
 *
 *      Example:
 *      pattern_element jsjfbefjb[] = {
 *          {.....},
 *          {.....},
 *          {ADDI, rd_h1, DONT_CARE, rs1_h2, 1, 0, 1, 32}
 *      };
 *
 *      In this example, rs1 of the 3rd instruction has to be
 *      the same register as rd of the second instruction,
 *      and rd has to be the same register as rs1 of the first instruction.
 *      The immediate has to be 32.
 *
 *      NOTE: not all options are implemented for every field yet
 *            (to avoid unnecessary comparisons in matcher).
 *            Do so in the switch-case under the corresponding comments (e.g. "rs1 match") in optimize.c
 *
 *  h1, h2 : helper variables
 *
 *  imm :
 *      0 = dont care ;
 *      1 = value has to be equal to imm_value ;
 *      2 = value has to be equal to immediate of (block_cache[pattern_start + h1])
 *
 * ----2: emitter function:-----
 * Emits the x86 equivalent of the pattern.
 *
 * ----3: entry in patterns[]:-----
 *
 * */


const pattern_element p_0_elem[] = {
        {LUI,  DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 0, 0},
        {LD,   rd_h1,     DONT_CARE, DONT_CARE, 0, 0, 0, 0},
        {ADDI, rd_h1,     DONT_CARE, rd_h1,     1, 0, 0, 0},
        {SD,   rd_h2,     rd_h1,     DONT_CARE, 1, 0, 2, 1}
};

const pattern_element p_1_elem[] = {
        {LUI,   DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 0, 0},
        {LW,    rd_h1,     DONT_CARE, DONT_CARE, 0, 0, 0, 0},
        {ADDIW, rd_h1,     DONT_CARE, rd_h1,     1, 0, 0, 0},
        {SW,    rd_h2,     rd_h1,     DONT_CARE, 1, 0, 2, 1}
};

const pattern_element p_2_elem[] = {
        {AUIPC, DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 0, 0},
        {ADDI,  rd_h1,     DONT_CARE, DONT_CARE, 0, 0, 0, 0},
        {LW,    rd_h1,     DONT_CARE, DONT_CARE, 1, 0, 0, 0},
        {ADDIW, rd_h1,     DONT_CARE, DONT_CARE, 2, 0, 0, 0},
        {SW,    rd_h1,     rd_h2,     DONT_CARE, 0, 3, 2, 2}
};

const pattern_element p_3_elem[] = {
        {AUIPC, DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 0, 0},
        {ADDI,  rd_h1,     DONT_CARE, rd_h1,     0, 0, 0, 0}
};

const pattern_element p_4_elem[] = {
        {AUIPC, DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 0, 0},
        {LW,    rd_h1,     DONT_CARE, rd_h1,     0, 0, 0, 0}
};

const pattern_element p_5_elem[] = {
        {AUIPC, DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 0, 0},
        {LD,    rd_h1,     DONT_CARE, rd_h1,     0, 0, 0, 0}
};

const pattern_element p_6_elem[] = {
        {SLLI, DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 1, 32},    //rd == rs1???
        {SRLI, rd_h1,     DONT_CARE, rd_h1,     0, 0, 1, 32}
};

const pattern_element p_7_elem[] = {
        {ADDIW, DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 0, 0},
        {SLLI,  rd_h1,     DONT_CARE, rd_h1,     0, 0, 1, 32},
        {SRLI,  rd_h1,     DONT_CARE, rd_h1,     0, 0, 1, 32}
};

const pattern_element p_8_elem[] = {
        {ADDIW, DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 1, 0}
};

const pattern_element p_9_elem[] = {
        {LUI,  DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 0, 0},
        {ADDI, rd_h1,     DONT_CARE, not_rd_h1, 0, 0, 1, 0},
        {SLLI, not_rd_h1, DONT_CARE, rd_h2,     1, 0, 1, 32},
        {SRLI, rd_h1,     DONT_CARE, rd_h1,     2, 0, 1, 32}
};

const pattern_element p_10_elem[] = {
        {ADDI, x0, DONT_CARE, x0, 0, 0, 1, 0}
};

const pattern_element p_11_elem[] = {
        {ADDI, DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 1, 0}
};

const pattern_element p_12_elem[] = {
        {XORI, DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 1, -1}
};

const pattern_element p_13_elem[] = {
        {SUB, x0, DONT_CARE, DONT_CARE, 0, 0, 0, 0}
};

const pattern_element p_14_elem[] = {
        {SUBW, x0, DONT_CARE, DONT_CARE, 0, 0, 0, 0}
};

const pattern_element p_15_elem[] = {
        {SLTIU, DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 1, 1}
};

const pattern_element p_16_elem[] = {
        {SLTU, x0, DONT_CARE, DONT_CARE, 0, 0, 0, 0}
};

const pattern_element p_17_elem[] = {
        {SLT, DONT_CARE, x0, DONT_CARE, 0, 0, 0, 0}
};

const pattern_element p_18_elem[] = {
        {SLT, x0, DONT_CARE, DONT_CARE, 0, 0, 0, 0}
};

const pattern_element p_19_elem[] = {
        {LUI,  DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 0, 0},
        {ADDI, rd_h1,     DONT_CARE, rd_h1,     0, 0, 0, 0}
};

const pattern_element p_20_elem[] = {
        {ADDI, x0, DONT_CARE, DONT_CARE, 0, 0, 0, 0}
};

const pattern_element p_21_elem[] = {
        {SLLI, DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 1, 32},
        {SRLI, rd_h1,     DONT_CARE, rd_h1,     0, 0, 0, 0}
};

const pattern_element p_22_elem[] = {
        {ANDI, DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 1, 0xff}
};

const pattern_element p_23_elem[] = {
        {ADDIW, DONT_CARE, DONT_CARE, DONT_CARE, 0, 0, 0, 0},
        {ANDI,  rd_h1,     DONT_CARE, rd_h1,     0, 0, 1, 0xff}
};

/* unused */
void emit_pattern_0(const t_risc_instr *instr, const register_info *r_info) {
    log_asm_out("emit pattern 0: inc mem64 at 0x%lx\n", instr->addr);
    invalidateAllReplacements(r_info);

    //potantially check if address fits into 32bit and use non RIP-relative absolute
    err |= fe_enc64(&current, FE_MOV64ri, FE_AX, (instr->addr + instr->imm));
    err |= fe_enc64(&current, FE_ADD64mi, FE_MEM(FE_AX, 0, 0, 0), instr[2].imm);
}

void emit_pattern_2(const t_risc_instr instrs[static 5], const register_info *r_info) {
    log_asm_out("emit pattern 2: inc m64 at 0x%lx\n", instrs[0].addr);
    invalidateAllReplacements(r_info);

    t_risc_addr addr = instrs[0].addr + instrs[0].imm + instrs[1].imm + instrs[2].imm;
    if ((int64_t) addr == (int32_t) addr) {
        err |= fe_enc64(&current, FE_ADD32mi, FE_MEM(0, 0, 0, addr), instrs[3].imm);
    } else {
        err |= fe_enc64(&current, FE_MOV64ri, FE_AX, addr);
        err |= fe_enc64(&current, FE_ADD32mi, FE_MEM(FE_AX, 0, 0, 0), instrs[3].imm);
    }
}

void emit_pattern_3(const t_risc_instr instrs[static 2], const register_info *r_info) {
    log_asm_out("emit pattern 3: AUIPC + ADDI at 0x%lx\n", instrs[0].addr);
    //invalidateAllReplacements(r_info);

    if (instrs[1].reg_dest == x0) {
        log_asm_out("pattern 3: addi x0 at %p\n", (void *) current);
        return;
    }

    t_risc_addr value = instrs[0].addr + instrs[0].imm + instrs[1].imm;

    FeReg regDest = getRd(&instrs[1], r_info);
    err |= fe_enc64(&current, FE_MOV64ri, regDest, value);

    /*
    if (r_info->mapped[instrs[1].reg_dest]) {
        err |= fe_enc64(&current, FE_MOV64ri, r_info->map[instrs[0].reg_dest], value);
    } else {
        if ((int64_t) value == (int32_t) value) {
            err |= fe_enc64(&current, FE_MOV64mi, FE_MEM_ADDR(r_info->base + 8 * instrs[1].reg_dest), value);
        } else {
            err |= fe_enc64(&current, FE_MOV64ri, FE_AX, value);
            err |= fe_enc64(&current, FE_MOV64mr, FE_MEM_ADDR(r_info->base + 8 * instrs[1].reg_dest), FE_AX);
        }
    }
     */
}

void emit_pattern_4(const t_risc_instr instrs[static 2], const register_info *r_info) {
    log_asm_out("emit pattern 4: AUIPC + LW at 0x%lx\n", instrs[0].addr);
    //invalidateAllReplacements(r_info);

    t_risc_addr addr = instrs[0].addr + instrs[0].imm + instrs[1].imm;
    if (r_info->gp_mapped[instrs[1].reg_dest]) {
        if ((int64_t) addr == (int32_t) addr) {
            err |= fe_enc64(&current, FE_MOVSXr64m32, r_info->gp_map[instrs[1].reg_dest], FE_MEM(0, 0, 0, addr));
        } else {
            invalidateReplacement(r_info, FE_AX, true);
            err |= fe_enc64(&current, FE_MOV64ri, FE_AX, addr);
            err |= fe_enc64(&current, FE_MOVSXr64m32, r_info->gp_map[instrs[1].reg_dest], FE_MEM(FE_AX, 0, 0, 0));
        }
    } else {

        FeReg regDest = getRd(&instrs[1], r_info);

        if ((int64_t) addr == (int32_t) addr) {
            err |= fe_enc64(&current, FE_MOVSXr64m32, regDest, FE_MEM(0, 0, 0, addr));
        } else {
            if(regDest != FE_AX) {
                invalidateReplacement(r_info, FE_AX, true);
                err |= fe_enc64(&current, FE_MOV64ri, FE_AX, addr);
                err |= fe_enc64(&current, FE_MOVSXr64m32, regDest, FE_MEM(FE_AX, 0, 0, 0));
            } else {
                invalidateReplacement(r_info, FE_CX, true);
                err |= fe_enc64(&current, FE_MOV64ri, FE_CX, addr);
                err |= fe_enc64(&current, FE_MOVSXr64m32, regDest, FE_MEM(FE_CX, 0, 0, 0));
            }
        }

        /*
        if ((int64_t) addr == (int32_t) addr) {
            err |= fe_enc64(&current, FE_MOVSXr64m32, FE_AX, FE_MEM(0, 0, 0, addr));
        } else {
            err |= fe_enc64(&current, FE_MOV64ri, FE_AX, addr);
            err |= fe_enc64(&current, FE_MOVSXr64m32, FE_AX, FE_MEM(FE_AX, 0, 0, 0));
        }
        err |= fe_enc64(&current, FE_MOV64mr, FE_MEM_ADDR(r_info->base + 8 * instrs[1].reg_dest), FE_AX);
         */
    }
}

void emit_pattern_5(const t_risc_instr instrs[static 2], const register_info *r_info) {
    log_asm_out("emit pattern 5: AUIPC + LD at 0x%lx\n", instrs[0].addr);
    //invalidateAllReplacements(r_info);

    t_risc_addr addr = instrs[0].addr + instrs[0].imm + instrs[1].imm;
    if (r_info->gp_mapped[instrs[1].reg_dest]) {
        if ((int64_t) addr == (int32_t) addr) {
            err |= fe_enc64(&current, FE_MOV64rm, r_info->gp_map[instrs[1].reg_dest], FE_MEM(0, 0, 0, addr));
        } else {
            invalidateReplacement(r_info, FE_AX, true);
            err |= fe_enc64(&current, FE_MOV64ri, FE_AX, addr);
            err |= fe_enc64(&current, FE_MOV64rm, r_info->gp_map[instrs[1].reg_dest], FE_MEM(FE_AX, 0, 0, 0));
        }
    } else {
        FeReg regDest = getRd(&instrs[1], r_info);
        if ((int64_t) addr == (int32_t) addr) {
            err |= fe_enc64(&current, FE_MOV64rm, regDest, FE_MEM(0, 0, 0, addr));
        } else {
            if(regDest != FE_AX) {
                invalidateReplacement(r_info, FE_AX, true);
                err |= fe_enc64(&current, FE_MOV64ri, FE_AX, addr);
                err |= fe_enc64(&current, FE_MOV64rm, regDest, FE_MEM(FE_AX, 0, 0, 0));
            } else {
                invalidateReplacement(r_info, FE_CX, true);
                err |= fe_enc64(&current, FE_MOV64ri, FE_CX, addr);
                err |= fe_enc64(&current, FE_MOV64rm, regDest, FE_MEM(FE_CX, 0, 0, 0));
            }
        }

        /*
        if ((int64_t) addr == (int32_t) addr) {
            err |= fe_enc64(&current, FE_MOV64rm, FE_AX, FE_MEM(0, 0, 0, addr));
        } else {
            err |= fe_enc64(&current, FE_MOV64ri, FE_AX, addr);
            err |= fe_enc64(&current, FE_MOV64rm, FE_AX, FE_MEM(FE_AX, 0, 0, 0));
        }
        err |= fe_enc64(&current, FE_MOV64mr, FE_MEM_ADDR(r_info->base + 8 * instrs[1].reg_dest), FE_AX);
         */
    }
}

void emit_pattern_6(const t_risc_instr instrs[static 2], const register_info *r_info) {
    log_asm_out("emit pattern 6: SLLI +  SRLI at 0x%lx\n", instrs[0].addr);
    //invalidateAllReplacements(r_info);

    if (r_info->gp_mapped[instrs[0].reg_src_1]) {
        if (r_info->gp_mapped[instrs[1].reg_dest]) {
            //sets high 32 to zero
            err |= fe_enc64(&current, FE_MOV32rr, r_info->gp_map[instrs[1].reg_dest], r_info->gp_map[instrs[0].reg_src_1]);
        } else {
            FeReg reg_dest = getRd(&instrs[1], r_info);
            err |= fe_enc64(&current, FE_MOV32rr, reg_dest, r_info->gp_map[instrs[0].reg_src_1]);

            /*
            err |= fe_enc64(&current, FE_MOV64mi, FE_MEM_ADDR(r_info->base + 8 * instrs[1].reg_dest), 0);

            err |= fe_enc64(&current, FE_MOV32mr, FE_MEM_ADDR(r_info->base + 8 * instrs[1].reg_dest),
                            r_info->map[instrs[0].reg_src_1]);
            */
        }
    } else if (r_info->gp_mapped[instrs[1].reg_dest]) {
        FeReg reg_src1 = getRs1(&instrs[0], r_info);
        err |= fe_enc64(&current, FE_MOV32rr, r_info->gp_map[instrs[1].reg_dest], reg_src1);

        /*
        err |= fe_enc64(&current, FE_MOV32rm, r_info->map[instrs[1].reg_dest],
                        FE_MEM_ADDR(r_info->base + 8 * instrs[0].reg_src_1));  //sets high 32 to zero
        */
    } else {
        //sets high 32 to zero
        FeReg regSrc1 = getRs1(&instrs[0], r_info);
        FeReg regDest = getRd(&instrs[1], r_info);
        err |= fe_enc64(&current, FE_MOV32rr, regDest, regSrc1);  //sets high 32 to zero

        /*
        err |= fe_enc64(&current, FE_MOV32rm, FE_AX, FE_MEM_ADDR(r_info->base + 8 * instrs[0].reg_src_1));
        err |= fe_enc64(&current, FE_MOV64mr, FE_MEM_ADDR(r_info->base + 8 * instrs[1].reg_dest), FE_AX);
        */
     }
}

void emit_pattern_7(const t_risc_instr instr[static 3], const register_info *r_info) {
    log_asm_out("emit pattern 7: ADDIW + SLLI + SRLI at 0x%lx\n", instr[0].addr);

    FeReg regSrc1 = getRs1(instr, r_info);
    FeReg regDest = getRd(instr, r_info);

    if (regSrc1 != regDest) {
        err |= fe_enc64(&current, FE_MOV32rr, regDest, regSrc1);
    }

    err |= fe_enc64(&current, FE_ADD32ri, regDest, instr[0].imm);
}

/**
 * Translate the SEXTW instruction.
 * Description
 * @param instr the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_8_SEXTW(const t_risc_instr *instr, const register_info *r_info) {
    log_asm_out("emit pattern 8: ADDIW 32b sign extension at 0x%lx\n", instr[0].addr);
    invalidateAllReplacements(r_info);

    if (r_info->gp_mapped[instr->reg_src_1]) {
        if (r_info->gp_mapped[instr->reg_dest]) {
            err |= fe_enc64(&current, FE_MOVSXr64r32, r_info->gp_map[instr->reg_dest], r_info->gp_map[instr->reg_src_1]);
        } else {
            err |= fe_enc64(&current, FE_MOVSXr64r32, FE_AX, r_info->gp_map[instr->reg_src_1]);
            err |= fe_enc64(&current, FE_MOV64mr, FE_MEM_ADDR(r_info->base + 8 * instr->reg_dest), FE_AX);
        }
    } else {
        if (r_info->gp_mapped[instr->reg_dest]) {
            err |= fe_enc64(&current, FE_MOVSXr64m32, r_info->gp_map[instr->reg_dest],
                            FE_MEM_ADDR(r_info->base + 8 * instr->reg_src_1));
        } else {
            err |= fe_enc64(&current, FE_MOVSXr64m32, FE_AX, FE_MEM_ADDR(r_info->base + 8 * instr->reg_src_1));
            err |= fe_enc64(&current, FE_MOV64mr, FE_MEM_ADDR(r_info->base + 8 * instr->reg_dest), FE_AX);
        }
    }
}

void emit_pattern_9(const t_risc_instr instrs[static 4], const register_info *r_info) {
    log_asm_out("emit pattern 9: LUI + ADDIW + SLLI + SRLI at 0x%lx\n", instrs[0].addr);

    FeReg regDest = getRd(&instrs[0], r_info);
    err |= fe_enc64(&current, FE_MOV64ri, regDest, instrs[0].imm);

    //err |= fe_enc64(&current, FE_MOV64mi, FE_MEM_ADDR(r_info->base + 8 * instrs[1].reg_dest), instrs[0].imm);

    emit_pattern_6(&instrs[2], r_info);
}

/**
 * Translate the NOP instruction.
 * Description
 * @param instr the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_10_NOP(const t_risc_instr *instr, const register_info *r_info) {
    log_asm_out("emit pattern 10: ADDI as NOP at 0x%lx\n", instr->addr);
    err |= fe_enc64(&current, FE_NOP);
}

/**
 * Translate the MV instruction.
 * Description
 * @param instr the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_11_MV(const t_risc_instr *instr, const register_info *r_info) {
    log_asm_out("emit pattern 11: ADDI as MV at 0x%lx\n", instr->addr);

    FeReg regSrc1 = 0;

    if (instr->reg_src_1 != 0) {
        regSrc1 = getRs1(instr, r_info);
    }

    FeReg regDest = getRd(instr, r_info);

    if(instr->reg_src_1 == 0) {
        err |= fe_enc64(&current, FE_XOR32rr, regDest, regDest);
    } else if(regDest != regSrc1) {
        err |= fe_enc64(&current, FE_MOV64rr, regDest, regSrc1);
    }
}

/**
 * Translate the NOT instruction.
 * Description
 * @param instr the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_12_NOT(const t_risc_instr *instr, const register_info *r_info) {
    log_asm_out("emit pattern 12: XORI as NOT at 0x%lx\n", instr->addr);

    FeReg regSrc1 = getRs1(instr, r_info);
    FeReg regDest = getRd(instr, r_info);

    if (regDest != regSrc1) {
        err |= fe_enc64(&current, FE_MOV64rr, regDest, regSrc1);
    }
    err |= fe_enc64(&current, FE_NOT64r, regDest);
}

/**
 * Translate the NEG instruction.
 * Description
 * @param instr the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_13_NEG(const t_risc_instr *instr, const register_info *r_info) {
    log_asm_out("emit pattern 13: SUB as NEG at 0x%lx\n", instr->addr);

    FeReg regSrc2 = getRs2(instr, r_info);
    FeReg regDest = getRd(instr, r_info);

    if (regDest != regSrc2) {
        err |= fe_enc64(&current, FE_MOV64rr, regDest, regSrc2);
    }
    err |= fe_enc64(&current, FE_NEG64r, regDest);
}

/**
 * Translate the NEGW instruction.
 * Description
 * @param instr the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_14_NEGW(const t_risc_instr *instr, const register_info *r_info) {
    log_asm_out("emit pattern 14: SUBW as NEGW at 0x%lx\n", instr->addr);

    FeReg regSrc2 = getRs2(instr, r_info);
    FeReg regDest = getRd(instr, r_info);

    if (regDest != regSrc2) {
        err |= fe_enc64(&current, FE_MOV32rr, regDest, regSrc2);
    }
    err |= fe_enc64(&current, FE_NEG32r, regDest);
    err |= fe_enc64(&current, FE_MOVSXr64r32, regDest, regDest);
}

/**
 * Translate the SEQZ instruction.
 * Description
 * @param instr the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_15_SEQZ(const t_risc_instr *instr, const register_info *r_info) {
    log_asm_out("emit pattern 15: SLTIU as SEQZ at 0x%lx\n", instr->addr);

    FeReg regSrc1 = getRs1(instr, r_info);
    FeReg regDest = getRd(instr, r_info);

    err |= fe_enc64(&current, FE_TEST64rr, regSrc1, regSrc1);
    err |= fe_enc64(&current, FE_SETZ8r, regDest);
    //Implicit zero extension to 64bit
    err |= fe_enc64(&current, FE_MOVZXr32r8, regDest, regDest);
}

/**
 * Translate the SNEZ instruction.
 * Description
 * @param instr the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_16_SNEZ(const t_risc_instr *instr, const register_info *r_info) {
    log_asm_out("emit pattern 16: SLTU as SNEZ at 0x%lx\n", instr->addr);

    FeReg regSrc2 = getRs2(instr, r_info);
    FeReg regDest = getRd(instr, r_info);

    err |= fe_enc64(&current, FE_TEST64rr, regSrc2, regSrc2);
    err |= fe_enc64(&current, FE_SETNZ8r, regDest);
    //Implicit zero extension to 64bit
    err |= fe_enc64(&current, FE_MOVZXr32r8, regDest, regDest);
}

/**
 * Translate the SLTZ instruction.
 * Description
 * @param instr the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_17_SLTZ(const t_risc_instr *instr, const register_info *r_info) {
    log_asm_out("emit pattern 17: SLT as SLTZ at 0x%lx\n", instr->addr);

    FeReg regSrc1 = getRs1(instr, r_info);
    FeReg regDest = getRd(instr, r_info);

    if (regSrc1 != regDest) {
        err |= fe_enc64(&current, FE_MOV64rr, regDest, regSrc1);
    }
    err |= fe_enc64(&current, FE_SHR64ri, 63);
}

/**
 * Translate the SGTZ instruction.
 * Description
 * @param instr the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_18_SGTZ(const t_risc_instr *instr, const register_info *r_info) {
    log_asm_out("emit pattern 18: SLT as SGTZ at 0x%lx\n", instr->addr);

    FeReg regSrc2 = getRs2(instr, r_info);
    FeReg regDest = getRd(instr, r_info);

    err |= fe_enc64(&current, FE_TEST64rr, regSrc2, regSrc2);
    err |= fe_enc64(&current, FE_SETG8r, regDest);
    //Implicit zero extension to 64bit
    err |= fe_enc64(&current, FE_MOVZXr32r8, regDest, regDest);
}

/**
 * Translate the LI instruction.
 * Loads the value in the immediate field into the destination register.
 * @param instrs the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_19_LI(const t_risc_instr instrs[static 2], const register_info *r_info) {
    log_asm_out("emit pattern 19: LUI ADDI as LI at 0x%lx\n", instrs[0].addr);

    FeReg regDest = getRd(instrs, r_info);

    err |= fe_enc64(&current, FE_MOV64ri, regDest, instrs[0].imm + instrs[1].imm);
}

/**
 * Translate an ADDI with rs1 == x0.
 * Loads the value in the immediate field into the destination register.
 * @param instr the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_20_small_LI(const t_risc_instr *instr, const register_info *r_info) {
    log_asm_out("emit pattern 20: ADDI as small LI at 0x%lx\n", instr->addr);

    FeReg regDest = getRd(instr, r_info);

    err |= fe_enc64(&current, FE_MOV64ri, regDest, instr->imm);
}

/**
 * Translate a zero-extension followed by a multiplication.
 * @param instrs the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_21(const t_risc_instr instrs[static 2], const register_info *r_info) {
    log_asm_out("emit pattern 21: SLLI + SRLI used as zero-extend multiplication at 0x%lx\n", instrs[0].addr);

    FeReg regSrc1 = getRs1(&instrs[0], r_info);
    FeReg regDest = getRd(&instrs[0], r_info);

    //zero-extend and/or move the value
    err |= fe_enc64(&current, FE_MOV32rr, regDest, regSrc1);

    if (instrs[1].imm < 32) {
        err |= fe_enc64(&current, FE_SHL64ri, regDest, 32 - instrs[1].imm);
    } else {
        err |= fe_enc64(&current, FE_SHR32ri, regDest, instrs[1].imm - 32);
    }
}

/**
 * Translate a zero-extension from 8-bit to 64-bit.
 * @param instr the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_22(const t_risc_instr *instr, const register_info *r_info) {
    log_asm_out("emit pattern 22: ANDI zero-extension at 0x%lx\n", instr->addr);

    FeReg regSrc1 = getRs1(instr, r_info);
    FeReg regDest = getRd(instr, r_info);

    //zero-extending to 32-bit implicitly zeroes the upper 32 bits of the 64-bit register
    err |= fe_enc64(&current, FE_MOVZXr32r8, regDest, regSrc1);
}

/**
 * Translate zero extended 8bit immediate add.
 * @param instrs the RISC-V instruction to translate
 * @param r_info the runtime register mapping (RISC-V -> x86)
 */
void emit_pattern_23(const t_risc_instr instrs[static 2], const register_info *r_info) {
    log_asm_out("emit pattern 20: ADDIW ANDI 0xff as ZX 8B add imm at 0x%lx\n", instrs[0].addr);
    FeReg regSrc1 = getRs1(instrs, r_info);
    FeReg regDest = getRd(instrs, r_info);

    //32 bit instructions should be most efficient and do the same
    if (regSrc1 != regDest) {
        err |= fe_enc64(&current, FE_LEA32rm, regDest, FE_MEM(regSrc1, 0, 0, instrs[0].imm));
    } else {
        err |= fe_enc64(&current, FE_ADD32ri, regDest, instrs[0].imm);
    }
    //zero-extending to 32-bit implicitly zeroes the upper 32 bits of the 64-bit register
    err |= fe_enc64(&current, FE_MOVZXr32r8, regDest, regDest);
}


//order = length, descending
//order is important because longer patterns can contain shorter ones,
//and would never match if the shorter pattern would be tested before the longer one
//(and if the shorter pattern is contained at the beginning).
const pattern patterns[] = {
        {p_2_elem,  5, &emit_pattern_2},  //inc mem64
        {p_9_elem,  4, &emit_pattern_9},  //LUI + ADDI + SRLI + SLLI
        {p_7_elem,  3, &emit_pattern_7},  //ADDIW + SLLI + SRLI
        {p_3_elem,  2, &emit_pattern_3},  //AUIPC + ADDI
        {p_4_elem,  2, &emit_pattern_4},  //AUIPC + LW
        {p_5_elem,  2, &emit_pattern_5},  //AUIPC + LD
        {p_6_elem,  2, &emit_pattern_6},  //SLLI + SRLI
        {p_21_elem, 2, &emit_pattern_21}, //zero-extend, then multiply
        {p_19_elem, 2, &emit_pattern_19_LI}, //LUI + ADDI
        {p_23_elem, 2, &emit_pattern_23},  //ADDIW + ANDI 0xff
        {p_11_elem, 1, &emit_pattern_11_MV}, //ADDI MV
        {p_20_elem, 1, &emit_pattern_20_small_LI}, //ADDI small LI
        {p_8_elem,  1, &emit_pattern_8_SEXTW},  //ADDIW SX only
        {p_22_elem, 1, &emit_pattern_22}, //ANDI zero-extend 0xff
        {p_10_elem, 1, &emit_pattern_10_NOP}, //ADDI NOP
        {p_12_elem, 1, &emit_pattern_12_NOT}, //XORI NOT
        {p_13_elem, 1, &emit_pattern_13_NEG}, //SUB NEG
        {p_14_elem, 1, &emit_pattern_14_NEGW}, //SUBW NEGW
        {p_15_elem, 1, &emit_pattern_15_SEQZ}, //SLTIU SEQZ
        {p_16_elem, 1, &emit_pattern_16_SNEZ}, //SLTU SNEZ
        {p_17_elem, 1, &emit_pattern_17_SLTZ}, //SLT SLTZ gcc seems to emit slti rd, rs, 0 instead
        {p_18_elem, 1, &emit_pattern_18_SGTZ}, //SLT SGTZ


        {0,         0, 0},      //stopper

        //unused
        {p_0_elem,  4, &emit_pattern_0},
        {p_1_elem,  4, &emit_pattern_0},
        {0}
};
