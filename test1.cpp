#include <stdio.h>
#define LED_NUM_MAX 3
#define RADIO_BTN_NUM_MAX 9
#define END_NUM 999

//global variable
int num1;
int num2;
int break_flag = 0;

// component define
// state1 check 1, uncheck 0
// state2 disable 1, enalbe 0
struct comp1 {
	int state1;
	int state2;
};

// init	
struct comp1 a[LED_NUM_MAX][RADIO_BTN_NUM_MAX] = {0, };

void printArray2() {
	for(int i = 0; i < LED_NUM_MAX; i++) {
		for(int j = 0; j < RADIO_BTN_NUM_MAX; j++) {
			printf("a[%d][%d]:check[%d]enable[%d]value[%d]\n", i, j, a[i][j].state1, a[i][j].state2, (j+1));
		}
		printf("\n");
	}
}

void printArray() {
	for(int j = 0; j < RADIO_BTN_NUM_MAX; j++) {
		for(int i = 0; i < LED_NUM_MAX; i++) {		
			printf("a[%d][%d]:C[%d]E[%d]V[%d]\t", i, j, a[i][j].state1, a[i][j].state2, (j+1));
		}
		printf("\n");
	}
}

// 해당 i 인덱스에 state1 이 1인 인덱스 return 
int check_state2() {
	for(int j = 0; j < RADIO_BTN_NUM_MAX; j++) {
		if(a[num1][j].state1 == 1) {
			return j;
		}						
	}
	// 설정된 값이 없는 경우
	return -1;
}

// check uncheck
void check_state1() {
	int checkedIndex = -1;
	// 체크되었던 index 얻어오기.	
	checkedIndex = check_state2();
	printf("checked Index:[%d]\n", checkedIndex);
	for(int i = 0; i < LED_NUM_MAX; i++) {
		for(int j = 0; j < RADIO_BTN_NUM_MAX; j++) {			
			
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

// 1:true, 0:false
int check_enable() {	 
	if(a[num1][num2].state2 == 1) {
		return 0;
	}
	return 1;
}

// 1:true, 0:false
int check_range1() {	
	if(num1 >= 0 && num1 < LED_NUM_MAX) {
		return 1;
	}
	if(num1 == END_NUM) {
		break_flag = 1;
		return 1;
	}
	printf("num1 range[0-%d]\n", LED_NUM_MAX - 1);
	printf("program end input 999\n");
	return 0;
} 

// 1:true, 0:false
int check_range2() {	
	if(num2 >= 0 && num2 < RADIO_BTN_NUM_MAX) {
		return 1;
	}
	if(num1 == END_NUM) {
		break_flag = 1;
		return 1;
	}
	printf("num2 range[0-%d]\n", RADIO_BTN_NUM_MAX - 1);
	printf("program end input 999\n");
	return 0;
} 

void select_radio_button() {
	if(break_flag)	{
		return;
	}
	
	printArray();
	
	do {
		printf("STEP2-input radio button number:");
		scanf("%d", &num2);
	} while(!check_range2() || !check_enable());
}

void select_led() {	
	do {
		printf("STEP1-input panel number:");
		scanf("%d", &num1);
	} while(!check_range1());
}

int main() {	
	while(!break_flag) {
		select_led();		
		select_radio_button();
		if(!break_flag) {
			check_state1();
			printf("num1:[%d], num2:[%d]\n", num1, num2);
		}		
	}
		
	printf("Good Bye!!!");
	return 0;	
}
