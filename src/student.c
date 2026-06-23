#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rpc.h>
#include <windows.h>
#include "student.h"

Student students[MAX_STUDENTS];
int student_count = 0;


// 유틸리티 함수
void clear_input_buffer(void) {
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

int find_by_id(int id) {
    for (int i = 0; i < student_count; ++i) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1;
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
	system("cls");
	printf("\n╔══════════════════════════════╗\n");
    printf("║   학생 성적 관리 시스템      ║\n");
    printf("╠══════════════════════════════╣\n");
    printf("║  1. 학생 추가                ║\n");
    printf("║  2. 학생 삭제                ║\n");
    printf("║  3. 성적 수정                ║\n");
    printf("║  4. 통계 보기                ║\n");
    printf("║  5. 전체 목록 보기           ║\n");
    printf("║  0. 종료                     ║\n");
    printf("╚══════════════════════════════╝\n");
    printf("선택 > ");
}




// 전체 목록 출력
void list_students(void) {
    if (student_count == 0) {
        printf("등록된 학생이 없습니다.\n");
        printf("\n계속하려면 Enter를 누르세요...");
        getchar();
        return;
    }

    printf("\n── 전체 학생 목록 (%d명) ──\n", student_count);
    printf("┌─────┬────────────┬──────┬──────┬──────┬────────┬──────┐\n");
    printf("│ ID  │    이름    │ 국어 │ 영어 │ 수학 │  평균  │ 등수 │\n");
    printf("├─────┼────────────┼──────┼──────┼──────┼────────┼──────┤\n");
    for (int i = 0; i < student_count; ++i) {
        // 한글 표시 너비 계산: ASCII는 1칸, 한글(0xC0 이상)은 2칸
        int w = 0;
        for (int j = 0; students[i].name[j]; j++) {
            unsigned char c = students[i].name[j];
            if (c < 0x80) w++;
            else if (c >= 0xC0) w += 2;
        }
        int pad = 10 - w;
        if (pad < 0) pad = 0;
        printf("│ %3d │ %s%*s │ %4d │ %4d │ %4d │ %6.1f │ %4d │\n",
               students[i].id, students[i].name, pad, "",
               students[i].korean, students[i].english, students[i].math,
               students[i].average, students[i].rank);
    }
    printf("└─────┴────────────┴──────┴──────┴──────┴────────┴──────┘\n");

    printf("\n계속하려면 Enter를 누르세요...");
    getchar();
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
    calc_average_and_rank();

    printf("[ID %d] %s 학생이 추가되었습니다.\n", s.id, s.name);

}


// 학생 삭제 함수
void delete_student(void) {
    if (student_count == 0) {
        printf("등록된 학생이 없습니다.\n");
        return;
    }

    int id;
    printf("\n삭제할 학생 ID: ");
    scanf("%d", &id);
    clear_input_buffer();

    int idx = find_by_id(id);
    if (idx == -1) {
        printf("%d 학생을 찾을 수 없습니다.\n", id);
        return;
    }

    printf("%s 학생을 삭제하시겠습니까? (y/n)", students[idx].name);
    char confirm;
    scanf("%c", &confirm);
    clear_input_buffer();
    if (confirm != 'y') {
        printf("취소되었습니다.\n");
        return;
    }

    for (int i = idx; i < student_count - 1; ++i) {
        students[i] = students[i + 1];
    }
    student_count--;

    calc_average_and_rank();
    printf("%d 학생이 삭제되었습니다.\n", id);
}



//성적 수정 기능
void update_student(void) {
    if (student_count == 0) {
        printf("등록된 학생이 없습니다.\n");
        return;
    }

    int id;
    printf("\n수정할 학생 ID: ");
    scanf("%d", &id);
    clear_input_buffer();

    int idx = find_by_id(id);
    if (idx == -1) {
        printf("%d 학생을 찾을 수가 없습니다.\n", id);
        return;
    }

    printf("── [%s] 성적 수정 (현재: 국어 %d / 영어 %d / 수학 %d) ──\n",
           students[idx].name,
           students[idx].korean, students[idx].english, students[idx].math);

    printf("새 국어 점수 : "); scanf("%d", &students[idx].korean); clear_input_buffer();
    printf("새 영어 점수 : "); scanf("%d", &students[idx].english); clear_input_buffer();
    printf("새 수학 점수 : "); scanf("%d", &students[idx].math); clear_input_buffer();

    calc_average_and_rank();
    printf("성적이 수정되었습니다.\n");
}

void show_statistics(void) {
    if (student_count == 0) {
        printf("등록된 학생이 없습니다.\n");
        return;
    }
    double sum_kor = 0, sum_eng = 0, sum_mat = 0, sum_avg = 0;
    double max_avg = -1, min_avg = 101;
    int best_idx = 0, worst_idx = 0;

    for (int i = 0; i < student_count; ++i) {
        sum_kor += students[i].korean;
        sum_eng += students[i].english;
        sum_mat += students[i].math;
        sum_avg += students[i].average;
        if (students[i].average > max_avg) {
            max_avg = students[i].average;
            best_idx = i;
        }
        if (students[i].average < min_avg) {
            min_avg = students[i].average;
            worst_idx = i;
        }
    }

    int n = student_count;
    printf("\n── 통계 (%d명) ──\n", n);
    printf("  과목 평균  : 국어 %.1f  /  영어 %.1f  /  수학 %.1f\n",
           sum_kor / n, sum_eng / n, sum_mat / n);
    printf("  전체 평균  : %.1f\n", sum_avg / n);
    printf("  최고 점수  : %s (%.1f)\n",
           students[best_idx].name, students[best_idx].average);
    printf("  최저 점수  : %s (%.1f)\n",
           students[worst_idx].name, students[worst_idx].average);

    int grades[5] = {0};
    for (int i = 0; i < student_count; i++) {
        double avg = students[i].average;
        if      (avg >= 90) grades[0]++;
        else if (avg >= 80) grades[1]++;
        else if (avg >= 70) grades[2]++;
        else if (avg >= 60) grades[3]++;
        else                grades[4]++;
    }
    printf("\n  등급 분포\n");
    printf("  A(90~) : %d명\n", grades[0]);
    printf("  B(80~) : %d명\n", grades[1]);
    printf("  C(70~) : %d명\n", grades[2]);
    printf("  D(60~) : %d명\n", grades[3]);
    printf("  F(~59) : %d명\n", grades[4]);
}
