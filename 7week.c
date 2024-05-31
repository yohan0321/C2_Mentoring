#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

//구조체 정의
typedef struct tnode {
	char* word;
	int count;
	struct tnode* left;
	struct tnode* right;

}node;

//함수 선언
struct tnode* addtree(struct tnode*, char*);
void treeprint(struct tnode*);
struct tnode* talloc(void);
int getword(char*, int lim);

//메모리 할당 함수
struct tnode* talloc(void) {
	return (struct tnode*)malloc(sizeof(struct tnode));
}

//이진탐색 트리에 새로운 단어 추가하는 함수
struct tnode* addtree(struct tnode* p, char* w) {
	int cond;

	if (p == NULL) {	//p가 null인경우 새로운 노드를 할당하고 초기화
		p = talloc();
		p->word = _strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)	//이미 존재하는 단어인 경우 count + 1
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);		//주어진 단어가 현재 단어보다 알파벳이 빠르면 왼쪽 자식 노드로 이동
	else
		p->right = addtree(p->right, w);	//큰 경우 오른쪽 노드로 이동
	return p;
}

void treeprint(struct tnode* p) {		//중위순회방식으로 이진 탐색 트리 출력
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

int getword(FILE* fp, char* word, int lim) {
	int c, i;

	i = 0;
	while (i < lim - 1 && (c = fgetc(fp)) != EOF && !isspace(c)) {
		if (isalpha(c)) {
			word[i++] = tolower(c);		//단어를 소문자로 변환
		}
	}
	word[i] = '\0';		//word 배열에 저장
	return c == EOF ? EOF : 0;	//입력이 끝나면 EOF 반환
}



int main() {
	struct tnode* root;
	char word[MAXWORD];
	FILE* fp = fopen("alice.txt", "r");

	root = NULL;
	while (getword(fp, word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	return 0;
}