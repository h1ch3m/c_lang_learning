#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct liste{
                        int i;
                       struct liste *ptr;

}liste;
void new(liste **newone)
{
    *newone=(liste*)malloc(sizeof(liste));
}
void extraction(int tab[3],liste **first,liste **liste1)
{   int i=2;

    *first=NULL;
    while(i>=0)
    {
        new(liste1);
        (*liste1)->i=tab[i];
        (*liste1)->ptr=*first;
        *first=*liste1;
        i--;
    }
}

void main()
{
    liste *liste1,*newone,*newoneptr;
    int tab[3]={1,2,3};
    extraction(tab,&liste1,&newoneptr);
    printf("%d",liste1->ptr->ptr->i);
    free(newoneptr); //how does this free ALL the pointers ?
     printf("%d",liste1->ptr->ptr->i);

}
