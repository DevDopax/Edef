#include <string.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "moves.h"

void split(char*);
int run(char*);

typedef struct
{
	short int type;
	short int top;
	short int front;
	short int right;
	short int back;
	short int left;
	short int bottom;
} part;
part cube[3][3][3];

#include "cube_graphics.h"

short int edge[12][3] = {{2, 2, 1}, {2, 1, 2}, {2, 0, 1}, {2, 1, 0}, 
				   {1, 2, 2}, {1, 0, 2}, {1, 0, 0}, {1, 2, 0},
				   {0, 2, 1}, {0, 1, 2}, {0, 0, 1}, {0, 1, 0}};
			
short int corners[8][3] = {{2, 2, 2}, {2, 0, 2}, {2, 0, 0}, {2, 2, 0},
					 {0, 2, 2}, {0, 0, 2}, {0, 0, 0}, {0, 2, 0}};

char moves[9][5] = {"U", "D", "R", "L", "F", "B"};

#include "resolution.h"

void split(char *to_token)
{
	char *com, *str = strdup(to_token);
	int x = 5, y = 28, err;
	clear();
	print_cube();
	com = strtok((char*) str, " ");
	err = run(com);
	if (err >= 0)
	{
		mvprintw(28, 1, "Do: ");
		while (com != NULL) 
		{
			curs_set(0);
			attron(A_REVERSE);
			mvprintw(y, x, "%s", com);
			attroff(A_REVERSE);
			mvprintw(32, 1, "Press any character to continue...");
			curs_set(1);
			getch();
			print_cube();
			if (err)
			{
				attron(COLOR_PAIR(3));
				attron(A_REVERSE);
				mvprintw(30, 1, "Unknow %s!   ", com);
				attroff(A_REVERSE);
				attroff(COLOR_PAIR(3));
				while ((com = strtok(NULL, " ")) != NULL);
				break;
			}
			else
			{
				attron(COLOR_PAIR(4));
				attron(A_REVERSE);
				mvprintw(30, 1, "%s done!      ", com);
				attroff(A_REVERSE);
				attroff(COLOR_PAIR(4));
				mvprintw(y, x, "%s ", com);
				getyx(stdscr, y, x);
				com = strtok(NULL, " ");
				if (com != NULL)
				{
					clear_near_cube();
					print_cube();
					err = run(com);
				}	
			}
			refresh();
		}
		clear_near_cube();
		print_cube();
		mvprintw(32, 1, "Press any character to continue...");
		getch();
	}
	free(str);
}

char *str_scramble(int *scramble, int len)
{
	char moveset_to_char[] = {'U', 'D', 'F', 'B', 'R', 'L'};
	char suffix_to_char[] = {'\0', '\'', '2'};
	int to_alloc_size = 0;
	for(int i=0; i<len; i++)
	{
		int suffix = scramble[i] % 3;
		if(suffix) to_alloc_size += 3;
		else to_alloc_size += 2;
	}
	char *ret = malloc(sizeof(char) * (to_alloc_size + 1));
	ret[to_alloc_size] = '\0';
	int str_index = 0;
	for(int i=0; i<len; i++)
	{
		ret[str_index++] = moveset_to_char[scramble[i] / 3];
		int suffix = scramble[i] % 3;
		if(suffix)
			ret[str_index++] = suffix_to_char[suffix];
		ret[str_index++] = ' ';
	}
	ret[str_index] = '\0';
	return ret;
}

int *scramble(int lenght)
{
	int *ret = malloc(sizeof(int)*lenght);
	int latest_moveset = -2;
	int latest_moveaxis = -1;
	int before_latest_moveaxis = -2;
	for(int i=0; i<lenght;i++)
	{
		bool valid = false;
		int move;
		while(!valid)
		{
			move = rand() % 18;
			int new_moveset = move / 3;
			int new_moveaxis = move / 6;
			if(new_moveset == latest_moveset) continue;
			if(new_moveaxis == latest_moveaxis && latest_moveaxis == before_latest_moveaxis) continue;
			valid = true;
			before_latest_moveaxis = latest_moveaxis;
			latest_moveaxis = new_moveaxis;
			latest_moveset = new_moveset;
		}
		ret[i] = move;
	}
	return ret;
}
void random_moves()
{
	clear();
	print_cube();
	mvprintw(26, 1, "Random scramble: ");
	srand(time(NULL));
	int *scr = scramble(20);
    char *moves = str_scramble(scr, 20);
	free(scr);
	split(moves);
	free(moves);
}

