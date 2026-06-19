#include <stdio.h>
#include <stdlib.h>
#include <rpc.h>
#include <windows.h>
#include "student.h"

int student[MAX_STUDENT][5];

// 처음에 어떤 메뉴 출력해주는 함수
void print_menu(void) {
	printf("\n╔══════════════════════════════╗\n");
    printf("║   학생 성적 관리 시스템       ║\n");
    printf("╠══════════════════════════════╣\n");
    printf("║  1. 학생 추가                ║\n");
    printf("║  2. 학생 삭제                ║\n");
    printf("║  3. 성적 수정                ║\n");
    printf("║  4. 전체 목록 보기           ║\n");
    printf("║  5. 이름으로 검색            ║\n");
    printf("║  6. 통계 보기                ║\n");
    printf("║  7. 저장                     ║\n");
    printf("║  0. 종료                     ║\n");
    printf("╚══════════════════════════════╝\n");
    printf("선택 > ");
}

// 학생 추가 함수
void add_student(void) {

}

// 학생 삭제 함수
void delete_student(void) {

}
