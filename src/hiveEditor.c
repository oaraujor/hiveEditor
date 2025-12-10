#include "hive_file_handling.h"

int main()
{
	hv_FILE * mytxtFile;

	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(1);

	bool running;
	char ch;
	char * mytxtname = {"octavioFIle.txt"};
	int cur_line, cur_col;
	
	cur_line = 1;
	cur_col = 1;
	running = true;
	mytxtFile = hv_create_new_file();
	mytxtFile->name_file = mytxtname;

	box(stdscr, 0, 0);

	while (running)
	{
		mvprintw(LINES - 1, 2, " hiveEditor | Ctrl+C to quit | Cursor: (%d,%d) chars: %zu",cur_line, cur_col, mytxtFile->num_char);
		wmove(stdscr, cur_line, cur_col);
		wrefresh(stdscr);
		refresh();

		ch = getch();
		hv_handle_usrIn(ch, mytxtFile, cur_col, cur_line, &running);
		mvaddch(cur_line, cur_col, ch);
	}
	endwin();
	hv_free_contents(mytxtFile->contents_HEAD);
	hv_free_file(mytxtFile);
	
	return 0;
}
