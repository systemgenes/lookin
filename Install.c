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
#include<dirent.h>
#include<stdlib.h>
int main()
{
 int flag=0,ret;
 char choice;
 struct dirent *rdir=NULL;
 DIR *dirname=NULL;
 if((dirname = opendir("/bin"))==NULL)
  {
   perror("Error in opening directory");
   return -1;
  }   
 while((rdir = readdir(dirname))!=NULL)
 {
  if((rdir->d_type != DT_DIR) && strcmp(rdir->d_name,"lookin")==0)
  {
   printf("This application is already installed. Do you want to uninstall it?<y or n> :");
   repeat:
   scanf("%c",&choice);
   if(choice == 'y')
   {
    ret=system("rm /bin/lookin");
    if(ret==0)
    printf("Uninstalled Successfully!!\n");
    else
    {
     printf("Try as root.\n");
     return -1;
    }
   }
   else if( choice == 'n')
   {
    return 0;
   }
   else
   {
    printf("<Enter 'y' for yes and 'n' for no> : ");
    goto repeat;
   }
   flag=1;
   break;
  }
 }
 if(flag == 0)
 {
  if ((system("cp \"./lookin\" /bin") == 0) && (system("chmod 777 /bin/lookin") == 0))
  {
   printf("Installed Successfully!!\n");
  }
  else
  {
   printf("Try installing as root.\n");
   return -1;
  }
 }
}
