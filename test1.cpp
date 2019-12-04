#include <stdio.h>

//global variable
int num1;
int num2;

// component define
// state1 check 1, uncheck 0
// state2 disable 1, enalbe 0
struct comp1 {
	int state1;
	int state2;
};

// init	
struct comp1 a[3][9] = {0, };

void printArray() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 9; j++) {
			printf("a[%d][%d]:\ncheck[%d]\nenable[%d]\nvalue[%d]\n", i, j, a[i][j].state1, a[i][j].state2, (j+1));
		}
		printf("\n");
	}
}

// �ش� i �ε����� state1 �� 1�� �ε��� return 
int check_state2() {
	for(int j = 0; j < 9; j++) {
		if(a[num1][j].state1 == 1) {
			return j;
		}						
	}
	// ������ ���� ���� ���
	return -1;
}

// check uncheck
void check_state1() {
	int checkedIndex = -1;
	// üũ�Ǿ��� index ������.	
	checkedIndex = check_state2();
	printf("checked Index:[%d]\n", checkedIndex);
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 9; j++) {			
			
			if(i == num1) {
				// uncheck
				a[i][j].state1 = 0;
				if(j == num2) {
					// check
					a[i][j].state1 = 1;					
				}
			} else {
				if(j == num2) {					
					//disable
					a[i][j].state2 = 1;
				} else if(j == checkedIndex) {
					//enable
					a[i][j].state2 = 0;
				}
			}			
		}
	}
	printArray();
}

void select_panel() {	
	//check_state2();
	printArray();
	printf("STEP2-input radio button number:");
	scanf("%d", &num2);	
}

int main() {
	while(num1 != 999) {
		printf("STEP1-input panel number:");
		scanf("%d", &num1);
		select_panel();				
		check_state1();
		printf("num1:[%d], num2:[%d]\n", num1, num2);
	}
		
	printf("Good Bye!!!");
	return 0;
}
