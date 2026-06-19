#include <stdio.h>
#include "student.h"
#include <rpc.h>
#include <windows.h>

#pragma comment(lib, "Rpcrt4.lib")

int main() {
	load_from_file();

	int choice;
	while(1) {
		print_menu();
		scanf("%d", &choice);
		switch (choice) {
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			default:
		}
	}
	return 0;
}
