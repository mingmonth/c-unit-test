#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("hello");
	int width = 8;
	int *arr;
	arr = (int *) malloc (sizeof(int) * width);

	printf("ũ�� %d\n", _msize((void*)arr) / sizeof(int));
	free(arr);	
}
