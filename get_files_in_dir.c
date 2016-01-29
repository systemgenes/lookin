#include "dir_content.h"

int get_files_in_dir(char path_name[],char key[])
{
 struct dirent *rdir;
 char sub_dir_name[MAX_SIZE];
 char full_file_name[MAX_SIZE];
 DIR *dirname;
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
    if(file == TEXT_FILE)
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
 
 closedir(dirname);
 return 0;
}
