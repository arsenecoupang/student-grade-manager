#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
	int id;
	char name[NAME_LEN];
	int korean;
	int english;
	int math;
	double average;
	int rank;
} Student;

// 전역 데이터
extern  Student students[MAX_STUDENTS];
extern int student_count;

// 함수 선언
void print_menu(void);

// 유틸
int nex_id(void);
void clear_input_buffer(void);

#endif
