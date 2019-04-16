// colors
#define F_RED		31 // foreground
#define F_GREEN		32
#define B_RED		41 // background
#define B_GREEN		42
#define B_YELLOW	43
#define B_WHITE		47

void move_cursor(char direction, int lenght); 	// u - up, d - down, 
												// l - left, r - right
void set_attr(int attr); // 0 - all attributes off
void color_print(char * text, int color);
void setw_title(char * title);
void setw_hw(int height, int width);
void hide_cursor (void);
void erase_chars(int count);
void clrscr(void);
void gotoxy(int x, int y);
void save_curs_pos();
void update_curs_pos();
