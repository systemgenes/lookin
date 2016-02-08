// Copyright (C) 2016 Ravi Kant Pandey

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<stdlib.h>    //exit()
#include<string.h>

#define MAX_SIZE 1024

char thread1FName[MAX_SIZE],thread2FName[MAX_SIZE];
char key[128];
int a=1,b=1,signal=1,choice=0,retVal1=0,retVal2=0,retVal3=0;

#include "get_files_in_dir.c"

int get_files_in_dir(char [],char []);

void *thread1(void *arg)
{
 if(choice!=3)
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
 if(choice!=3)
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

int main_thread(int ch,char * argv1,char* argv2)
{
 pthread_t t1,t2;
 a=1;b=1;signal=1;choice=0;retVal1=0;retVal2=0;retVal3=0;
 int val1=1,val2=2;
 int * retptr;
 choice=ch;
 char path_name[MAX_SIZE];
 strcpy(path_name,argv1);
 strcpy(key,argv2);
 printf("\n\t-----------------------------------------------\n\n");
 fflush(NULL);
 pthread_create(&t1,NULL,thread1,&val1);
 pthread_create(&t2,NULL,thread2,&val2);
 get_files_in_dir(path_name,key);
 signal=0;
 pthread_join(t1,(void**)&retptr);
 pthread_join(t2,(void**)&retptr);
 if(!(retVal1|retVal2|retVal3))
    printf("Keyword Not Found! <Press ENTER to return to main menu>");
 else
    printf("\n*--------*Search Finished!*--------*\n<Press ENTER to return to main menu>");
 return 0;
}
