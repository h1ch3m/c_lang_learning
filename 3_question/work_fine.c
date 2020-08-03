#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void fgetsline(char *s, int size)
{
    fgets(s, size, stdin);

    int len = strlen(s);
    if (s[len - 1] == '\n')
       s[len - 1] = '\0';
}
void main()
{
    FILE *ptr_file;
    int i=1,mat,number;
    char name[100];
    char last[100];


        printf("information:\n");
        printf("name:");
        fgetsline(name,100);
        printf("last:");
        fgetsline(last,100);
        scanf("%d",&i);
        printf("%s %s %d ",last,name,i);
}
