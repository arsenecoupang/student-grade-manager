#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENT 100
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

void print_menu(void);
