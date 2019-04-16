#include <stdlib.h>			// free
#include <stdio.h> 			// printf
#include <time.h>			// time
#include <conio.h>			// getch 
#include "./lib/lbrnth.h"	// idx, li_solve_maze, build_lbrt,
							// struct maze, struct dot			
#include "./lib/term.h"		// move_cursor, set_attr, color_print, setw_title,
							// setw_hw, hide_cursor, erase_chars, clrscr, gotoxy,
							// save_curs_pos, update_curs_pos

							
void 	print_field 	(struct maze maze);
void 	print_esc_path	(struct maze maze);
void 	update_footer	(struct maze maze);
void 	new_maze		(struct maze * maze);
void 	handle_press 	(char c, struct maze * maze, int * maze_passed);

int main(int argc, char * argv)
{
	setw_hw(FIELD.HEIGHT+1, FIELD.WIDTH*2);
	setw_title("labyrinth");
	hide_cursor();
	
	struct maze maze;
	maze.player.step = 1;
	maze.player.level = 1;
	
	new_maze(&maze);
	print_field(maze);
	
	int maze_passed = 0;
	
	update_footer(maze);
	char c = getch();
	do {
		handle_press(c, &maze, &maze_passed);
		
		if (maze_passed)
		{
			new_maze(&maze);
			print_field(maze);
			maze_passed = 0;
			maze.player.level++;
		}

		update_footer(maze);
		c = getch();
		
	} while(c != 'q');

	free(maze.field);

	return 0;
}


void print_field(struct maze maze) 
{
	int * field = maze.field;
	struct pl curs = maze.player;
	struct dot end = maze.endPoint;
	
	clrscr();
	
	for (int i = 0; i < FIELD.HEIGHT; ++i)
	{
		for (int j = 0; j < FIELD.WIDTH; ++j)
			if (i == curs.y && j == curs.x)
				color_print("  ", B_GREEN);
			else if (i == end.y && j == end.x)
				color_print("  ", B_RED);
			else 
				switch (field[idx(i, j)]) 
				{
					case -1: // WALL
						color_print("  ", B_WHITE); break;
					case 0: // BLANK
						printf("  "); break;
					default: break;
				}
	}
	move_cursor('d', 1);
	gotoxy(2, 1); 
	
}


void handle_press(char c, struct maze * maze, int * maze_passed)
{
	
	int * field = maze->field;
	struct pl * curs = &maze->player;
	struct dot * end = &maze->endPoint;
	
	struct dot prev = {curs->x, curs->y};
	
	struct direct {
		char dir;
		int len;
	} d;

	switch (c)
	{
		case 'e':
			if (!maze->showPath)
			{
				field[idx(curs->y, curs->x)] = ESC_PATH+1;
				li_solve_maze(maze);
				print_esc_path(*maze); 
				maze->showPath++;
			} 
			break;
			
		case 80: 
			if (field[idx(curs->y+1, curs->x)] != WALL)
			{
				curs->y++;
				d.dir = 'd';
				d.len = 1;
			} else if (field[idx(curs->y+1, curs->x)] == WALL) return;
			break;
			
		case 72: 
			if (field[idx(curs->y-1, curs->x)] != WALL)
			{
				curs->y--;
				d.dir = 'u';
				d.len = 1;
			} else if (field[idx(curs->y-1, curs->x)] == WALL) return;
			break;
			
		case 77:
			if (field[idx(curs->y, curs->x+1)] != WALL) 
			{
				curs->x++;
				d.dir = 'r';
				d.len = 2;
			} else if (field[idx(curs->y, curs->x+1)] == WALL) return;
			break;
			
		case 75:
			if (field[idx(curs->y, curs->x-1)] != WALL)  
			{
				curs->x--;
				d.dir = 'l';
				d.len = 2;		
			} else if (field[idx(curs->y, curs->x-1)] == WALL) return;
			break;
			
		default: return; break;
	}
	
	maze->player.step++;

	if (maze->showPath)
	{
		color_print("  ", B_YELLOW);
		move_cursor('l', 2);
	} else erase_chars(2);
	
	if (field[idx(curs->y, curs->x)] == ESC_PATH)
	{
		field[idx(prev.y, prev.x)] = BLANK;
		erase_chars(2);
	} 
	if (maze->showPath) 
		field[idx(curs->y, curs->x)] = ESC_PATH;
	
	move_cursor(d.dir, d.len);
	color_print("  ", B_GREEN);
	move_cursor('l', 2);
	
	if (curs->x == end->x && curs->y == end->y)
		*maze_passed = 1;
}

void print_esc_path(struct maze maze)
{
	save_curs_pos();
	for (int i = 0; i < FIELD.HEIGHT; i++)
		for (int j = 0; j < FIELD.WIDTH; j++)
			if (maze.field[idx(i, j)] == ESC_PATH)
			{
				gotoxy(j*2, i);
				color_print("  ", B_YELLOW);
			}
	update_curs_pos();
}

void new_maze(struct maze * maze)
{
	maze->endPoint.x = FIELD.WIDTH-2;
	maze->endPoint.y = FIELD.HEIGHT-2;
	maze->seed = time(0);
	maze->field = build_lbrt(maze->seed);
	maze->player.x = 1;
	maze->player.y = 1;
	maze->showPath = 0;
}

void update_footer(struct maze maze)
{
	save_curs_pos();
	gotoxy(0, FIELD.HEIGHT);
	printf("seed: %i\tlevel: %i \tstep: %i \tq - quit, e - escape", 
			maze.seed, maze.player.level, maze.player.step);
	update_curs_pos();
}
