//
// Created by flo on 10.05.20.
//

#ifndef DYNAMICBINARYTRANSLATORRISCV64_X86_64_REGISTER_H
#define DYNAMICBINARYTRANSLATORRISCV64_X86_64_REGISTER_H

#include <util/log.h>
#include <util/typedefs.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Global for saving if the static mapped float registers have been loaded
 */
extern uint8_t floatRegsLoaded;

t_risc_reg_val *get_gp_reg_file(void);

t_risc_reg_val *get_csr_reg_file(void);

t_risc_reg_val *get_fp_reg_file(void);

uint64_t *get_swap_file(void);

uint32_t *get_fctrl_file(void);

t_risc_reg_val get_value(t_risc_reg reg);

t_risc_fp_reg_val get_fpvalue(t_risc_reg reg);

void set_value(t_risc_reg reg, t_risc_reg_val val);

void set_fpvalue(t_risc_reg reg, t_risc_fp_reg_val val);

void dump_gp_registers(void);

#ifdef __cplusplus
}
#endif

#endif //DYNAMICBINARYTRANSLATORRISCV64_X86_64_REGISTER_H
