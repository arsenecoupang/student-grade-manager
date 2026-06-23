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

void add_student(void);
void delete_student(void);
void update_student(void);
void list_students(void);

// 통계
void calc_average_and_rank(void);
void show_statistics(void);

// 유틸
int next_id(void);
void clear_input_buffer(void);

#endif
