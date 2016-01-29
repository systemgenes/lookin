#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<stdlib.h>    //exit()
#include<string.h>

#define MAX_SIZE 1024

char thread1FName[MAX_SIZE], thread2FName[MAX_SIZE];
char key[128];
int a=1,b=1,signal=1,choice=0,retVal1=0,retVal2=0;

#include "get_files_in_dir.c"

int get_files_in_dir(char [],char []);

void *thread1(void *arg)
{

 while(signal)
 {
  if(a == 0)// thread1 is busy
  {
   if(choice==1)
     retVal1 = (retVal1|id_search(thread1FName,key));
   else if(choice==2)
     retVal1 = (retVal1|search(thread1FName,key));  
   a=1;
  }
 }
 pthread_exit((void*)1);
}

void *thread2(void *arg)
{
 while(signal)
 {
  if(b == 0)// thread2 is busy
  {
   if(choice==1)
     retVal2 =(retVal2|id_search(thread2FName,key));
   else if(choice==2)
     retVal2 = (retVal2|search(thread2FName,key));
   b=1;
  }
 }
 pthread_exit((void*)2);
}

int main(int argc,char * argv[])
{
 pthread_t t1,t2;
 int val1=1,val2=2;
 int * retptr;
 char path_name[MAX_SIZE];
 if(argc !=3) 
 {	      /* this is used because our program will need two arguments (path name and keyword to search) */
    printf("\nUsage:  %s <Path Name> <Keyword>\n",argv[0]);
    printf("Please provide the path name and keyword to search!!\n");
    exit(-1);
  }
 printf("\nSelect : 1-Identifier Search , 2-Freetext Search\n");
 scanf("%d",&choice);
 strcpy(path_name,argv[1]);
 strcpy(key,argv[2]);
 printf("\n\t-----------------------------------------------\n\n");
 pthread_create(&t1,NULL,thread1,&val1);
 pthread_create(&t2,NULL,thread2,&val2);
 
 get_files_in_dir(path_name,key);
 signal=0;
 pthread_join(t1,(void**)&retptr);
 //printf("Thread 1 returned %d\n",(int)retptr);
 pthread_join(t2,(void**)&retptr);
 //printf("Thread 2 returned %d\n",(int)retptr);
 if(!(retVal1|retVal2))
    printf("Keyword Not Found!!\n");
 return 0;
}
