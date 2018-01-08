//-----------------Ncurses Header---------------------------------
#include <ncurses.h>
#include <form.h>
#include <menu.h>
//---------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// -----------------NETWORK HEADDER-------------------------------
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
//-----------------------------------------------------------------
#define MAX_ARR_SIZE 2000
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
//----------------------색갈표------------------------------------
//RAGNE 0~15까지만!!!!
//9빨강 10 녹색 8 회색 7 
#define BRIGHT_WHITE 15
#define BRIGHT_BLUE 12
#define BRIGHT_YELLOW 7
#define SKY_BLUE	14
//----------------------------------------------------------------
#define PAIR_BLACK_WHITE	1
#define PAIR_WHITE_BLACK	2
#define PAIR_RED_BLUE		3
#define PAIR_WHITE_BLUE		4
#define PAIR_RED_YELLOW		5
//필요한 함수선언-------------------------------------------------------------
WINDOW *create_newwin(int TITLE_HEIGHT, int TITLE_WIDTH, int starty, int startx);
void destroy_win(WINDOW *local_win);
int System_Command(char* Command_in , char Data_out[]);
void Color_Setting(void);
void Init_Program(void);
void create_newslectwin(WINDOW* SLECT_W,char* choices[],int SLECT_WIDTH, int SLECT_HEIGHT, int x, int y, char SLECT_DATA[]);
//------------------------------------------------------------------------------

int Key_IN;

