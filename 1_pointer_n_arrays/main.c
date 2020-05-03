#include <stdio.h>
#include <stdlib.h>

void array_manipulations();

void pointer_manipulations();

void pointer_array_decay();

int main(int argc, char** argv) {

    array_manipulations();

    pointer_manipulations();

    pointer_array_decay();
}

void print_array_of_int(int ai[], int len){
    int i = len;
    while(i--)
        printf("[%d] ", ai[len-i-1]);
    printf("\n");
}

void print_pointers_of_int(int *ai, int len){
    // Notice that the instructions are same as print_array_of_int
    int i = len;
    while(i--)
        printf("[%d] ", ai[len-i-1]);
    printf("\n");
}

void assign_to_array_of_int(int ai[], int index, int value){
    ai[index] = value;
}

void array_manipulations(){
    printf("\n*** Array manipulations ***\n");
    /**
        Array are immutable reference to contiguous
        place holders for memory addresses.
        Their size are fixed. they can't be re-assigned
    */

    // Simple array declaration
    int ai_declared[5];
    print_array_of_int(ai_declared, 5);

    // Inline empty init array
    // this will fill the array with 0 values
    int ai_empty[5] = {};
    print_array_of_int(ai_empty, 5);

    // Inline array initialization
    int ai_initialized[10] = {1,2,3,4,5,6,7,8,9,10};
    print_array_of_int(ai_initialized, 10);

    // Arrays can't be re-assigned like this :
    // ai_declared = ai_initialized;

    // value assign
    ai_declared[0] = 3;
    print_array_of_int(ai_declared, 5);

    // Like pointers array are placeholders
    // a.k.a address types, reference types
    // so we pass them by address (not by value)
    assign_to_array_of_int(ai_declared,1,3);

    print_array_of_int(ai_declared, 5);

    // Array cannot be directly returned by functions
}

void pointer_manipulations(){
    printf("\n*** Pointer manipulations ***\n");
    // A pointer is a reference to memory address holding a value
    int i = 3;
    int *ip = &i;
    printf("ip address = %li [%p]  ; ip size = %d ; ip content = %d \n", ip, ip , sizeof(ip), *ip); // li long int data type wich size is 8 bytes

    // All pointers are 8 byte sized (in practice but not in theory)
    // This is for modern 64 bit processors (64 bits = 8 * 8 = 8 bytes, this is why pointer sizes are of 8 bytes)
    printf("Pointer type size : void* = %d; double* = %d; int* = %d; char* = %d; char** = %d \n", sizeof(void *),sizeof(double *),sizeof(int *),sizeof(char *),sizeof(char**));

    // A pointer can be of void type and be casted later to any actual type
    void *vp;
    vp = ip;
    int *recover_int = vp;
    printf("Void* for int address %p => %d \n", vp, *recover_int);
    char c = 'c';
    vp = &c;
    char *recover_char = vp;
    printf("Void* for char address %p => %c \n", vp, *recover_char);

    // Pointers are used to access and mutate values through function calls
    // They also limit copying large value arguments through the call stack
    // Imagine a limited memory environment that have to copy structures holding
    // large byte arrays (files or streams of data).
    // Also be aware of the stack vs heap memory regions.
    // Unallocated pointers still points stack memory addresses
    // and cannot (should not) be returned after function call
    // @see pointers chapters there http://www2.cs.uregina.ca/~hilder/cs833/Other%20Reference%20Materials/The%20C%20Programming%20Language.pdf
}


