//
// Created by 고호정 on 2021/06/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lp_utils_debug.h"

// 안전하게 메모리를 할당하기 위한 함수로 메모리 할당 시마다 포인터가 올바르게 설정되었는지 체크함
char* lp_safemloc_char(const unsigned long size) {
    // 자동으로 NULL TERMINATOR 추가
    char *char_ptr = malloc(size + 1);

    // heap에 정상적으로 메모리를 할당했는지 체크
    if (!char_ptr) {
        lp_error("Failed to allocate memory on heap!");
    }

    return char_ptr;
}

char* lp_concat_string(const char *a, const char *b) {
    // 각각의 문자열 길이 가져오기
    unsigned long size_a = strlen(a);
    unsigned long size_b = strlen(b);

    // 안전하게 메모리 할당
    char *result = lp_safemloc_char(size_a + size_b);

    strcpy(result, a);
    strcat(result, b);

    return result;
}
char** lp_split_string(char *text, const char sep) {
    int count = 0;
    char **result;
    char *tmp = text;
    char *last_comma = 0;
    char delim[2] = { sep, 0 };

    while (*tmp) {
        if (sep == *tmp) {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    // 마지막 항목에 대한 추가 메모리 공간 확보
    count += last_comma < (text + strlen(text) - 1);

    // NULL TERMINATOR 추가
    count++;

    result = malloc(sizeof(char*) * count);

    if (result) {
        int idx = 0;
        char *token = strtok(text, delim);

        while (token) {
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }

        *(result + idx) = 0;
    }

    return result;
}
char* lp_read_file(const char *path) {
    // 읽을 파일의 경로가 주어지지 않았을 때
    if (!strlen(path)) {
        lp_error("The path of file to execute not provided! Please keep context.");
    }

    // 파일 경로와 함께 로그 메세지 출력
    lp_info(lp_concat_string("Loading file from ", path));

    // 파일 포인터 정의
    FILE *file;

    long file_size; // 파일 크기
    char *file_buffer; // 파일 버퍼 (읽은 데이터가 쌓일 곳)

    // Windows에서 오류를 피하기 위해 rb 모드로 읽기
    file = fopen(path, "rb");

    // 파일이 존재하지 않거나 읽을 수 없을 때
    if (!file) {
        lp_error(lp_concat_string("No such file ", path));
    }

    // 파일 끝으로 커서를 이동하여 파일 크기를 측정하고 file_size에 값 할당
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    // 다시 커서를 파일의 위로 이동
    rewind(file);

    // 파일 버퍼에 file_size + NULL만큼 메모리 할당
    file_buffer = calloc(1, file_size + 1);

    // 메모리 할당 실패 시
    if (!file_buffer) {
        fclose(file);
        lp_error("Failed to allocate memory to read file!");
    }
    // 파일 읽기 작업 실패 시
    if (1 != fread(file_buffer, file_size, 1, file)) {
        fclose(file);
        lp_error("Failed to read all file content!");
    }

    // 메모리 절약을 위해 파일 포인터를 먼저 닫음
    fclose(file);

    // 버퍼만 반환 (이후에 free 요망)
    return file_buffer;
}
