#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct liste
{
    int i;
    struct liste *ptr;

} liste;

void new (liste **newone)
{
    *newone = (liste *) malloc(sizeof(liste));
}

void extraction(int tab[3], liste **first, liste **liste1)
{
    int i = 2;

    *first = NULL;
    while (i >= 0)
    {
        new (liste1);
        (*liste1)->i = tab[i];
        (*liste1)->ptr = *first;
        *first = *liste1;
        i--;
    }
}

void print_linked_list(liste *node) {
    if (node != NULL) {
        printf("-> %d", node->i);
        print_linked_list(node->ptr);
    }
}

void free_linked_list(liste *node) {
    if (node != NULL) {
        free_linked_list(node->ptr);
        // we always need to free every allocated memory
        // so for every malloc we need to have a corresponding free
        // Note that free do not have to know the size of the memory block to be freed
        // That is an internal implementation: c language internally track every pointer allocated size
        free(node);
    }
}

void main()
{
    liste *liste1, *newoneptr;
    int tab[3] = {1, 2, 3};
    extraction(tab, &liste1, &newoneptr);
    print_linked_list(liste1);
    free_linked_list(liste1);
    printf("\n all done \n");
    // this can (or not) rise access violation error
    // print_linked_list(liste1);
}