void solve()
{		
	first_layer_cross();
	first_layer_corners();
	second_layer_edges();
	cross_last_layer();
	last_layer_up();
	pll();
	clear();
	print_cube();
	attron(COLOR_PAIR(4));
	attron(A_REVERSE);
	mvprintw(26, 1, "Cube done!");
	attroff(A_REVERSE);
	attroff(COLOR_PAIR(4));
	getch();
}

void set_cube()
{
	int i, j, k, l;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++)
				for (l = 1; l < 7; l++)
					*((short int*) &cube[i][j][k] + l) = -1;
					
	// strato superiore
	cube[0][0][0].type = 3;
	cube[0][0][0].top = 0;
	cube[0][0][0].back = 3;
	cube[0][0][0].left = 4;
	
	cube[0][0][1].type = 2;
	cube[0][0][1].top = 0;
	cube[0][0][1].back = 3;
	
	cube[0][0][2].type = 3;
	cube[0][0][2].top = 0;
	cube[0][0][2].right = 2;
	cube[0][0][2].back = 3;
	
	cube[0][1][0].type = 2;
	cube[0][1][0].top = 0;
	cube[0][1][0].left = 4;
	
	cube[0][1][1].type = 1;
	cube[0][1][1].top = 0;
	
	cube[0][1][2].type = 2;
	cube[0][1][2].top = 0;
	cube[0][1][2].right = 2;
	
	cube[0][2][0].type = 3;
	cube[0][2][0].top = 0;
	cube[0][2][0].front = 1;
	cube[0][2][0].left = 4;
	
	cube[0][2][1].type = 2;
	cube[0][2][1].top = 0;
	cube[0][2][1].front = 1;
	
	cube[0][2][2].type = 3;
	cube[0][2][2].top = 0;
	cube[0][2][2].front = 1;
	cube[0][2][2].right = 2;
	
	// strato intermedio
	cube[1][0][0].type = 2;
	cube[1][0][0].back = 3;
	cube[1][0][0].left = 4;
	
	cube[1][0][1].type = 1;
	cube[1][0][1].back = 3;
	
	cube[1][0][2].type = 2;
	cube[1][0][2].right = 2;
	cube[1][0][2].back = 3;
	
	cube[1][1][0].type = 1;
	cube[1][1][0].left = 4;
	
	cube[1][1][1].type = 0;
	
	cube[1][1][2].type = 1;
	cube[1][1][2].right = 2;
	
	cube[1][2][0].type = 2;
	cube[1][2][0].front = 1;
	cube[1][2][0].left = 4;
	
	cube[1][2][1].type = 1;
	cube[1][2][1].front = 1;
	
	cube[1][2][2].type = 2;
	cube[1][2][2].front = 1;
	cube[1][2][2].right = 2;
	
	// strato inferiore
	cube[2][0][0].type = 3;
	cube[2][0][0].back = 3;
	cube[2][0][0].left = 4;
	cube[2][0][0].bottom = 5;
	
	cube[2][0][1].type = 2;
	cube[2][0][1].back = 3;
	cube[2][0][1].bottom = 5;
	
	cube[2][0][2].type = 3;
	cube[2][0][2].right = 2;
	cube[2][0][2].back = 3;
	cube[2][0][2].bottom = 5;

	cube[2][1][0].type = 2;
	cube[2][1][0].left = 4;
	cube[2][1][0].bottom = 5;

	cube[2][1][1].type = 1;
	cube[2][1][1].bottom = 5;
	
	cube[2][1][2].type = 2;
	cube[2][1][2].right = 2;
	cube[2][1][2].bottom = 5;
	
	cube[2][2][0].type = 3;
	cube[2][2][0].front = 1;
	cube[2][2][0].left = 4;
	cube[2][2][0].bottom = 5;
	
	cube[2][2][1].type = 2;
	cube[2][2][1].front = 1;
	cube[2][2][1].bottom = 5;

	cube[2][2][2].type = 3;
	cube[2][2][2].front = 1;
	cube[2][2][2].right = 2;
	cube[2][2][2].bottom = 5;
}

