#include <stdio.h>

int main() {
	int n1, n2, x, t;
	t = 1;
	printf("두 정수 입력:");
	scanf_s("%d %d", &n1, &n2);

	for (int i = 1; i <= n1 && i <= n2; ++i) {
		if (n1 % i == 0 && n2 % i == 0)
			x = i;
	}

	t = (n1 * n2) / x;
	printf("최소 공배수: %d", t);

	return 0;
}