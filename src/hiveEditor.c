#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int main(){

	initscr();
	printw("hello with ncurses test\n");
	refresh();
	getch();
	endwin();

	return 0;
}