void x(part *dest, part *from)
{
	dest->top =    from->top;
	dest->front =  from->right;
	dest->right =  from->back;
	dest->back =   from->left;
	dest->left =   from->front;
	dest->bottom = from->bottom;
}

void x_inverse(part *dest, part *from)
{
	dest->top =    from->top;
	dest->front =  from->left;
	dest->right =  from->front;
	dest->back =   from->right;
	dest->left =   from->back;
	dest->bottom = from->bottom;
}

void y(part *dest, part *from)
{
	dest->top =    from->front; 
	dest->front =  from->bottom;
	dest->right =  from->right;
	dest->back =   from->top;
	dest->left =   from->left;
	dest->bottom = from->back;
}

void y_inverse(part *dest, part *from)
{
	dest->top =    from->back; 
	dest->front =  from->top;
	dest->right =  from->right;
	dest->back =   from->bottom;
	dest->left =   from->left;
	dest->bottom = from->front;
}

void z(part *dest, part *from)
{
	dest->top =    from->left; 
	dest->front =  from->front;
	dest->right =  from->top;
	dest->back =   from->back;
	dest->left =   from->bottom;
	dest->bottom = from->right;
}

void z_inverse(part *dest, part *from)
{
	dest->top =    from->right; 
	dest->front =  from->front;
	dest->right =  from->bottom;
	dest->back =   from->back;
	dest->left =   from->top;
	dest->bottom = from->left;
}

void command(int height, int caso)
{
	part tmp[3];
	switch (caso)
	{
		case 0: // X
			memcpy(tmp, cube[height][0], 3 * sizeof(part));
			x(&cube[height][0][1], &cube[height][1][0]);
			x(&cube[height][0][0], &cube[height][2][0]);
			x(&cube[height][1][0], &cube[height][2][1]);
			x(&cube[height][2][0], &cube[height][2][2]);
			x(&cube[height][2][1], &cube[height][1][2]);
			x(&cube[height][0][2], &tmp[0]);
			x(&cube[height][1][2], &tmp[1]);
			x(&cube[height][2][2], &tmp[2]);
			break;
			
		case 1: // X'
			memcpy(tmp, cube[height][0], 3 * sizeof(part));
			x_inverse(&cube[height][0][1], &cube[height][1][2]);
			x_inverse(&cube[height][0][2], &cube[height][2][2]);
			x_inverse(&cube[height][1][2], &cube[height][2][1]);
			x_inverse(&cube[height][2][2], &cube[height][2][0]);
			x_inverse(&cube[height][2][1], &cube[height][1][0]);
			x_inverse(&cube[height][2][0], &tmp[0]);
			x_inverse(&cube[height][1][0], &tmp[1]);
			x_inverse(&cube[height][0][0], &tmp[2]);
			break;

		case 2: // Y	
			memcpy(&tmp[0], &cube[0][0][height], sizeof(part));
			memcpy(&tmp[1], &cube[0][1][height], sizeof(part));
			memcpy(&tmp[2], &cube[0][2][height], sizeof(part));
			y(&cube[0][2][height], &cube[2][2][height]);
			y(&cube[0][1][height], &cube[1][2][height]);
			y(&cube[2][2][height], &cube[2][0][height]);
			y(&cube[1][2][height], &cube[2][1][height]);
			y(&cube[2][0][height], &tmp[0]);
			y(&cube[2][1][height], &cube[1][0][height]);
			y(&cube[0][0][height], &tmp[2]);
			y(&cube[1][0][height], &tmp[1]);
			break;
	
		case 3: // Y'
			memcpy(&tmp[0], &cube[0][0][height], sizeof(part));
			memcpy(&tmp[1], &cube[0][1][height], sizeof(part));
			memcpy(&tmp[2], &cube[0][2][height], sizeof(part));
			y_inverse(&cube[0][0][height], &cube[2][0][height]);
			y_inverse(&cube[0][1][height], &cube[1][0][height]);
			y_inverse(&cube[2][0][height], &cube[2][2][height]);
			y_inverse(&cube[1][0][height], &cube[2][1][height]);
			y_inverse(&cube[2][2][height], &tmp[2]);
			y_inverse(&cube[2][1][height], &cube[1][2][height]);
			y_inverse(&cube[0][2][height], &tmp[0]);
			y_inverse(&cube[1][2][height], &tmp[1]);
			break;
			
		case 4: // Z 
			memcpy(&tmp[0], &cube[0][height][0], sizeof(part));
			memcpy(&tmp[1], &cube[1][height][0], sizeof(part));
			memcpy(&tmp[2], &cube[2][height][0], sizeof(part));
			z(&cube[2][height][0], &cube[2][height][2]);
			z(&cube[1][height][0], &cube[2][height][1]);
			z(&cube[2][height][2], &cube[0][height][2]);
			z(&cube[2][height][1], &cube[1][height][2]);
			z(&cube[0][height][2], &tmp[0]);
			z(&cube[1][height][2], &cube[0][height][1]);
			z(&cube[0][height][0], &tmp[2]);
			z(&cube[0][height][1], &tmp[1]);
			break;
			
		case 5: // Z'
			memcpy(&tmp[0], &cube[0][height][0], sizeof(part));
			memcpy(&tmp[1], &cube[1][height][0], sizeof(part));
			memcpy(&tmp[2], &cube[2][height][0], sizeof(part));
			z_inverse(&cube[0][height][0], &cube[0][height][2]);
			z_inverse(&cube[1][height][0], &cube[0][height][1]);
			z_inverse(&cube[0][height][2], &cube[2][height][2]);
			z_inverse(&cube[0][height][1], &cube[1][height][2]);
			z_inverse(&cube[2][height][2], &tmp[2]);
			z_inverse(&cube[1][height][2], &cube[2][height][1]);
			z_inverse(&cube[2][height][0], &tmp[0]);
			z_inverse(&cube[2][height][1], &tmp[1]);
			break;
		}
}

