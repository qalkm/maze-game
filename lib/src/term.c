#include <stdio.h> 	// printf
#include <stdlib.h> 	// system
#include "../term.h"	//

#define ESC "\033"

void move_cursor(char direction, int lenght)
{
	switch (direction)
	{
		case 'u':
			printf(ESC "[%dA", lenght); break;
		case 'd':
			printf(ESC "[%dB", lenght); break;
		case 'l':
			printf(ESC "[%dD", lenght); break;
		case 'r':
			printf(ESC "[%dC", lenght); break;
		default: break;
	}
}

void setw_hw(int height, int width)
{
	char cmd[64];
	sprintf(cmd, "mode con: lines=%i cols=%i", height, width);
	system(cmd);
}

void setw_title(char * title)
{
	printf(ESC "]0;%s\x07", title);
}

void color_print(char * text, int color)
{
	set_attr(color);
	printf(text);
	set_attr(0);
}

void gotoxy(int x, int y)
{
	printf(ESC "[%d;%dH", y+1, x+1); 
}

void erase_chars(int count)
{
	printf(ESC "[%dX", count);
}

void clrscr(void)
{
	printf(ESC "[2J");
}

void set_attr(int attr)
{
	printf(ESC "[%dm", attr);
}

void hide_cursor(void) 
{
	printf(ESC "[?25l");
}

void save_curs_pos()
{
	printf(ESC "[s");
}

void update_curs_pos()
{
	printf(ESC "[u");
}
