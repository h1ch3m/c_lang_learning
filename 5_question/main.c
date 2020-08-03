#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

int main(int argc, char *argv[])
{
    food food;
    int i = 0;
    FILE *ptr;
    FILE *ptr2;
    char *s;

    switch (*argv[1])
    {
    case '1':
        if (argc != 6)
            return (0);
        ptr = fopen("information.txt", "a");
        remplire(&food, argv);
        remplire_fiche(ptr, food);
        fclose(ptr);
        break;
    default:
        break;
    }
    printf("oui"); //workts only with this line (probably because of any other reason than a mistake in my code)
    ptr = fopen("information.txt", "r+");
    eaten_information("bonjour", ptr, &food);
    printf("%d %d %d", food.carbs, food.fats, food.proteins);
    fclose(ptr);
    ptr2 = fopen("food.txt", "w+");
    food_eaten(food, ptr2);
    fprintf(ptr2, "cv"); //works if i dont open annother file (probably because of god)
    fclose(ptr2);
}
