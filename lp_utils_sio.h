//
// Created by 고호정 on 2021/06/15.
//
#include <stdbool.h>

extern char* lp_safemloc_char(unsigned long size);
extern char* lp_concat_string(const char *a, const char *b);
extern char** lp_split_string(char *text, const char sep);
extern char* lp_read_file(const char *path, bool verbose);
