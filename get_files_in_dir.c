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

#include "dir_content.h"

int get_files_in_dir(char path_name[],char key[])
{
 int v=0;
 struct dirent *rdir=NULL;
 DIR *dirname=NULL;
 char sub_dir_name[MAX_SIZE];
 char full_file_name[MAX_SIZE];
 if((dirname = opendir(path_name))==NULL)
  {
   perror("Error in opening directory");
   return -1;
  }   
 while((rdir = readdir(dirname))!=NULL)
 {
  if((rdir->d_type == DT_DIR && strcmp(rdir->d_name,".")!= 0 && strcmp(rdir->d_name,"..")!= 0))
  {
   strcpy(sub_dir_name,path_name);
   strcat(sub_dir_name,"/");
   strcat(sub_dir_name,rdir->d_name);
   get_files_in_dir(sub_dir_name,key);
  }
  else
  {
    enum file_types file;
    file = get_file_type(path_name,rdir->d_name);
    if(choice == 3 && file == AUDIO_FILE)
    {
     sprintf(full_file_name,"%s/%s",path_name,rdir->d_name);
     if(strcasestr(rdir->d_name,key))
      {
       printf("%s\n",full_file_name);
       fflush(NULL);
      }
     else
     {
      extract_metadata(full_file_name);
      v = meta_search("/tmp/temp_file.txt",key);
      if(v == 1)
       {
        printf("%s\n",full_file_name);
        fflush(NULL);
        retVal3=1;
       }
     }
    }
    else if(choice !=3 && file == TEXT_FILE)
     {
       if((choice == 1 && (strstr(rdir->d_name,".c")||strstr(rdir->d_name,".h"))) || choice == 2)
       {
        sprintf(full_file_name,"%s/%s",path_name,rdir->d_name);
    again:   
        if(a == 1)
  	  {
   		strcpy(thread1FName,full_file_name);
   		a=0;
   		full_file_name[0]='\0';
  	  }
  	else if(b == 1)
  	  {
   		strcpy(thread2FName,full_file_name);
   		b=0;
   		full_file_name[0]='\0';
  	  }      
  	if(full_file_name[0] != '\0')
  	  goto again;
  	}
     }
   }   
 }
 
 closedir(dirname);
 return 0;
}
