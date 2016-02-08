// Copyright (C) 2016 Ravi Kant Pandey
// Mail at systemgenes@gmail.com for any queries.

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
#include<string.h>
#include "dir_content.h"

#define MAX_SIZE 1024

int extract_metadata(char path[])
{
  FILE* fp=NULL;
//  char username[64]=getlogin();
   char directory[] = "/tmp/temp_file.txt";
   fp= fopen(directory ,"w+");
   if(fp==NULL)
   {
    printf("Temporary File location Error.extract_metadata() function\n");
    return -1;
   }
    char temp[MAX_SIZE];
    sprintf(temp, "extract \"%s\" > \"%s\"",path,directory);
        fclose(fp);
    FILE *file_p = popen(temp, "r");
    if (!file_p)
    {
     perror("popen :");
     return -1;
    }
    char buffer[MAX_SIZE];
   fgets(buffer, sizeof(buffer), file_p);
    pclose(file_p);
    //fputs(buffer,fp);
    return 0;
}
