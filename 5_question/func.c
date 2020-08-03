#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

void remplire(food *food, char *argv[])
{
    strcpy(food->name, argv[2]);
    food->proteins = atoi(argv[3]);
    food->carbs = atoi(argv[4]);
    food->fats = atoi(argv[5]);
}

void remplire_fiche(FILE *ptr, food food)
{
    fprintf(ptr, "%s carbs=%d/fats=%d/proteins=%d.\n", food.name, food.carbs, food.fats, food.proteins);
}

char *extraction(char ligne[100], int *i)
{
    int j = 0, u;
    char *s, *s2;
    s = malloc(sizeof(char) * 200); //is it okay to allocate way too much space ? :o

    while (ligne[*i] != '=')
    {
        *i = *i + 1;
    }
    *i = *i + 1;
    while ((ligne[*i] != '/') && (ligne[*i] != '.'))
    {
        s[j] = ligne[*i];
        j++;
        *i = *i + 1;
    }
    s[j] = '\0';
    return (s); //is it okay to free the allocated space outside the function ?
}

void extraire_fiche(char ligne[100], food *food)
{
    int i;
    char *transition;
    transition = extraction(ligne, &i); //is it the right way to free the allocated space from the "extraction" function ?
    food->carbs = atoi(transition);
    free(transition);
    transition = extraction(ligne, &i);
    food->fats = atoi(transition);
    free(transition);
    transition = extraction(ligne, &i);
    food->proteins = atoi(transition);
    free(transition);
}

int eaten_information(char eaten[100], FILE *ptr, food *food)
{
    char transition[20];
    char ligne[100];
    int i;

    while (fgets(ligne, 100, ptr) != NULL)
    {
        while (ligne[i] != ' ')
        {
            transition[i] = ligne[i];
            i++;
        }
        transition[i] = '\0';
        if (strcmp(transition, eaten) == 0)
        {
            extraire_fiche(ligne, food);

            return (1);
        }
        i = 0;
    }
    return (0);
}

void food_eaten(food food, FILE *ptr)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("%s", asctime(tm));
    fprintf(ptr, "%s\ncarbs=%d/fats=%d/proteins=%d", asctime(tm), food.carbs, food.fats, food.proteins);
}
