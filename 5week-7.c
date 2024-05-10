#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define ALLOCSIZE 10000


char* lineptr[MAXLINES];

int readlines(char* lineptr[], int maxlines);
void writelines(char* lineptr[], int nlines);
void qsort(void* lineptr[], int left, int right, int (*comp)(const void*, const void*));
int numcmp(const char* s1, const char* s2);
char* alloc(int);
int getline(char* line, int max);

int main(int argc, char* argv[]) {
    int nlines;
    int numeric = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort((void**)lineptr, 0, nlines - 1, (numeric ? numcmp : (int (*)(const void*, const void*))strcmp));
        writelines(lineptr, nlines);
        return 0;
    }
    else {
        printf("input too big to sort\n");
        return 1;
    }
}

int readlines(char* lineptr[], int maxlines) {
    int len, nlines;
    char* p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

void writelines(char* lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
        free(lineptr[i]); 
    }
}

void qsort(void* v[], int left, int right, int (*comp)(const void*, const void*)) {
    int i, last;
    if (left >= right)
        return;

    void swap(void* v[], int, int);
    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    qsort(v, left, last - 1, comp);
    qsort(v, last + 1, right, comp);
}

void swap(void* v[], int i, int j) {
    char* temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(const char* s1, const char* s2) {
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int strcmp(char* s, char* t) {
    int i;
    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;
    return s[i] - t[i];
}

int getline(char* line, int max) {
    if (fgets(line, max, stdin) == NULL)
        return 0;
    else
        return strlen(line);
}

char* alloc(int n) {
    static char allocbuf[ALLOCSIZE];
    static char* allocp = allocbuf;

    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    }
    else {
        return 0;
    }
}