void pointer_array_decay(){
    printf("\n*** Pointers and arrays equivalences ***\n");
    /**
        Pointers and arrays are two referencing
        data structure in C language.
        There is equivalence between the two of them

        Quote from "The Programming language" book:
            " A pointer is a variable that contains the address of a variable. Pointers are much used in C,
        partly because they are sometimes the only way to express a computation, and partly because
        they usually lead to more compact and efficient code than can be obtained in other ways.
        Pointers and arrays are closely related;
        "
     */

    // Pointers point to a memory address
    // Memory addresses in C are represented as a large contiguous array
    // (Again, pay attention to address regions. Mainly Stack and Heap)
    // So if p points the Address A then p+1 points the address B where B is next to A : ...[][A][B][][][]...
    int ia = 3;
    int *pia = &ia,
        *pib = pia + 1;

    uintptr_t addr_int_val_ia = (uintptr_t) pia; // uintptr_t is an unsigned int type capable of holding pointer address = 8 bytes in general
    uintptr_t addr_int_val_ib = (uintptr_t) pib;
    // Pointer arithmetics gives us that PB - PA = 1
    // Address consideration gives that PB is 4 bytes long from PA (we need 4 bytes to encode int type)
    printf("For int type : pa = %p (li = %li); pb = %p (li = %li);pointer diff = %d; byte addresses diff = %d  \n", pia, pib, pia, pib, pib - pia, addr_int_val_ib - addr_int_val_ia);

    char ca = '3';
    char *pca = &ca,
        *pcb = pca + 1;

    uintptr_t addr_int_val_ca = (uintptr_t) pca;
    uintptr_t addr_int_val_cb = (uintptr_t) pcb;
    // Pointer arithmetics gives us that PB - PA = 1
    // Address consideration gives that PB is 1 byte long from PA (we need 1 byte to encode char type)
    printf("For char type :pa = %p (li = %li); pb = %p (li = %li);pointer diff = %d; byte addresses diff = %d  \n", pca, pcb, pca, pcb, pcb - pca, addr_int_val_cb - addr_int_val_ca);

    // As shown, pointers reference addresses as long dynamic array
    // So they can be considered as dynamic arrays

    // Since we are going to manipulate contiguous memory addresses
    // start by allocating it into the Heap region
    // /!\ We should not manipulate contiguous memory from the Stack and without arrays
    // exemple : int *pIntA  = &i; *(pIntA + 1) = 11;
    // This is because we dont know what address pIntA + 1 is used for
    // The program will sometimes work and sometimes crash (exemple: reserved memory place, permission to access denied, etc.)
    int *pIntA = malloc(5 * sizeof(int));

    // Always test if allocation is OK
    if( pIntA == NULL){
        printf("Allocation failed !");
        exit(1);
    }

    *pIntA = 10; // could have written *(pIntA + 0)
    *(pIntA + 1) = 11;
    *(pIntA + 2) = 12;
    *(pIntA + 3) = 13;
    *(pIntA + 4) = 14;
    // Notice that print_pointers_of_int instructions are identical to print_array_of_int
    print_pointers_of_int(pIntA, 5);
    // Notice that pIntA can be passed as int[] (int[] takes array and pointer to ints on function arguments - not on assignments)
    print_array_of_int(pIntA, 5);

    pIntA[0] = 20; // This is also pointer dereferencing (like *pIntA). It is similar to array access
    pIntA[1] = 21;
    pIntA[2] = 22;
    pIntA[3] = 23;
    pIntA[4] = 24;

    print_pointers_of_int(pIntA, 5);

    free(pIntA);

    // As array are static contiguous memory addresses
    // They can be transformed to pointers

    int intB[] = {10,11,12,13,14};

    int *pIntB1 = &intB[0];
    int *pIntB2 = intB; // This is shortcut to *pIntB1 = &intB[0];

    printf("pIntB1 == pIntB2 : %s \n", pIntB1 == pIntB2 ? "TRUE" : "FALSE");

    // Since arrays are statically allocated
    // It is safe to use pointer dereferencing and arithmetics
    // Even if we are in the Stack region; recall that memory is alreay allocated here
    pIntB2[0] = 30;
    *(pIntB2 + 1) = 31;
    pIntB2[2] = 32;
    pIntB2[3] = 33;
    pIntB2[4] = 34;

    // intB[] is passed as pointer here
    print_pointers_of_int(intB,5);
    // *pIntB2 give same values
    print_pointers_of_int(pIntB2, 5);

    // Other Implication of pointer arithmetics :  Pointers can be sliced
    pIntB2 ++;
    print_pointers_of_int(pIntB2, 4);
}
