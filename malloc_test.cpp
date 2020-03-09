#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("hello");
	int width = 8;
	int *arr;
	arr = (int *) malloc (sizeof(int) * width);

	printf("Å©±â %d\n", _msize((void*)arr) / sizeof(int));
	free(arr);	
}
