#ifndef HIVE_HAND
#define HIVE_HAND

#include "hive_types.h"
#include <ncurses.h>
//#include <termios.h>
//#include <unistd.h>

void hv_handle_usrIn(char, hv_FILE *, int, int, bool *);
void hv_add_char(hv_FILE *, char);
void print_file(hv_FILE *);
//int hv_getch();

void hv_handle_usrIn(char ch, hv_FILE * file, int curr_col, int curr_line, bool * isRunning) {

    switch (ch) {

        case 3:
            *isRunning = false;
            break;

        case KEY_UP: 
            // Move cursor up a line if not at the top
            if (curr_line > 0) {
                curr_line--;
            }
            break;

        case KEY_DOWN:
            // Move cursor down a line if not at the bottom
            curr_line++;
            break;

        case KEY_LEFT:
            curr_col--;
            file->curr_char_cursor = file->curr_char_cursor->prev_char_n;
            break;
            
        case KEY_RIGHT:
            // Move cursor right if not at end of buffer
            if (curr_col > 0) {
                curr_col++;
            }
            file->curr_char_cursor = file->curr_char_cursor->next_char_n;
            break;
        
        case KEY_BACKSPACE:
        case 127:
        case 8:
            // Handle backspace: remove character before cursor
            
            break;

        case '\n':
            hv_add_char(file, '\n');
            curr_line++;
            curr_col = 1;
            break;
            
        default:    
            hv_add_char(file, ch);
            curr_col++;
            break;
    }
}


void hv_add_char(hv_FILE* file, char c) {
    hv_CHAR *newChar = NULL;
    hv_CHAR *t = NULL, *curr = NULL;

    newChar = hv_create_new_char();
    if (newChar not_eq NULL) {
        newChar->c = c;
        newChar->next_char_n = NULL;
        newChar->prev_char_n = NULL;

        if(file->contents_HEAD == NULL) {
            file->contents_HEAD = newChar;
            file->curr_char_cursor = newChar;
        }
        else if (file->curr_char_cursor == NULL) {
            t = file->contents_HEAD;
            while (t->next_char_n not_eq NULL) {
                t = t->next_char_n;
            }
            t->next_char_n = newChar;
            newChar->prev_char_n = t;
            file->curr_char_cursor = newChar;
        }
        else {
            curr = file->curr_char_cursor;
            newChar->next_char_n = curr->next_char_n;
            newChar->prev_char_n = curr;
            curr->next_char_n = newChar;
            if (newChar->next_char_n not_eq NULL) {
                newChar->next_char_n->prev_char_n = newChar;
            }
            file->curr_char_cursor = newChar;
        }
        file->num_char++;
    }
}
/*
int hv_getch() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;

}
*/

void print_file(hv_FILE *file) {

    hv_cursor *currChar;
    
    currChar = file->contents_HEAD;

    printf("file: %s | chars: %zu\n", file->name_file, file->num_char);
    while (currChar not_eq NULL) {
        putchar(currChar->c);
        currChar = currChar->next_char_n;
    }
}
#endif