int main(int argc, char* argv[])
{	
Init_Program();
//-------------------------------------------------------------------------------------------
int BG_HEIGHT= LINES ;
int BG_WIDTH = COLS ;
int BG_POS_X = 0;
int BG_POS_Y = 1;
int TITLE_HEIGHT= 2;
int TITLE_WIDTH = COLS;
int TITLE_POS_X = 0; 
int TITLE_POS_Y = 1; 
int AREA_1_HEIGHT= 30;
int AREA_1_WIDTH =(COLS*1)/4;
int AREA_1_POS_X = 1; 
int AREA_1_POS_Y = 7*(LINES/30);
int AREA_2_HEIGHT= 30;
int AREA_2_WIDTH =(COLS*1)/4;
int AREA_2_POS_X = (COLS - AREA_2_WIDTH - 1); //제 목은 중간 에 출력
int AREA_2_POS_Y = 7*(LINES/30); // 출력할 높이는 화면을 30으로 나눈 첫번째 영역에 출력
int AREA_3_HEIGHT= 30;
int AREA_3_WIDTH =(COLS - AREA_2_WIDTH - AREA_1_WIDTH )-4;
int AREA_3_POS_X = (COLS - AREA_3_WIDTH)/2; //제 목은 중간 에 출력
int AREA_3_POS_Y = 7*(LINES/30); // 출력할 높이는 화면을 30으로 나눈 첫번째 영역에 출력
int AREA_4_HEIGHT= 10;
int AREA_4_WIDTH =(COLS*3)/4-3;
int AREA_4_POS_X = (COLS -AREA_3_WIDTH)/2; 
int AREA_4_POS_Y = LINES - AREA_4_HEIGHT -1; // 출력할 높이는 화면을 30으로 나눈 첫번째 영역에 출력
int SLECT_HEIGHT = 10;
int SLECT_WIDTH = (COLS)/4;
int SLECT_POS_X = 1; 
int SLECT_POS_Y = LINES - SLECT_HEIGHT - 1; 
//-----------------------------------------------------------------------------------------------
char UPTOP_MESSEAGE[MAX_ARR_SIZE]="Press Q to Quit";
char TITLE_STRING[MAX_ARR_SIZE]="PUT TITLE HERE";	
char AREA_1_DATA[MAX_ARR_SIZE]="example";
char Data_1[MAX_ARR_SIZE];
char Data_2[MAX_ARR_SIZE];
char Data_3[MAX_ARR_SIZE];
char Data_4[MAX_ARR_SIZE];
char SLECT_DATA[MAX_ARR_SIZE]="SELECT OPTION";
//--------------------------------Slection Menu----------선택메뉴만--------------------------------------
char *choices[] = {
                        "Sytem Status           ",
                        "Choise 2               ",
                        "Choice 3               ",
                        "Choice 4               ",
                        "Choise 5               ",
			"Choise 6               ",
			"Choise 7               "
                 };
	
//-----------------------------------------------------------------------------------------------------	
WINDOW* BG;	
WINDOW* Title_Win;
WINDOW* AREA_1;
WINDOW* AREA_2;
WINDOW* AREA_3;
WINDOW* AREA_4;	
WINDOW* SLECT_W;
	
//-----------------------------------------------------------------------------------------------------	
BG=create_newwin(BG_HEIGHT,BG_WIDTH,BG_POS_Y,BG_POS_X);
Title_Win=create_newwin(TITLE_HEIGHT,TITLE_WIDTH,TITLE_POS_Y,TITLE_POS_X);
AREA_1=create_newwin(AREA_1_HEIGHT,AREA_1_WIDTH,AREA_1_POS_Y,AREA_1_POS_X);
AREA_2=create_newwin(AREA_2_HEIGHT,AREA_2_WIDTH,AREA_2_POS_Y,AREA_2_POS_X);	
AREA_3=create_newwin(AREA_3_HEIGHT,AREA_3_WIDTH,AREA_3_POS_Y,AREA_3_POS_X);
AREA_4=create_newwin(AREA_4_HEIGHT,AREA_4_WIDTH,AREA_4_POS_Y,AREA_4_POS_X);
SLECT_W = create_newwin(SLECT_HEIGHT,SLECT_WIDTH,SLECT_POS_Y,SLECT_POS_X);
	
//-------------------------------------배경--------------색-----------------------------------------------
bkgd(COLOR_PAIR(PAIR_RED_YELLOW));	
wbkgd(BG,COLOR_PAIR(PAIR_WHITE_BLUE));  //배경색갈 지정 PAIR_(**)를 위에 #define 보면서 변경가능	
wbkgd(Title_Win,COLOR_PAIR(PAIR_WHITE_BLACK));
wbkgd(AREA_1,COLOR_PAIR(PAIR_WHITE_BLACK));
wbkgd(AREA_2,COLOR_PAIR(PAIR_WHITE_BLACK));	
wbkgd(AREA_3,COLOR_PAIR(PAIR_WHITE_BLACK));
wbkgd(AREA_4,COLOR_PAIR(PAIR_WHITE_BLACK));
wbkgd(SLECT_W,COLOR_PAIR(PAIR_BLACK_WHITE));
	
//--------------------------------------------------------------------------
keypad(SLECT_W, TRUE);
keypad(Title_Win, TRUE);
keypad(AREA_1, TRUE);
keypad(AREA_2, TRUE);
keypad(AREA_3, TRUE);
keypad(AREA_4, TRUE);
	
//-----------------------------------------------------------------------------------------	
	
refresh();	
wrefresh(BG);	
wrefresh(Title_Win);
wrefresh(AREA_1);
wrefresh(AREA_2);
wrefresh(AREA_3);
wrefresh(AREA_4);	
	

printw(UPTOP_MESSEAGE);
mvwprintw(Title_Win,1,(TITLE_WIDTH - strlen(TITLE_STRING))/2,"%s",TITLE_STRING);
//------------------------------------영역 1---------------------------------------------------------
mvwprintw(AREA_1,0,0,AREA_1_DATA);
//------------------------------------영역 2-------------------------------------------------------
System_Command("ls /etc",Data_2);
mvwprintw(AREA_2,0,0,Data_2);
//------------------------------------영역 3-------------------------------------------------------
System_Command("df -h",Data_3);
mvwprintw(AREA_3,0,0,Data_3);

//------------------------------------영역 4-------------------------------------------------------
System_Command("du -h",Data_4);
mvwprintw(AREA_4,0,0,Data_4);

//----------------------------------선택 메뉴 -영역4---------------------------------------------------------

create_newslectwin(SLECT_W,choices,SLECT_WIDTH,SLECT_HEIGHT, 0, 0,SLECT_DATA);	
	
	/*
ITEM **TABLE;
int Key_IN;
MENU *Menu;
int n_choices, i;
ITEM *Current_Slected;
//아이템 생성----------

n_choices = ARRAY_SIZE(choices);
TABLE = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
	for(i = 0; i < n_choices; ++i)
	        TABLE[i] = new_item(choices[i], choices[i]);
	TABLE[n_choices] = (ITEM *)NULL;
//메뉴 생성-----------
	Menu = new_menu((ITEM **)TABLE);

set_menu_win(Menu,SLECT_W);
set_menu_sub(Menu, derwin(SLECT_W, n_choices,SLECT_WIDTH,SLECT_HEIGHT - n_choices,0)); //(상자크기(y,x 위치 y,x)
set_menu_mark(Menu, ">");
wattron(SLECT_W,COLOR_PAIR(PAIR_RED_BLUE));
//box(SLECT_W, 0, 0);
mvwprintw(SLECT_W,1,(SLECT_WIDTH - strlen(SLECT_DATA))/2, SLECT_DATA);
//mvwaddch(SLECT_W, 2, 0, ACS_LTEE);
//mvwhline(SLECT_W, 2, 1, ACS_HLINE, 38);
//mvwaddch(SLECT_W, 2, 39, ACS_RTEE);
refresh();
wattroff(SLECT_W,COLOR_PAIR(PAIR_RED_BLUE));
post_menu(Menu);
refresh();
wrefresh(SLECT_W);
*/

//---------------------------------------------------------------------------------------------------
while((Key_IN = getch()) != 'q')
   // while((Key_IN = getch()) != KEY_F(1))
    {   switch(Key_IN)
        {   case KEY_DOWN:
                    menu_driver(Menu, REQ_DOWN_ITEM);
                            break;
                    case KEY_UP:
                            menu_driver(Menu, REQ_UP_ITEM);
                            break;
            }
     	refresh();	
	wrefresh(BG);	
	wrefresh(Title_Win);
	wrefresh(AREA_1);
	wrefresh(AREA_2);
	wrefresh(AREA_3);
	wrefresh(AREA_4);	
	wrefresh(SLECT_W);
    }


//----------------종료시-------------------------------------------------------

	//free_item(TABLE[0]);
	//free_item(TABLE[1]);
	//free_menu(Menu);
	endwin();
	return 0;
}



