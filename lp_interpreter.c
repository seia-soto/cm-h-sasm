//
// Created by 고호정 on 2021/06/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lp_utils_debug.h"
#include "lp_utils_sio.h"
#include "lp_vzheap.h"

int lp_is_supported_instruction(char *instruction) {
    char instructions[] = "SET,UNSET,ADD,MINUS,READ,PRINT,PRINT_I";
    char **instruction_set = lp_split_string(instructions, ',');

    for (int i = 0; *(instruction_set + i); i++) {
        if (!strcmp(instruction, *(instruction_set + i))) {
            return i;
        }
    }

    return -1;
}
int lp_calc_memory(int mode, int num) {
    static int i = 0;

    if (mode) {
        i = num;
    }

    return i;
}
int lp_interpret_line(int line_pos, char *line, bool verbose) {
    if (verbose == true) {
        lp_info(lp_concat_string("Interpreting... ", line));
    }

    char **tokens = lp_split_string(line, ' ');
    int command_id = lp_is_supported_instruction(*tokens);

    if (command_id < 0) {
        printf("LINE: %d -> ", line_pos);

        lp_error("Unknown instruction found at line!");
    }

    switch (command_id) {
        case 0: { // SET
            // 커맨드 이후 첫 번재 인자는 key
            char *key = *(tokens + 1);
            // 0만큼 할당
            char *value = "";

            // 나머지 토큰을 모두 더해 설정할 값으로 만들어줍니다
            for (int i = 2; *(tokens + i); i++) {
                if (i > 2) {
                    value = lp_concat_string(value, " ");
                }

                value = lp_concat_string(value, *(tokens + i));
            }

            // 가상 힙에 변수 등록
            lp_vzheap_write(key, value);

            break;
        }
        case 1: { // UNSET
            char *key = *(tokens + 1);

            lp_vzheap_write(key, "");

            break;
        }
        case 2: { // ADD
            long r = 0;

            for (int i = 1; *(tokens + i); i++) {
                if (!strcmp(*(tokens + i), "MEM")) {
                    r += (long)lp_calc_memory(0, 0);

                    continue;
                }

                r += strtol(*(tokens + i), NULL, 10);
            }

            lp_calc_memory(1, (int)r);

            break;
        }
        case 3: { // MINUS
            long r = (strtol(*(tokens + 1), NULL, 10));

            for (int i = 2; *(tokens + i); i++) {
                if (!strcmp(*(tokens + i), "MEM")) {
                    r -= (long)lp_calc_memory(0, 0);

                    continue;
                }

                r -= strtol(*(tokens + i), NULL, 10);
            }

            lp_calc_memory(1, (int)r);

            break;
        }
        case 4: { // READ
            char *key = *(tokens + 1);

            printf("%s\n", lp_vzheap_read(key));

            break;
        }
        case 5: { // PRINT (string)
            for (int i = 1; *(tokens + i); i++) {
                printf("%s ", *(tokens + i));
            }

            printf("\n");

            break;
        }
        case 6: { // PRINT (calc memory)
            printf("%d\n", lp_calc_memory(0, 0));

            break;
        }
    }

    return 0;
}
