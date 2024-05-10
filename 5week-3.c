#include <stdio.h>
#include <string.h>

int mystrlen(char* s) {
	int a = 0;
	while (*s != '\0') {
		a++;
		s++;
	}
	return a;
}

int main(void) {
	char* s[] = { "This is Lab5", "Easy C Programing", "Have fun" };

	printf("with strlen()\n");
	int n = (int)(sizeof(s) / sizeof(char*));
	for (int i = 0; i < n; i++)
		printf("%s %d\n", *(s + i), (int)strlen(s[i]));
	putchar('\n');

	printf("with mystrlen()\n");
	for (int i = 0; i < n; i++)
		printf("%s %d\n", *(s + i), mystrlen(s[i]));

	
	return 0;
}