int run(char *stringa)
{
	if (!strcmp(stringa, "U"))
	{
		U();
		command(0, 0);
	}
	else if (!strcmp(stringa, "U2"))
	{
		U2();
		command(0, 0);
		command(0, 0);
	}
	else if (!strcmp(stringa, "U'"))
	{
		U_inverse();
		command(0, 1);
	}
	else if (!strcmp(stringa, "U2'"))
	{
		U2_inverse();
		command(0, 1);
		command(0, 1);
	}
	else if (!strcmp(stringa, "Uw"))
	{
		Uw();
		command(0, 0);
		command(1, 0);
	}
	else if (!strcmp(stringa, "Uw2"))
	{
		Uw2();
		command(0, 0);
		command(1, 0);
		command(0, 0);
		command(1, 0);
	}
	else if (!strcmp(stringa, "Uw'"))
	{
		Uw_inverse();
		command(0, 1);
		command(1, 1);
	}
	else if (!strcmp(stringa, "Uw2'"))
	{
		Uw2_inverse();
		command(0, 1);
		command(1, 1);
	}
	else if (!strcmp(stringa, "E"))
	{
		E();
		command(1, 1);
	}
	else if (!strcmp(stringa, "E2"))
	{
		E2();
		command(1, 1);
		command(1, 1);
	}
	else if (!strcmp(stringa, "E'"))
	{
		E_inverse();
		command(1, 0);
	}
	else if (!strcmp(stringa, "E2'"))
	{
		E2_inverse();
		command(1, 0);
		command(1, 0);
	}
	else if (!strcmp(stringa, "D"))
	{
		D();
		command(2, 1);
	}
	else if (!strcmp(stringa, "D2"))
	{
		D2();
		command(2, 1);
		command(2, 1);
	}
	else if (!strcmp(stringa, "D'"))
	{
		D_inverse();
		command(2, 0);
	}
	else if (!strcmp(stringa, "D2'"))
	{
		D2_inverse();
		command(2, 0);
		command(2, 0);
	}
	else if (!strcmp(stringa, "Dw"))
	{
		Dw();
		command(1, 1);
		command(2, 1);
	}
	else if (!strcmp(stringa, "Dw2"))
	{
		Dw2();
		command(1, 1);
		command(2, 1);
		command(1, 1);
		command(2, 1);
	}
	else if (!strcmp(stringa, "Dw'"))
	{
		Dw_inverse();
		command(1, 0);
		command(2, 0);
	}
	else if (!strcmp(stringa, "Dw2'"))
	{
		Dw2_inverse();
		command(1, 0);
		command(2, 0);
		command(1, 0);
		command(2, 0);
	}
	else if (!strcmp(stringa, "R"))
	{
		R();
		command(2, 2);
	}
	else if (!strcmp(stringa, "R2"))
	{
		R2();
		command(2, 2);
		command(2, 2);
	}
	else if (!strcmp(stringa, "R'"))
	{
		R_inverse();
		command(2, 3);	
	}
	else if (!strcmp(stringa, "R2'"))
	{
		R2_inverse();
		command(2, 3);
		command(2, 3);
	}
	else if (!strcmp(stringa, "Rw"))
	{
		Rw();
		command(1, 2);
		command(2, 2);
	}
	else if (!strcmp(stringa, "Rw2"))
	{
		Rw2();
		command(1, 2);
		command(2, 2);
		command(1, 2);
		command(2, 2);
	}
	else if (!strcmp(stringa, "Rw'"))
	{
		Rw_inverse();
		command(1, 3);
		command(2, 3);
	}
	else if (!strcmp(stringa, "Rw2'"))
	{
		Rw2_inverse();
		command(1, 3);
		command(2, 3);
		command(1, 3);
		command(2, 3);
	}
	else if (!strcmp(stringa, "M"))
	{
		M();
		command(1, 3);
	}
	else if (!strcmp(stringa, "M2"))
	{
		M2();
		command(1, 3);
		command(1, 3);
	}
	else if (!strcmp(stringa, "M'"))
	{
		M_inverse();
		command(1, 2);
	}
	else if (!strcmp(stringa, "M2'"))
	{
		M2_inverse();
		command(1, 3);
		command(1, 3);
	}
	else if (!strcmp(stringa, "L"))
	{
		L();
		command(0, 3);
	}
	else if (!strcmp(stringa, "L2"))
	{
		L2();
		command(0, 3);
		command(0, 3);
	}
	else if (!strcmp(stringa, "L'"))
	{
		L_inverse();
		command(0, 2);
	}
	else if (!strcmp(stringa, "L2'"))
	{
		L2_inverse();
		command(0, 3);
		command(0, 3);
	}
	else if (!strcmp(stringa, "Lw"))
	{
		Lw();
		command(0, 3);
		command(1, 3);
	}
	else if (!strcmp(stringa, "Lw2"))
	{
		Lw2();
		command(0, 3);
		command(1, 3);
		command(0, 3);
		command(1, 3);
	}
	else if (!strcmp(stringa, "Lw'"))
	{
		Lw_inverse();
		command(0, 2);
		command(1, 2);
	}
	else if (!strcmp(stringa, "Lw2'"))
	{
		Lw2_inverse();
		command(0, 2);
		command(1, 2);
		command(0, 2);
		command(1, 2);
	}
	else if (!strcmp(stringa, "F"))
	{
		F();
		command(2, 4);
	}
	else if (!strcmp(stringa, "F2"))
	{
		F2();
		command(2, 4);
		command(2, 4);
	}
	else if (!strcmp(stringa, "F'"))
	{
		F_inverse();
		command(2, 5);
	}
	else if (!strcmp(stringa, "F2'"))
	{
		F2_inverse();
		command(2, 5);
		command(2, 5);
	}
	else if (!strcmp(stringa, "Fw"))
	{
		Fw();
		command(1, 4);
		command(2, 4);
	}
	else if (!strcmp(stringa, "Fw2"))
	{
		Fw2();
		command(1, 4);
		command(2, 4);
		command(1, 4);
		command(2, 4);
	}
	else if (!strcmp(stringa, "Fw'"))
	{
		Fw_inverse();
		command(1, 5);
		command(2, 5);
	}
	else if (!strcmp(stringa, "Fw2'"))
	{
		Fw2_inverse();
		command(1, 5);
		command(2, 5);
		command(1, 5);
		command(2, 5);
	}
	else if (!strcmp(stringa, "S"))
	{
		S();
		command(1, 4);
	}
	else if (!strcmp(stringa, "S2"))
	{
		S2();
		command(1, 4);
		command(1, 4);
	}
	else if (!strcmp(stringa, "S'"))
	{
		S_inverse();
		command(1, 5);
	}
	else if (!strcmp(stringa, "S2'"))
	{
		S2_inverse();
		command(1, 5);
		command(1, 5);
	}
	else if (!strcmp(stringa, "B"))
	{
		B();
		command(0, 5);
	}
	else if (!strcmp(stringa, "B2"))
	{
		B2();
		command(0, 5);
		command(0, 5);
	}
	else if (!strcmp(stringa, "B'"))
	{
		B_inverse();
		command(0, 4);	
	}
	else if (!strcmp(stringa, "B2'"))
	{
		B2_inverse();
		command(0, 4);
		command(0, 4);
	}
	else if (!strcmp(stringa, "Bw"))
	{
		Bw();
		command(0, 5);
		command(1, 5);
	}
	else if (!strcmp(stringa, "Bw2"))
	{
		Bw2();
		command(0, 5);
		command(1, 5);
		command(0, 5);
		command(1, 5);
	}
	else if (!strcmp(stringa, "Bw'"))
	{
		Bw_inverse();
		command(0, 4);
		command(1, 4);
	}
	else if (!strcmp(stringa, "Bw2'"))
	{
		Bw2_inverse();
		command(0, 4);
		command(1, 4);
		command(0, 4);
		command(1, 4);
	}
	else if (!strcmp(stringa, "X"))
	{
		X();
		command(0, 2);
		command(1, 2);
		command(2, 2);
	}
	else if (!strcmp(stringa, "X2"))
	{
		X2();
		command(0, 2);
		command(1, 2);
		command(2, 2);
		command(0, 2);
		command(1, 2);
		command(2, 2);
	}
	else if (!strcmp(stringa, "X'"))
	{
		X_inverse();
		command(0, 3);
		command(1, 3);
		command(2, 3);
	}
	else if (!strcmp(stringa, "X2'"))
	{
		X2_inverse();
		command(0, 3);
		command(1, 3);
		command(2, 3);
		command(0, 3);
		command(1, 3);
		command(2, 3);
	}
	else if (!strcmp(stringa, "Y"))
	{
		Y();
		command(0, 0);
		command(1, 0);
		command(2, 0);
	}
	else if (!strcmp(stringa, "Y2"))
	{
		Y2();
		command(0, 0);
		command(1, 0);
		command(2, 0);
		command(0, 0);
		command(1, 0);
		command(2, 0);
	}
	else if (!strcmp(stringa, "Y'"))
	{
		Y_inverse();
		command(0, 1);
		command(1, 1);
		command(2, 1);
	}
	else if (!strcmp(stringa, "Y2'"))
	{
		Y2_inverse();
		command(0, 1);
		command(1, 1);
		command(2, 1);
		command(0, 1);
		command(1, 1);
		command(2, 1);
	}
	else if (!strcmp(stringa, "Z"))
	{
		Z();
		command(0, 4);
		command(1, 4);
		command(2, 4);
	}
	else if (!strcmp(stringa, "Z2"))
	{
		Z2();
		command(0, 4);
		command(1, 4);
		command(2, 4);
		command(0, 4);
		command(1, 4);
		command(2, 4);
	}
	else if (!strcmp(stringa, "Z'"))
	{
		Z_inverse();
		command(0, 5);
		command(1, 5);
		command(2, 5);
	}
	else if (!strcmp(stringa, "Z2'"))
	{
		Z2_inverse();
		command(0, 5);
		command(1, 5);
		command(2, 5);
		command(0, 5);
		command(1, 5);
		command(2, 5);
	}
	else if (!strcmp(stringa, "reset"))
	{
		set_cube();
		return -1;
	}
	else if (!strcmp(stringa, "solve"))
	{
		solve();
		return -1;
	}
	else if (!strcmp(stringa, "random"))
	{
		random_moves();
		return -1;
	}
	else if (!strcmp(stringa, "moves"))
	{
		print_moves();
		return -1;
	}
	else if (!strcmp(stringa, "info"))
	{
		print_info();
		return -1;
	}
	else if (!strcmp(stringa, "end"))
	{
		return -1;
	}
	else
		return 1;
	return 0;
}