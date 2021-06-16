//
// Created by 고호정 on 2021/06/15.
//

#include <stdlib.h>
#include <string.h>

#include "lp_utils_debug.h"
#include "lp_utils_sio.h"

char* lp_vzheap_load(int mode, char *vzheap_pre) {
    static char *vzheap = NULL;

    // 가상 heap 대체
    if (mode) {
        free(vzheap);

        vzheap = vzheap_pre;
    }
    // heap이 없으면 메모리 0개만큼 할당
    if (vzheap == NULL) {
        // 임의의 값이 할당되지 않게 초기화
        vzheap = calloc(sizeof(char), 0);
    }

    // 즉시 반환
    return vzheap;
}
void lp_vzheap_write(const char *key, const char *value) {
    char *vzheap_orig = lp_vzheap_load(0, NULL);
    // k-v 저장소를 ; 기준으로 나눔
    char **vzheap = lp_split_string(vzheap_orig, ';');
    // 앞으로 확장할 예정인 vzheap_pre 포인터에 0만큼 메모리 할당
    char *vzheap_pre = "";

    int is_key_found = 0;

    for (int i = 0; *(vzheap + i); i++) {
        // 현재 덩어리(key=value)를 =로 나눔
        char **item = lp_split_string(*(vzheap + i), '=');
        // 미리 key= 형태를 만듦
        char *key_pre = lp_concat_string(key, "=");

        // 만약 함수 인자 key와 현재 key가 같으면
        if (!strcmp(key, *item)) {
            // 키가 발견되었다고 표시
            is_key_found = 1;
            // 새로운 값으로 대체하여 vzheap_pre에 이어붙임
            vzheap_pre = lp_concat_string(vzheap_pre, lp_concat_string(key_pre, value));
        } else {
            // 기존값으로 그대로 이어붙임 (이 때 *(item + 1)이 key= 뒤의 value가 됨)
            vzheap_pre = lp_concat_string(vzheap_pre, lp_concat_string(key_pre, *(item + 1)));
        }

        // 세미콜론으로 마침
        vzheap_pre = lp_concat_string(vzheap_pre, ";");

        // item에 대한 메모리 비움
        free(*item);
        free(*(item + 1));
        // 기존 vzheap에 대한 메모리 비움
        free(*(vzheap + i));
    }

    // 키가 없었다면 추가
    if (!is_key_found) {
        char *k_key = lp_concat_string(key, "=");
        char *k_value = lp_concat_string(value, ";");

        vzheap_pre = lp_concat_string(k_key, k_value);
    }

    // vzheap 주소를 vzheap_pre로 대체함
    lp_vzheap_load(1, vzheap_pre);
}
char *lp_vzheap_read(char *key) {
    char *vzheap_orig = lp_vzheap_load(0, NULL);
    // k-v 저장소를 ; 기준으로 나눔
    char **vzheap = lp_split_string(vzheap_orig, ';');

    for (int i = 0; *(vzheap + i); i++) {
        // ;로 마지막에 끝나므로 값이 없으면 순서 넘김
        if (!*(vzheap + i)) {
            continue;
        }

        // 현재 덩어리(key=value)를 =로 나눔
        char **item = lp_split_string(*(vzheap + i), '=');
        // 만약 함수 인자 key와 현재 key가 같으면
        if (!strcmp(key, *item)) {
            // value를 바로 반환
            return *(item + 1);
        }

        // item에 대한 메모리 비움
        free(*item);
        free(*(item + 1));
        // 기존 vzheap에 대한 메모리 비움
        free(*(vzheap + i));
    }

    return NULL;
}
