#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUF_LINES 100
#define BUF_COLS 128

int main()
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(1);

	bool running;
	int MAX_file_edit_lines = LINES - 2;	// -2 bc of borders
	int MAX_file_edit_col = COLS - 2;	// -2 bc of borders
	char ch;
	int cur_line, cur_col;
	
	cur_line = 1;
	cur_col = 1;
	running = true;

	//draw border
	box(stdscr, 0, 0);

	while (running )
	{
		//statusbar
		mvprintw(LINES - 1, 2, " hiveEditor | Ctrl+C to quit | Cursor: (%d,%d) ",  cur_line, cur_col);
		wmove(stdscr, cur_line, cur_col);
		wrefresh(stdscr);
		refresh();

		// USER INPUT HANDLING
		ch = getch();
		switch (ch)
		{
			case 3: // Ctrl+C (ASCII 3) to quit
				running = false;
				break;

			case KEY_UP: // Move cursor up a line if not at the top
				if (cur_line > 0) {
					cur_line--;
				}
				break;

			case KEY_DOWN: // Move cursor down a line if not at the bottom
				cur_line++;
				break;

			case KEY_LEFT: // Move cursor left if not at the start of line
				cur_col--;
				break;

			case KEY_RIGHT: // Move cursor right if not at end of buffer
				if (cur_col > 0) {
					cur_col++;
				}
				break;
			
			case KEY_BACKSPACE:
			case 127:
			case 8: // Handle backspace: remove character before cursor
				
				break;

			case '\n': // Handle Enter: move to start of next line
				cur_line++;
				cur_col = 1;
				break;

			default: // Insert printable ASCII character
				mvwaddch(stdscr, cur_line, cur_col, ch);
				cur_col++;
				break;
		}
	}
	// === Cleanup ncurses resources and exit ===
	endwin();
	
	return 0;
}
