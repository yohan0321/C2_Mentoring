#include <stdio.h>

int main(void) {
	int a[] = { 1, 2, 3, 4, 5 };
	int* p = a;
	int i;

	for (i = 0; i < 5; i++) {
		int* p = &a[i];
		printf("%d ", *p);
	}

	printf("\n");
	i = 0;

	while (i < 5) {
		int* p = &a[i];
		printf("%d ", *p);
		i++;
	}
	return 0;
}