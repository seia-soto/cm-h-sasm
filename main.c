#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lp_utils_debug.h"
#include "lp_utils_sio.h"
#include "lp_interpreter.h"

#define LP_DEFAULT_FILE "index.s" // 프로그램 파라메터에 파일이 없을 경우 대신 읽을 파일

int main(int argc, char *argv[]) {
    char *file_path;

    // 인자가 충분하지 않으면 (읽을 파일이 없으면) LP_DEFAULT_FILE로 대체
    if (argc < 2) {
        lp_warning("No file to describe! Interpreter will use default path instead.");

        file_path = lp_safemloc_char(strlen(LP_DEFAULT_FILE));
        strcpy(file_path, LP_DEFAULT_FILE);
    } else {
        file_path = lp_safemloc_char(strlen(argv[1]));
        strcpy(file_path, argv[1]);
    }

    char *file_buffer = lp_read_file(file_path);
    char **file_lines = lp_split_string(file_buffer, '\n');

    // 라인이 없을 때
    if (!file_lines) {
        lp_info("Nothing to do!");

        exit(0);
    }

    for (int i = 0; *(file_lines + i); i++) {
        lp_interpret_line(i, *(file_lines + i));

        free(*(file_lines + i));
    }

    // 메모리 정리 (필수)
    free(file_lines);
    free(file_path);
    free(file_buffer);

    return 0;
}
