#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Note : this remove the well known EOL formats
// (extracted from fgetsline to reuse it on getting file lines)
// These are \n or \r\n
// https://en.wikipedia.org/wiki/Newline
void remove_eol(char *s){
    s[strcspn(s, "\r\n")] = 0;
}

void fgetsline(char *s, int size)
{
    fgets(s, size, stdin);
    remove_eol(s);
}

int main()
{
    // Note : do not use global variables
    FILE *ptr,*bilan;
    // Note : no need for date_line[100]
    char date[100], line[100], carbs_transition[10], prot_transition[10], fat_transition[10];
    int i, proteins, carbs, fats, calories, j = 1, u, m, sommefat = 0, sommeprot = 0, sommecarbs = 0;
    char test[100];
    // Note: this was 20 (too short for : Wed Jul 01 22:09:10 2020)
    fgetsline(date, 100);
    ptr = fopen("daily-intake.txt", "r+");
    fgets(line, 100, ptr);
    printf("%s\n", line);
    while (fgets(line, 100, ptr) != NULL)
    {
        // Note remove eol
        remove_eol(line);
        if (strcmp(date, line) == 0)
        {
            fgets(line, 100, ptr);

            for (i = 0;; i++)
            {
                if (line[i] == '=')
                    break;
            }
            for (j = i + 1, i = 0;; j++, i++)
            {
                if (line[j] == ' ')
                    break;
                prot_transition[i] = line[j];
            }
            prot_transition[i] = '\0';

            for (u = j + 9, i = 0;; u++, i++)
            {
                if (line[u] == ' ')
                    break;
                carbs_transition[i] = line[u];
            }
            carbs_transition[i] = '\0';

            for (m = u + 8, i = 0;; m++, i++)
            {
                if (line[m] == ' ')
                    break;
                fat_transition[i] = line[m];
            }
            fat_transition[i] = '\0';

            printf("prot: %s carbs: %s fat : %s\n", prot_transition, carbs_transition, fat_transition);
            sommeprot = sommeprot + strtol(prot_transition, NULL, 10);
            sommefat = sommefat + strtol(fat_transition, NULL, 10);
            sommecarbs = sommecarbs + strtol(carbs_transition, NULL, 10);
        } else {
            // Note : Why breaking here ?
            // break;

        }
    }
    printf("le %s vous avez manger %d de proteins, %d carbs, %d de fats et %d calories", date, sommeprot, sommecarbs, sommefat, 4 * sommecarbs + 4 * sommeprot + 9 * sommefat);
    fclose(ptr);
    printf("\n le %s vous avez manger %d de proteins, %d carbs, %d de fats et %d calories", date, sommeprot, sommecarbs, sommefat, 4 * sommecarbs + 4 * sommeprot + 9 * sommefat);
    bilan = fopen("bilan.txt", "w");
    fprintf(bilan, "bilan du %s\nproteins=%d/carbs=%d/fats=%d/calories=%d/\n", date, sommeprot, sommecarbs, sommefat, 4 * sommecarbs + 4 * sommeprot + 9 * sommefat);
    fclose(bilan);

    return (0);
}
