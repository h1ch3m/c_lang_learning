#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

void basic_strings();

void basic_maniuplations();

void encoding();

int main(int argc, char** argv) {

    basic_strings();

    basic_maniuplations();

    encoding();
}


void basic_strings(){
    printf("\n*** Basic strings ***\n");

    // String are typically handled in c in the form of a char array
    // a string = array of chars ending with the \0 char (null char)
    char c[] = { 't','h','i','s',' ','i','s',' ','g','r','e','a','t','\0' };

    printf("c[] string is : %s \n", c);

    // Because of array / pointers equivalence we can write
    char *cp = c;
    // but not : char *cp = { 't','h','i','s',' ','i','s',' ','g','r','e','a','t','\0' }
    // since the inline arrays are not the reference (we need a declaration) - /!\ not sure about the explanation

    printf("*c string is : %s \n", cp);

    // chars are 1 byte sized type
    // notice that \0 == 0x00
    char bytesc[] = { 0x74, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x67, 0x72, 0x65, 0x61, 0x74, 0x00 };
    printf("bytesc[] string is : %c \n", cp);


    // Char arrays = strings can be manipulated

    c[0] = 'T';
    c[1] = 'H';
    c[2] = 'I';
    c[3] = 'S';

    cp[5] = 'I';
    cp[6] = 'S';

    printf("New c[] string is : %s \n", cp);

    // Const String still can be modified by pointers
    const char constc[] = { 't','h','i','s',' ','i','s',' ','g','r','e','a','t','\0' };

    char *constcp = constc;
    constcp[5] = 'I';
    constcp[6] = 'S';

    printf("New constc[] string is : %s \n", constcp);

    // String literals are used to facilitate static string usage (but they are immutable)
    // cannot be changed - they are in a static memory allocated at compile time (or kind of)
    char sl[] = "this is great" ;

    // String literal can directly be referenced by a pointer
    char *slp = "this is great" ;

    printf("*slp string is : %s \n", slp);

    // There are forbidden
    // sl[5] = 'I';
    // or slp[6] = 'S';
}

void basic_maniuplations(){
    printf("\n*** String manipulations ***\n");
    // Unlike other language, string manipulation in c are not handy
    // The stc library in string.h is used for this purpose
    // @see https://en.wikibooks.org/wiki/C_Programming/String_manipulation#The_%3Cstring.h%3E_Standard_Header

    // for doing strcat, we need to have sufficient memory allocated for the concatenation
    char *c = malloc(200);
    strcpy(c, "This is ");
    strcat(c, "Great");

    printf("Concatenation gives : %s \n", c);

    printf("String size is : %d \n", strlen(c));

    free(c);
}

void encoding(){
    printf("\n*** String encoding ***\n");
    // http://cppwhispers.blogspot.com/2012/11/unicode-and-your-application-3-of-n.html

    // First  : char array definition and manipulations do not handle encoding
    // Second : String literal and IO functions are responsible for encoding
    // Third  : String literal encoding are compiler and platform dependent (for modern gcc, it is utf-8 charset by default)

    char simple[] = "This is great";
    char special[] = "This is gr€at";

    printf("Size of simple[] = %d \n", strlen(simple));
    printf("Size of special[] = %d \n", strlen(special));

    // same as (since sizeof(char) == 1)
    // printf("Size of simple[] = %d \n", sizeof(simple) - 1 );
    // printf("Size of special[] = %d \n", sizeof(special) - 1 );

    // reduce the problem
    printf("Size of E = %d \n", strlen("E"));   // give 1
    printf("Size of € = %d \n", strlen("€"));  // give 3

    // Since we need 3 bytes to encode € sign (this is utf-8, a variable length encoding)
    // we cannot do char c = '€'
    char c = '€';
    //printf("Char = %c \n", c);

    // This was text encoding. a string in c is a char array and do not consider encoding
    // String literal and IO functions from compiler, libraries, etc. do consider it

    // For some uses, C language definde wchar_t type wich is > 1 byte sized (usually 4 bytes but it is compiler dependent)
    // Notice the L modifier before string literal

    wchar_t wstring[] = L"This is great";
    // we could hve written : wchar_t *wstring = L"This is great";

    printf("wstring[] = %ls \n", wstring);
    printf("Size of wstring[] = %d (sizeof(wchar_t) = %d) \n", sizeof(wstring) / sizeof(wchar_t) - 1, sizeof(wchar_t));
    // /!\ i dont know the L"..." encoding and if it is utf8 but by default it do not encoding € sign
}
