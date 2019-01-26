#include "cubo.h"

int main()
{
	char *str = NULL;
	initscr();
	initialization();
	set_cube();
    do
	{
		clear();
		print_cube();
		print_options();
		if (str != NULL)
			free(str);
		str = NULL;
		do
		{
			move(28, 10);
			scanw("%m[^\n]", &str);
		}
		while (str == NULL);
		split(str);
	}	
	while (strcmp(str, "end"));
	endwin();
	return 0;
}
