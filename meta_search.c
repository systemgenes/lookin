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
#include<string.h>
/*void meta_search(char f[50],char str[40]);
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
int meta_search(char f[50],char str[40])
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
        fclose(fp);
        return 1;
      }
    }
   fclose(fp);
   return 0;
}
