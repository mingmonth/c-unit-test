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

// check uncheck
void check_state1() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 9; j++) {
			if(i != num1 && a[i][j].state1 == 1) {
				//disable
				a[i][j].state2 = 1;				
			}
			
			if(i == num1 && j == num2) {
				a[i][j].state1 = 1;
			} else if(i == num1) {
				a[i][j].state1 = 0;
			}
			printf("a[%d][%d]:\ncheck[%d]\nenable[%d]\nvalue[%d]\n", i, j, a[i][j].state1, a[i][j].state2, (j+1));
		}
		printf("\n");
	}
}

// enable disable
void check_state2() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 9; j++) {
			if(i != num1 && a[i][j].state1 == 1) {
				//disable
				a[i][j].state2 = 1;
			} 
			if(i == num1 && a[i][j].state2 == 1) {
				//enable
				a[i][j].state2 = 0;
			}
			printf("a[%d][%d]:\ncheck[%d]\nenable[%d]\nvalue[%d]\n", i, j, a[i][j].state1, a[i][j].state2, (j+1));
		}
		printf("\n");
	}	
}

void select_panel() {	
	check_state2();
	printf("STEP2-input radio button number:");
	scanf("%d", &num2);	
}

int main() {
	while(num1 != 999) {
		printf("STEP1-input panel number:");
		scanf("%d", &num1);		
		select_panel();				
		check_state1();
	}
	
	
	printf("hello world!!!");
	return 0;
}
