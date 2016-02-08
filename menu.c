// This is the main program which will start when the lookin software starts.
// This opens up the ncurses menu window to give the user options.
   
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

#include <curses.h>
#include <menu.h>
#include <malloc.h>
#include <string.h>
#include<stdlib.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
char p_name[1024],k_word[1024];
char *choices[] = {
			"Identifier Searching",
			"Freetext Searching",
			"Metadata Searching",
		  };
char *description[] = {
			"<Search C Program files>",
			"<General Freetext Search>",
			"<Music File Search>",
		      };

void func(char *name);

int main(int argc,char *argv[])
{
   int c=0;
  ITEM **my_items;
  ITEM *cur;
  MENU *my_menu;
  int n_choices, i;
  ITEM *cur_item;
  
  if(argc !=3) 
   {	      // this is used because our program will need two arguments (path name and keyword to search) 
    printf("\nUsage:  %s <Path Name> <Keyword>\n",argv[0]);
    printf("Please provide the path name and keyword to search!!\n");
    exit(-1);
   }
  strcpy(p_name,argv[1]);
  strcpy(k_word,argv[2]);
  /* Initialize curses */
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
  /* Initialize items */
  n_choices = ARRAY_SIZE(choices);
  my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
  for(i = 0; i < n_choices; ++i)
   {
    my_items[i] = new_item(choices[i], description[i]);   //new_item("item_name","description");
    /* Set the user pointer */
    //set_item_userptr(my_items[i], func);
   }
  
  my_items[n_choices] = (ITEM *)NULL;
  /* Create menu */
  my_menu = new_menu((ITEM **)my_items);
  /* Post the menu */
  mvprintw(LINES-3,0,"Press <ENTER> to select the option");
  mvprintw(LINES-2,0,"Up and Down arrow keys to navigate <F2 to Exit>");
  post_menu(my_menu);
  refresh();
  while((c = getch()) != KEY_F(2))
   {
    switch(c)
     {
      case KEY_DOWN:
           menu_driver(my_menu, REQ_DOWN_ITEM);
           break;
      case KEY_UP:
           menu_driver(my_menu, REQ_UP_ITEM);
           break;
      case 10: /* Enter */
           {
            cur = current_item(my_menu);
            func((char*)item_name(cur));
            pos_menu_cursor(my_menu);
            break;
           }
           break;
     }
   }
  unpost_menu(my_menu);
  for(i = 0; i < n_choices; ++i)
    free_item(my_items[i]);
  free_menu(my_menu);
  endwin();
}

void func(char *name)
{
 def_prog_mode(); /*saving the ncurses mode so as to return to terminal*/
 endwin();
 if(!strcmp(name,"Identifier Searching"))
 {
  main_thread(1,p_name,k_word);
  getch();
 }
 if(!strcmp(name,"Freetext Searching"))
 {
  main_thread(2,p_name,k_word);
  getch();
 }
 if(!strcmp(name,"Metadata Searching"))
 {
  main_thread(3,p_name,k_word);
  getch();
 }
 reset_prog_mode();/*return to ncurses mode*/
 refresh();
}
