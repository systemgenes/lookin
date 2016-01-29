
#include<stdio.h>
#include<string.h>
#include "dir_content.h"

#define MAX_SIZE 1024

enum file_types get_file_type(char path[],char file_name[])
{
    char temp[MAX_SIZE];
    sprintf(temp, "file \"%s/%s\"",path,file_name);
    FILE *file_p = popen(temp, "r");
    if (!file_p)
    {
     perror("popen :");
     return -1;
    }
    char buffer[MAX_SIZE];
   fgets(buffer, sizeof(buffer), file_p);
    pclose(file_p);
    
    if(strstr(buffer,"ASCII") || strstr(buffer,"text"))
    	return TEXT_FILE;
    else
    	return OTHER;
}
