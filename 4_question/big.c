#include<stdio.h>
#include<stdlib.h>
#include<string.h>
  FILE *ptr,*bilan;
void fgetsline(char *s, int size)
{
    fgets(s, size, stdin);

    int len = strlen(s);
    if (s[len - 1] == '\n')
       s[len - 1] = '\0';
}
int main()
{
  // FILE *ptr,*bilan;
   char date[100],line[100],date_line[100],carbs_transition[10],prot_transition[10],fat_transition[10];
   int i,proteins,carbs,fats,calories,j=1,u,m,sommefat=0,sommeprot=0,sommecarbs=0;
   char test[100];
fgetsline(date,20);
ptr=fopen("daily intake.txt","r+");
fgets(line,100,ptr);
printf("%s\n",line);
    while(fgets(line,100,ptr)!=NULL)
    {
            for(i=0;i<=9;i++)
            {   date_line[i]=line[i];
            }
           // date_line[i]='\0';
            printf("date corrupted :%s",date_line);
            if (strcmp(date,date_line)==0)
        {   //  printf("after while :%s\n",line);
            fgets(line,100,ptr);

            for(i=0;;i++)
            {
                if(line[i]=='=')
                    break;
            }
            for(j=i+1,i=0;;j++,i++)
            {if(line[j]==' ')
                break;
                prot_transition[i]=line[j];
            }
            prot_transition[i]='\0';


              for(u=j+9,i=0;;u++,i++)
        {   if(line[u]==' ')
                break;
            carbs_transition[i]=line[u];
        }
        carbs_transition[i]='\0';

        for(m=u+8,i=0;;m++,i++)
        {   if(line[m]==' ')
            break;
            fat_transition[i]=line[m];
        }
        fat_transition[i]='\0';

        printf("prot: %s carbs: %s fat : %s\n",prot_transition,carbs_transition,fat_transition);
        sommeprot=sommecarbs+strtol(prot_transition, NULL, 10);
        sommefat=sommefat+strtol(fat_transition, NULL, 10);
        sommecarbs=sommecarbs+ strtol(carbs_transition, NULL, 10);
        }
            else
            break;
}
printf("le %s vous avez manger %d de proteins, %d carbs, %d de fats et %d calories",date,sommeprot,sommecarbs,sommefat,4*sommecarbs+4*sommeprot+9*sommefat);
fclose(ptr);
printf("\n le %s vous avez manger %d de proteins, %d carbs, %d de fats et %d calories",date,sommeprot,sommecarbs,sommefat,4*sommecarbs+4*sommeprot+9*sommefat);
bilan=fopen("bilan.txt","w");
      fprintf(bilan,"bilan du %s\nproteins=%d/carbs=%d/fats=%d/calories=%d/\n",date,sommeprot,sommecarbs,sommefat,4*sommecarbs+4*sommeprot+9*sommefat);
fclose(bilan);

return(0);
}





