#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct int_list
{
    int i;
    struct int_list *ptr;

} int_list;

int_list* new_int_list()
{
    return (int_list *) malloc(sizeof(int_list));
}

int_list* to_int_list(int tab[], int size)
{
    int_list* current = new_int_list();
    int_list* head = current;
    for (int i = 0; i < size; i++) {
        current->i = tab[i];
        if (i < size - 1) {
            current->ptr = new_int_list();
            current = current->ptr;
        }else {
            current->ptr = NULL;
        }

    }
    return head;
}

void print_linked_list(int_list *node) {
    if (node != NULL) {
        printf("-> %d", node->i);
        print_linked_list(node->ptr);
    }
}

void free_linked_list(int_list *node) {
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
    int tab[3] = {1, 2, 3};
    int_list* head = to_int_list(tab, 3);

    print_linked_list(head);
    free_linked_list(head);
    printf("\n all done \n");
    // this can (or not) rise access violation error
    // print_linked_list(liste1);
}
