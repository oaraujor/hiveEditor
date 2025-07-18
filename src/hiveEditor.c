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

	int win_height = LINES - 2;
	int win_width = COLS - 2;

	WINDOW *edit_win = newwin(win_height, win_width, 1, 1);
	
	char buffer[BUF_LINES][BUF_COLS] = {{0}};
	int line_len[BUF_LINES] = {0};
	int cur_line = 0, cur_col = 0;
	int running = true;
	int i, ch;

	//draw border
	box(stdscr, 0, 0);

	while (running)
	{
		//statusbar
		mvprintw(LINES - 1, 2, " hiveEditor | Ctrl+Q to quit | Cursor: (%d,%d) ", cur_line + 1, cur_col + 1);
		
		wmove(edit_win, cur_line, cur_col);
		wrefresh(edit_win);
		refresh();

		//draw in window
		werase(edit_win);

		i = 0;
		for (i = 0; i < BUF_LINES; i++)
		{
			if(line_len[i] > 0)
			{
				//print lines into window
				mvwaddnstr(edit_win, i, 0, buffer[i], line_len[i]);
			}
		}

		//wmove(edit_win, cur_line, cur_col);
		//wrefresh(edit_win);
		//refresh();
		
		// USER INPUT HANDLING
		ch = wgetch(edit_win);
		switch (ch)
		{
			case 17: // Ctrl+Q (ASCII 17) to quit
				running = false;
				break;

			case KEY_UP: // Move cursor up a line if not at the top
				if (cur_line > 0)
				{
					cur_line--;
					if (cur_col > line_len[cur_line])
					{
						cur_col = line_len[cur_line];
					}
				}
				break;

			case KEY_DOWN: // Move cursor down a line if not at the bottom
				if (cur_line < BUF_LINES - 1)
				{
					cur_line++;
					if (cur_col > line_len[cur_line])
					{
						cur_col = line_len[cur_line];
					}
				}
				break;

			case KEY_LEFT: // Move cursor left if not at the start of line
				if (cur_col > 0)
				{
					cur_col--;
				}
				break;

			case KEY_RIGHT: // Move cursor right if not at end of buffer
				if (cur_col < line_len[cur_line])
				{
					cur_col++;
				}
				break;

			case KEY_BACKSPACE:
			case 127:
			case 8: // Handle backspace: remove character before cursor
				if (cur_col > 0)
				{
					memmove(&buffer[cur_line][cur_col - 1], &buffer[cur_line][cur_col], line_len[cur_line] - cur_col + 1);
					cur_col--;
					line_len[cur_line]--;
					buffer[cur_line][line_len[cur_line]] = '\0';
				}
				break;

			case '\n': // Handle Enter: move to start of next line
				if (cur_line < BUF_LINES - 1)
				{
					cur_line++;
					cur_col = 0;
				}
				break;
			default:
				// Insert printable ASCII character
				if (ch >= 32 && ch < 127)
				{
					if (line_len[cur_line] < BUF_COLS - 1)
					{
						// Shift text right to make room for new character
						memmove(&buffer[cur_line][cur_col + 1], &buffer[cur_line][cur_col], line_len[cur_line] - cur_col + 1);
						buffer[cur_line][cur_col] = ch; // Insert character
						line_len[cur_line]++;
						cur_col++;
						buffer[cur_line][line_len[cur_line]] = '\0';
					}
				}
				break;
		}

	}
	// === Cleanup ncurses resources and exit ===
	delwin(edit_win);
	endwin();
	
	return 0;
}
