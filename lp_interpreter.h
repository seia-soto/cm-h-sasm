//
// Created by 고호정 on 2021/06/15.
//

#include "stdbool.h"

extern int lp_is_supported_instruction(char *instruction);
extern int lp_calc_memory(int mode, int num);
extern int lp_interpret_line(int line_pos, char *line, bool verbose);
