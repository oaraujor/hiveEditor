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
	int cur_line = 0, cur_col = 0;
	int running = true;
	int i, ch;

	while (running)
	{
		clear();                    // Clear entire stdscr (main screen)
		box(stdscr, 0, 0);          // Draw a border around stdscr
		// Status bar at the bottom: show editor name, quit hint, and cursor position
		mvprintw(LINES-1, 2, " hiveEditor | Ctrl+Q to quit | Cursor: (%d,%d) ", cur_line + 1, cur_col + 1);
        	// --- Draw Buffer in Editing Window ---
		werase(edit_win);           // Clear the editing window
		i = 0;
		for (i = 0; i < BUF_LINES; i++)
		{
			// Print each line of the buffer into the edit window
			mvwprintw(edit_win, i, 0, "%s", buffer[i]);
		}

		// Put the cursor at the correct place in the edit window
		wmove(edit_win, cur_line, cur_col);
		wrefresh(edit_win);         // Refresh edit window to show changes
		refresh();                  // Refresh stdscr (border/status)
		// --- Handle User Input ---
		ch = wgetch(edit_win);  // Wait for keypress in edit window

		switch (ch)
		{
			case 17: // Ctrl+Q (ASCII 17) to quit
				running = false;
				break;

			case KEY_UP:
				// Move cursor up a line if not at the top
				if (cur_line > 0)
				{
					cur_line--;
				}
				break;

			case KEY_DOWN:
			// Move cursor down a line if not at the bottom
				if (cur_line < BUF_LINES-1)
				{
					cur_line++;
				}
				break;

			case KEY_LEFT:
				// Move cursor left if not at the start of line
				if (cur_col > 0)
				{
					cur_col--;
				}
				break;
			case KEY_RIGHT:
				// Move cursor right if not at end of buffer
				if (cur_col < BUF_COLS-1)
				{
					cur_col++;
				}
				break;
			case KEY_BACKSPACE:
			case 127:
			case 8:
				// Handle backspace: remove character before cursor
				if (cur_col > 0)
				{
					// Shift text left to fill the gap
					memmove(&buffer[cur_line][cur_col - 1], &buffer[cur_line][cur_col], BUF_COLS - cur_col);
					cur_col--;
				}
				break;
			case '\n':
				// Handle Enter: move to start of next line
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
					if (cur_col < BUF_COLS - 1)
					{
						// Shift text right to make room for new character
						memmove(&buffer[cur_line][cur_col + 1], &buffer[cur_line][cur_col], BUF_COLS - cur_col - 1);
						buffer[cur_line][cur_col] = ch; // Insert character
						cur_col++;
					}
				}
				break;
		}
	}
	// === Cleanup ncurses resources and exit ===
	delwin(edit_win);    // Delete editing window
	endwin();            // End ncurses mode, restore normal terminal
	
	return 0;
}
