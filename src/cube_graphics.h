void initialization()
{
	if(has_colors() == FALSE)
	{	
		endwin();
		printf("Your terminal doesn't support colors!\n");
		exit(1);
	}
    keypad(stdscr, TRUE);
	start_color();
	wbkgd(stdscr, COLOR_PAIR(0));
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	init_pair(2, COLOR_BLACK, COLOR_BLUE);
	init_pair(3, COLOR_BLACK, COLOR_RED);
	init_pair(4, COLOR_BLACK, COLOR_GREEN);
	init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
}

void print_cube()
{
	int i, j;
	for (i = 0; i < 6; i += 2) // top
	{
		for (j = 0; j < 3; j++)
		{
			attron(COLOR_PAIR(cube[0][i / 2][j].top + 1));
			mvprintw(i + 4, 19 + j * 4, "    ");
			mvprintw(i + 5, 19 + j * 4, "    ");
			attroff(COLOR_PAIR(cube[0][i / 2][j].top + 1));
		}
	}
	for (i = 0; i < 6; i += 2) // left
	{
		for (j = 0; j < 3; j++)
		{
			attron(COLOR_PAIR(cube[i / 2][j][0].left + 1));
			mvprintw(i + 11, 5 + j * 4, "    ");
			mvprintw(i + 12, 5 + j * 4, "    ");
			attroff(COLOR_PAIR(cube[i / 2][j][0].left + 1));
		}
	}
	for (i = 0; i < 6; i += 2) // front
	{
		for (j = 0; j < 3; j++)
		{
			attron(COLOR_PAIR(cube[i / 2][2][j].front + 1));
			mvprintw(i + 11, 19 + j * 4, "    ");
			mvprintw(i + 12, 19 + j * 4, "    ");
			attroff(COLOR_PAIR(cube[i / 2][2][j].front + 1));
		}
	}
	for (i = 0; i < 6; i += 2) // right
	{
		for (j = 2; j >= 0; j--)
		{
			attron(COLOR_PAIR(cube[i / 2][j][2].right + 1));
			mvprintw(i + 11, 33 + (-j + 2) * 4, "    ");
			mvprintw(i + 12, 33 + (-j + 2) * 4, "    ");
			attroff(COLOR_PAIR(cube[i / 2][j][2].right + 1));
		}
	}
	for (i = 0; i < 6; i += 2) // back
	{
		for (j = 2; j >= 0; j--)
		{
			attron(COLOR_PAIR(cube[i / 2][0][j].back + 1));
			mvprintw(i + 11, 47 + (-j + 2) * 4, "    ");
			mvprintw(i + 12, 47 + (-j + 2) * 4, "    ");
			attroff(COLOR_PAIR(cube[i / 2][0][j].back + 1));
		}
	}
	for (i = 4; i >= 0; i -= 2) // bottom
	{
		for (j = 0; j < 3; j++)
		{
			attron(COLOR_PAIR(cube[2][i / 2][j].bottom + 1));
			mvprintw((-i + 4) + 18, 19 + j * 4, "    ");
			mvprintw((-i + 4) + 19, 19 + j * 4, "    ");
			attroff(COLOR_PAIR(cube[2][i / 2][j].bottom + 1));
		}
	}
	refresh();
}

void print_options()
{
	mvprintw(1, 70, " _____     _         ___    _____     _____ ");
	mvprintw(2, 70, "|  ___|   | |       / __|  |  _  |   |___  |");
	mvprintw(3, 70, "| |__   __| |  ___ | |__   | | | |    ___| |");
	mvprintw(4, 70, "|  __| / _` | / _ \\|  __|  | | | |   |___  |");
	mvprintw(5, 70, "| |___ |(_| ||  __/| |     | |_| | _  ___| |");
	mvprintw(6, 70, "|_____|\\__,_| \\___||_|     |_____|(_)|_____|");
	mvprintw(8, 70, "Rubik's cube simulator and solver!");
	mvprintw(11, 70, "Command available:");
	mvprintw(12, 70, "- reset");
	mvprintw(13, 70, "- solve");
	mvprintw(14, 70, "- random");
	mvprintw(15, 70, "- moves");
	mvprintw(16, 70, "- info");
	mvprintw(17, 70, "- end");
	mvprintw(28, 1, "Command: ");
	refresh();
}

void print_moves()
{
	clear();
	attron(A_REVERSE);
	mvprintw(1, 2, "Moves available:");
	attroff(A_REVERSE);
	mvprintw(3, 4, "- U, U2, U', U2', Uw, Uw2, Uw', Uw2'");
	mvprintw(4, 4, "- D, D2, D', D2', Dw, Dw2, Dw', Dw2'");
	mvprintw(5, 4, "- R, R2, R', R2', Rw, Rw2, Rw', Rw2'");
	mvprintw(6, 4, "- L, L2, L', L2', Lw, Lw2, Lw', Lw2'");
	mvprintw(7, 4, "- F, F2, F', F2', Fw, Fw2, Fw', Fw2'");
	mvprintw(8, 4, "- B, B2, B', B2', Bw, Bw2, Bw', Bw2'");
	mvprintw(9, 4, "- M, M2, M', M2'"); 
	mvprintw(10, 4, "- E, E2, E', E2'");
	mvprintw(11, 4, "- S, S2, S', S2'");
	mvprintw(12, 4, "- X, X2, X', X2'");
	mvprintw(13, 4, "- Y, Y2, Y', Y2'");
	mvprintw(14, 4, "- Z, Z2, Z', Z2'");
	mvprintw(18, 2, "Press any character to continue...");
	getch();
}

void print_info()
{
	clear();
	attron(A_REVERSE);
	mvprintw(1, 2, "About author:");
	attroff(A_REVERSE);
	mvprintw(3, 4, "Developed by Andrea Dipace (dopas).");
	mvprintw(4, 4, "Email: ");
	attron(A_UNDERLINE);
	printw("andrea.dipace.00@gmail.com");
	attroff(A_UNDERLINE);
	mvprintw(5, 4, "Facebook: ");
	attron(A_UNDERLINE);
	printw("https://www.facebook.com/dopas.pajot");
	attroff(A_UNDERLINE);
	attron(A_REVERSE);
	mvprintw(8, 2, "Program's info:");
	attroff(A_REVERSE);
	mvprintw(10, 4, "Edef 0.3 is a rubik's cube simulator and solver.");
	mvprintw(11, 4, "The method used for solving cube is:");
	mvprintw(12, 4, "- First Layer Cross");
	mvprintw(13, 4, "- First Layer Corners");
	mvprintw(14, 4, "- Second Layer Edges");
	mvprintw(15, 4, "- OLL Simplified (3 for cross, 7 for corners)");
	mvprintw(16, 4, "- Permutate Last Layer (PLL from Fridrich)");
	mvprintw(18, 4, "It is entirely programmed in C with ncurses as");
	mvprintw(19, 5, "a graphics library for terminal management.");
	mvprintw(23, 2, "Press any character to continue...");
	getch();
}