WINDOW *create_newwin(int TITLE_HEIGHT, int TITLE_WIDTH, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(TITLE_HEIGHT, TITLE_WIDTH, starty, startx);
//	box(local_win, 0 , 0);
	wrefresh(local_win);

	return local_win;
}


void destroy_win(WINDOW *local_win)
{
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}


int System_Command(char* Command_in, char Data_out[])
{
FILE *fp;
char path[MAX_ARR_SIZE];
memset(path,0,sizeof(path));
int c=-1;
int i=0;


  /* Open the command for reading. */
  fp = popen(Command_in, "r");
  if (fp == NULL)
 {
    return -1;
  }
 
  while(c != 0)
 {
	c=fgetc(fp);
	if(c == EOF || i >= (MAX_ARR_SIZE-1))
	{
		c=0;
	}
	path[i++]=c;
 }

 
strcpy(Data_out,path);
  /* close */
  pclose(fp);
return 0;

}



void Color_Setting(void)
{

	
	
//-----------------흰색 글자 검정 파탕---------------------------------------------

		if(can_change_color() && COLORS >= 16)
			{
				init_color(BRIGHT_WHITE, 1000,1000,1000);
			}
		if(COLORS >=16)
			{
				init_pair(PAIR_BLACK_WHITE, COLOR_BLACK, BRIGHT_WHITE);
			}
		else
			{
				init_pair(PAIR_BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);
			}
//-----------------글자흰색  배경파랑색  생성-------------------------------------------
	    if(can_change_color() && COLORS >= 16 )
	             {
        	            init_color(BRIGHT_BLUE, 100,100,1000);
        	     }
   		 if(COLORS >=16)
           		 {
                  		 init_pair(PAIR_WHITE_BLUE, BRIGHT_WHITE, BRIGHT_BLUE);
           		  }
   		 else
             		 {
                	    init_pair(PAIR_WHITE_BLUE, COLOR_WHITE, COLOR_BLUE);
            		 }
//-------------------하늘색 생성------------------------------------------


	 if(can_change_color() && COLORS >= 16 )
        	  {
        	         init_color(SKY_BLUE, 100,100,1000);
       		   }
     	 if(COLORS >=16)
              {
                      init_pair(PAIR_RED_BLUE, COLOR_RED, SKY_BLUE);
               }
    	  else
              {
                 init_pair(PAIR_RED_BLUE, COLOR_RED, COLOR_BLUE);
		}

//--------------------배경검은색글자흰색--------------------------------------------------


  if(can_change_color() && COLORS >= 16 )
           {
                  init_color(SKY_BLUE, 100,100,1000);
            }
  if(COLORS >=16)
       {
               init_pair(PAIR_WHITE_BLACK, BRIGHT_WHITE, COLOR_BLACK);
        }
   else
       {
          init_pair(PAIR_WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
         }

//--------------------노랑빨강--------------------------------------------------


  if(can_change_color() && COLORS >= 16 )
           {
                  init_color(BRIGHT_YELLOW, 1000,1000,1000);
            }
  if(COLORS >=16)
       {
               init_pair(PAIR_RED_YELLOW, COLOR_RED, BRIGHT_YELLOW);
        }
   else
       {
          init_pair(PAIR_RED_YELLOW, COLOR_RED, COLOR_YELLOW);
         }

	
}


void Init_Program(void)
{
// INTITIALIZATION
initscr(); //이걸 활성화시켜야지 그래픽 모드 작동댐
raw();	//사용자가 엔터키를 안눌러도 글자 전달댐
keypad(stdscr, TRUE); //특수키를 입력 받을지의 여부, ex F1,F2~F12같은 거
noecho(); //사용자가 입력해도 화면에, 지저분하게 뜨지 않음
//cbreak();
refresh(); //반드시 해야함 LINES, COLS을 업데이트 함
start_color();// 색갈을 사용함
Color_Setting();	
}

void create_newslectwin(WINDOW* SLECT_W,char* choices[],int SLECT_WIDTH, int SLECT_HEIGHT, int x, int y, char SLECT_DATA[])
{
	
ITEM **TABLE;
MENU *Menu;
int n_choices, i;
ITEM *Current_Slected;
//아이템 생성----------

n_choices = ARRAY_SIZE(choices);
TABLE = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
	for(i = 0; i < n_choices; ++i)
	        TABLE[i] = new_item(choices[i], choices[i]);
	TABLE[n_choices] = (ITEM *)NULL;
//메뉴 생성-----------
	Menu = new_menu((ITEM **)TABLE);

set_menu_win(Menu,SLECT_W);
set_menu_sub(Menu, derwin(SLECT_W, n_choices,SLECT_WIDTH,SLECT_HEIGHT - n_choices,0)); //(상자크기(y,x 위치 y,x)
set_menu_mark(Menu, ">");
wattron(SLECT_W,COLOR_PAIR(PAIR_RED_BLUE));
//box(SLECT_W, 0, 0);
mvwprintw(SLECT_W,1,(SLECT_WIDTH - strlen(SLECT_DATA))/2, SLECT_DATA);
//mvwaddch(SLECT_W, 2, 0, ACS_LTEE);
//mvwhline(SLECT_W, 2, 1, ACS_HLINE, 38);
//mvwaddch(SLECT_W, 2, 39, ACS_RTEE);
refresh();
wattroff(SLECT_W,COLOR_PAIR(PAIR_RED_BLUE));
post_menu(Menu);
refresh();
wrefresh(SLECT_W);
	
}
