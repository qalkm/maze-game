#include <strings.h> 	// memcpy
#include <stdio.h>	// printf
#include <stdlib.h> 	// rand srand
#include "../lbrnth.h"	// 

struct FIELD FIELD = {25, 39}; // both even
const int 
	ESC_PATH 	= 1,
	WALL		= -1,
	BLANK		= 0;

int 	idx		(int n, int m);
void 	build_matrix	(const struct FIELD, int * a);
int * 	li_share_wave	(int * maze, struct pl curs);
int 	wasnt		(struct dot curs, int * maze); // 1 - wasn't, 0 - was

void li_solve_maze(struct maze * maze)
{
	struct dot crs = {maze->endPoint.x, maze->endPoint.y};
	
	int * field = maze->field;
	int * fieldCpy = li_share_wave(field, maze->player);
	
	int weight = fieldCpy[idx(crs.y, crs.x)];
	
	do {
		weight--;

		if (fieldCpy[idx(crs.y-1, crs.x)] == weight)
			field[idx(crs.y--, crs.x)] = ESC_PATH;
		else if (fieldCpy[idx(crs.y+1, crs.x)] == weight)
			field[idx(crs.y++, crs.x)] = ESC_PATH;
		else if (fieldCpy[idx(crs.y, crs.x-1)] == weight)
			field[idx(crs.y, crs.x--)] = ESC_PATH;
		else if (fieldCpy[idx(crs.y, crs.x+1)] == weight) 
			field[idx(crs.y, crs.x++)] = ESC_PATH;
		
	} while (weight != 2);
	
	free(fieldCpy);
	
	field[idx(FIELD.HEIGHT-2, FIELD.WIDTH-2)] = BLANK;
}

int * li_share_wave(int * maze, struct pl curs)
{
	int * fieldCpy = malloc(FIELD.HEIGHT * FIELD.WIDTH * sizeof(maze[0]));
	memcpy(fieldCpy, maze, FIELD.HEIGHT * FIELD.WIDTH * sizeof(maze[0]));
	int weight = fieldCpy[idx(curs.y, curs.x)];
	do {
		weight++;	
		for (int i = 0; i < FIELD.HEIGHT; i++)
			for (int j = 0; j < FIELD.WIDTH; j++)
				if (fieldCpy[idx(i, j)] != WALL)
				if (fieldCpy[idx(i, j)] == weight-1)
				{
					fieldCpy[idx(i+1, j)] == BLANK ? fieldCpy[idx(i+1, j)]=weight:0;
					fieldCpy[idx(i-1, j)] == BLANK ? fieldCpy[idx(i-1, j)]=weight:0;
					fieldCpy[idx(i, j+1)] == BLANK ? fieldCpy[idx(i, j+1)]=weight:0;
					fieldCpy[idx(i, j-1)] == BLANK ? fieldCpy[idx(i, j-1)]=weight:0;
				}
	} while (fieldCpy[idx(FIELD.HEIGHT-2, FIELD.WIDTH-2)] == BLANK);
	
	
	return fieldCpy;
}

int * build_lbrt(int seed)
{
	srand(seed);

	struct dot curs;

	curs.x = rand()%(FIELD.WIDTH-1);
	curs.x&1 ? curs.x : curs.x++; // even / odd - bitwise comp.

	curs.y = rand()%(FIELD.HEIGHT-1);
	curs.y&1 ? curs.y : curs.y++;

	int * maze = malloc(FIELD.HEIGHT * FIELD.WIDTH * 4);

	build_matrix(FIELD, maze);

	int spaces = 1;
	while (spaces != (FIELD.HEIGHT-1)/2 * (FIELD.WIDTH-1)/2)
	{
		switch(rand() % 4) // 0 - 3
		{
			case 0:
				if (curs.x-1 > 1) 
				{	
					curs.x-=2;
					if (wasnt(curs, maze))
					{
						maze[idx(curs.y, curs.x+1)] = BLANK;
						spaces++;
					}
				}
				break;
			case 1:
				if (curs.x+1 < FIELD.WIDTH-1)
				{	
					curs.x+=2;
					if (wasnt(curs, maze))
					{
						maze[idx(curs.y, curs.x-1)] = BLANK;
						spaces++;
					}
				}
				break;
			case 2:
				if (curs.y-1 > 1)
				{	
					curs.y-=2;
					if (wasnt(curs, maze))
					{
						maze[idx(curs.y+1, curs.x)] = BLANK;
						spaces++;
					}
				}
				break;
			case 3:
				if (curs.y+1 < FIELD.HEIGHT-1)
				{	
					curs.y+=2;
					if (wasnt(curs, maze))
					{
						maze[idx(curs.y-1, curs.x)] = BLANK;
						spaces++;
					}
				}
				break;
			default: break;
		}
	}
	return maze;
}

void build_matrix(const struct FIELD size, int * a)
{
	for (int i = 0; i < size.HEIGHT; i++)
		for (int j = 0; j < size.WIDTH; j++)
			if (i % 2 != 0 && j % 2 != 0)
				a[idx(i, j)] = BLANK;
			else 
				a[idx(i, j)] = WALL;
}

int wasnt(struct dot curs, int * maze)
{
	return 	maze[idx(curs.y ,curs.x-1)] == WALL &&
			maze[idx(curs.y, curs.x+1)] == WALL &&
			maze[idx(curs.y-1, curs.x)] == WALL &&
			maze[idx(curs.y+1, curs.x)] == WALL;
}

int idx(int n, int m)
{
	return FIELD.WIDTH * n + m;
}
