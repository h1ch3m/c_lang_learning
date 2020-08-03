#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct employe
{
    int matricule;
    char name[100];
    char last[100];
} employe;
employe one;
void fgetsline(char *s, int size)
{
    fgets(s, size, stdin);

    int len = strlen(s);
    if (s[len - 1] == '\n')
        s[len - 1] = '\0';
}
void main()
{

    int i = 1, mat, number;
    char number_line[30];
    FILE *info;
    printf("number : ");
    fgetsline(number_line, 30);
    i = atoi(number_line);

    printf("information:\n");
    printf("name:");
    fgetsline(one.last, 100);
    printf("last:");
    fgetsline(one.name, 100);
    printf("%s %s %d ", one.last, one.name, i);
}
