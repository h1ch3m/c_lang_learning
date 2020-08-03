#ifndef FUNC_H
#define FUNC_H
typedef struct date
{
    int j;
    int m;
    int a;
} date;
typedef struct food
{
    char name[100];
    int carbs;
    int fats;
    int proteins;
} food;
void remplire(food *food, char *argv[]);                       //loads information about a food in a struct
void remplire_fiche(FILE *ptr, food food);                     //loads information about a food in a file
char *extraction(char ligne[100], int *i);                     //extracts information about a food from a string
void extraire_fiche(char ligne[100], food *food);              //putting extacted information in a struct
int eaten_information(char eaten[100], FILE *ptr, food *food); //extracting food information from a file
void food_eaten(food food, FILE *ptr);                         //putting eaten_food_information in a file
#endif
