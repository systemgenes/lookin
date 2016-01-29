#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char reserve_keys[][12]={
"auto","double","if","static","break","else","int","struct","case","enum","long","switch","char","extern","near","typedef","const","float",
"register","union","continue","far","return","unsigned","default","for","short","void","do","goto","signed","while"
};

int check(char ch)
{
 if(ch==EOF)
  return 0;
 else if(ch=='\n')
  return 1;
 else
  return 0;
}
int reserve_key(char * reserve)
{
 int i=0,flag=0;
 for(i=0;i<32;i++)
 {
  if(strcmp(reserve,reserve_keys[i]) == 0)
   {
    flag=1;
    break;
   }
 }
 if(flag == 1)
  return 1;
 return 0;
}
int id_search(char f[1024],char str[128])
{
 FILE*fp,*temp,*temp1;
 int flag=0;
 fp=fopen(f,"r");
 if(fp == NULL)
   {
     printf("Error opening file: No such file.\n");
     exit(0);
   }
int count=1;
int len=0;
char ch,next_ch;
char* str1 = str;
while((ch=fgetc(fp))!=EOF)
 {
  if(ch == '"')
   { 
     while((ch=fgetc(fp))!='"');
     ch=fgetc(fp);
     count=count+check(ch);
   }
  /* 
  if(ch == '/')
  {
   ch = fgetc(fp);
   if(ch == '/')
   {
     while((ch=fgetc(fp)!='\n'));
     count++;
   }
   else if(ch == '*')
   {
    while(1)
     {
      ch=fgetc(fp);
      count=count+check(ch);
      if(ch== '*')
      {
        ch=fgetc(fp);
        count=count+check(ch);
        if(ch=='/')
        break;
      }   
     }
   }
  }*/
  if(*str1!='\0')
    {
        if(ch == *str1)
          {
             str1++;
          }
        else
          {
             str1=str;
          }
    }
  else
    {
        temp = fp;
        len=strlen(str);
        fseek(fp,-(len+2),SEEK_CUR);
        next_ch = fgetc(fp);
        count=count+check(next_ch);
        fseek(fp,len,SEEK_CUR);
       
        if(!(!(next_ch >= 'A' && next_ch <= 'Z') && !(next_ch >= 'a' && next_ch <= 'z' ) && !(next_ch >= '0' && next_ch <= '9') && next_ch != '_'))
          {
             //This condition ensures that there is no alphabet or digit before this keyword.
             next_ch=ch;
          }
          
        else if(!(!(ch >= 'A' && ch <= 'Z') && !(ch >= 'a' && ch <= 'z' ) && !(ch >= '0' && ch <= '9') && ch != '_'))
          {
             //This condition ensures that there is no alphabet or digit after this keyword.
             next_ch=ch;
          }
        
        else
          {
             if(reserve_key(str))
    	       {
    	           printf("%s : reserved keyword \"%s\" used at line %d\n",f,str,count);
    	           str1 = str;
    	           flag=1;
    	           goto last_statement;
    	       }
             next_ch=ch;
             while(next_ch == ' ')
               { 
                   next_ch=fgetc(temp);
                   count=count+check(next_ch);
               }
             if(next_ch =='(')
               {
                   next_ch=fgetc(temp);
                   count=count+check(next_ch);
                   while(next_ch!=')')
                     {
                         next_ch = fgetc(temp);
                     }
                   next_ch=fgetc(temp);
                   while(next_ch == ' ' || next_ch == '\n')
                     {
                         next_ch= fgetc(temp);
                     }
                   if(next_ch == ';')
                     {
                         printf("%s : function used at line no. %d\n",f,count);
                         flag = 1;
                     }
                   else if(next_ch == '{')
                     {
                         printf("%s : function definition at line no. %d\n",f,count);
                         flag = 1;
                     }
               }
             else if(!(next_ch >= 'A' && next_ch <= 'Z') || !(next_ch >= 'a' && next_ch <= 'z' ) || !(next_ch >= '0' && next_ch <= '9'))
               {
                   printf("%s : variable used at line no. %d\n",f,count);
                   flag = 1;
               }
          }
          
        str1 = str;
    }
last_statement:
   if(ch=='\n')
   {
    count++;
   }
 }
exit:
 fclose(fp);
 return(flag); 
}
