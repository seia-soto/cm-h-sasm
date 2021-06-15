//
// Created by 고호정 on 2021/06/15.
//
#include <stdio.h>
#include <stdlib.h>

void lp_info(char *message) {
    printf("INFO: %s\n", message);
}
void lp_warning(char *message) {
    printf("WARNING: %s\n", message);
}
void lp_error(char *message) {
    printf("ERROR: %s\n", message);

    exit(1);
}
