const int 
		ESC_PATH,
		WALL,
		BLANK;
		
struct FIELD {
	const int HEIGHT, WIDTH;
};
struct FIELD FIELD;

int idx(int n, int m);

struct dot {
	int x, y;
};

struct pl {
	int x, y;
	int step, level;
};

struct maze {
	struct dot 	endPoint;
	struct pl	player;
	int * 		field;
	int 		seed;
	int		showPath;
};

void li_solve_maze(struct maze * maze);
int * build_lbrt(int seed);
