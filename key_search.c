#include<stdio.h>
#include<string.h>
/*void search(char f[50],char str[40]);
void main()
{
  char f[50],str[40];
  printf("enter the filename");
  scanf("%s",f);
  printf("enter the string");
  scanf("%s",str);
  search(f,str);
}
*/
int search(char f[50],char str[40])
{
 FILE*fp;
 fp=fopen(f,"r");
 if(fp == NULL)
    return;
 int count=1,flag=0;
 char ch;
 char* str1 = str;
 while((ch=fgetc(fp))!=EOF)
   {
    if(*str1!='\0')
      {
        if(ch == *str1)
           str1++;
        else
           str1=str;
      }
    else
      {
        flag = 1;
        printf("%s : keyword found at Line %d\n",f,count);
        str1=str;
      }
     if(ch=='\n')
       {
        count++;
       }
    }
   fclose(fp);
   return(flag);
}
