#include <stdio.h>
#include <stdlib.h>
#include <rpc.h>
#include <windows.h>
#include "student.h"

Student students[MAX_STUDENTS];
int student_count = 0;


// 유틸리티 함수
void clear_intput_buffer(void) {
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}
int next_id(void) {
	int max_id = 0;
	for (int i = 0; i < student_count; ++i) {
		if (students[i].id > max_id) {
			max_id = students[i].id;
		}
	}
	return max_id + 1;
}


// 평균 & 등수 계산
void calc_average_and_rank(void) {
	// 평균
	for (int i =0; i < student_count; ++i) {
		students[i].average =
			(students[i].korean + students[i].english + students[i].math) / 3.0;
	}

	// 등수 계산
	for (int i = 0; i < student_count; ++i) {
		int rank = 1;
		for (int j = 0; j < student_count; ++j) {
			if (students[j].average > students[i].average) {
				rank++;
			}
		}
		students[i].rank = rank;
	}
}

// 메뉴 출력
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
    if (student_count >= MAX_STUDENTS) {
        printf("최대 학생 수(%d)명에 도달했습니다.\n", MAX_STUDENTS);
        return;
    }

    Student s;
    s.id = next_id();

    printf("\n── 학생 추가 ──\n");
    printf("이름 : "); scanf("%s", s.name); clear_input_buffer();

    printf("국어 점수 (0~100) : "); scanf("%d", &s.korean); clear_input_buffer();
    printf("영어 점수 (0~100) : "); scanf("%d", &s.english); clear_input_buffer();
    printf("수학 점수 (0~100) : "); scanf("%d", &s.math); clear_input_buffer();

    // 점수 범위 유효성 검사
    if (s.korean < 0 || s.korean > 100 || s.english < 0 || s.english > 100 || s.math < 0 || s.math > 100) {
    	printf("점수는 0~100 사이어야 합니다. 추가를 취소합니다.\n");
    	return;
    }

    students[student_count++] = s;
    cal_average_and_rank();
    save_to_file();

    printf("[ID %d] %s 학생이 추가되었습니다.\n", s.id, s.name);

}


// 학생 삭제 함수
void delete_student(void) {

}
