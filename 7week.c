#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

//����ü ����
typedef struct tnode {
	char* word;
	int count;
	struct tnode* left;
	struct tnode* right;

}node;

//�Լ� ����
struct tnode* addtree(struct tnode*, char*);
void treeprint(struct tnode*);
struct tnode* talloc(void);
int getword(char*, int lim);

//�޸� �Ҵ� �Լ�
struct tnode* talloc(void) {
	return (struct tnode*)malloc(sizeof(struct tnode));
}

//����Ž�� Ʈ���� ���ο� �ܾ� �߰��ϴ� �Լ�
struct tnode* addtree(struct tnode* p, char* w) {
	int cond;

	if (p == NULL) {	//p�� null�ΰ�� ���ο� ��带 �Ҵ��ϰ� �ʱ�ȭ
		p = talloc();
		p->word = _strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)	//�̹� �����ϴ� �ܾ��� ��� count + 1
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);		//�־��� �ܾ ���� �ܾ�� ���ĺ��� ������ ���� �ڽ� ���� �̵�
	else
		p->right = addtree(p->right, w);	//ū ��� ������ ���� �̵�
	return p;
}

void treeprint(struct tnode* p) {		//������ȸ������� ���� Ž�� Ʈ�� ���
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
			word[i++] = tolower(c);		//�ܾ �ҹ��ڷ� ��ȯ
		}
	}
	word[i] = '\0';		//word �迭�� ����
	return c == EOF ? EOF : 0;	//�Է��� ������ EOF ��ȯ
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