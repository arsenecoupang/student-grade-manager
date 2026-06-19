#include <stdio.h>
#include "student.h"
#include <rpc.h>
#include <windows.h>

#pragma comment(lib, "Rpcrt4.lib")

int main() {
	int choice;

    while (1) {
        print_menu();
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1: add_student();    break;
            case 2: delete_student(); break;
            case 3: update_student(); break;
            case 4: show_statistics(); break;
            case 0:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("올바른 메뉴 번호를 입력하세요.\n");
        }
    }
}
