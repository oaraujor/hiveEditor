#ifndef HIVE_TYPES
#define HIVE_TYPES

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    NA,
    NOT_VISIBLE,
    VISIBLE
} LINE_VIS;

typedef struct _node_char {
    char c;
    struct _node_char *next_char_n; //next character in line
    struct _node_char *prev_char_n; //prev character in line
} hv_CHAR;

typedef struct _scrn_line {
    hv_CHAR *strng_head;        //head ptr of the strng 
    LINE_VIS status_line;           //is the line visible?
    struct _scrn_line *next_line;   // nextline
    struct _scrn_line *prev_line;   // previous line
} hv_LINE;

typedef struct _editor_file {
    hv_LINE *file_line_HEAD;   // first line of the file
    char *name_file;
}hv_FILE;

void kill_hv_char(hv_CHAR *);
void kill_hv_file(hv_FILE *);
void kill_hv_line(hv_LINE * );

hv_CHAR * c_init_hv_char();
hv_LINE * c_init_hv_line();
hv_FILE * c_init_hv_file(char *);

/*
    kill_hv_char(hv_CHAR * line_head);

    Frees ALL memory used and allocated to each node for each character in a line;
*/
void kill_hv_char(hv_CHAR * strng_head) {
    hv_CHAR *curr = NULL, *temp = NULL;
    curr = strng_head;
    if (curr != NULL) {
        while(curr != NULL) {
            temp = curr->next_char_n;
            free(curr);
            curr = temp;
        }
    }
    return;
}

void kill_hv_line(hv_LINE * line_head) {
    hv_LINE *curr_line, *temp;

    curr_line = line_head;
    if (curr_line != NULL) {
        while (curr_line != NULL) {
            temp = curr_line->next_line;
            kill_hv_char(curr_line->strng_head);
            curr_line = temp;
        }
    }
    free(line_head);
    return;
}

void kill_hv_file(hv_FILE *hv_file) {
    hv_FILE * temp_hv_file;

    temp_hv_file = hv_file;

    if(temp_hv_file != NULL) {
        temp_hv_file->name_file = NULL;
        kill_hv_line(temp_hv_file->file_line_HEAD);
    }
    free(hv_file);
    return;
}

/*
    hv_CHAR * init_hv_char()
    Init a single node, everything to NULL and \0 for the char value

    Returns:    NULL if failed to allocate memory
                hv_CHAR * ptr if succesfully allocated memory
*/
hv_CHAR * c_init_hv_char() {
    hv_CHAR * init_char;

    init_char = (hv_CHAR *)malloc(sizeof(hv_CHAR));
    if (init_char != NULL) {
        init_char->c = '\0';
        init_char->next_char_n = NULL;
        init_char->prev_char_n = NULL;
    }
    return init_char;
}

/*
    hv_LINE * create_newLine();
    Init a new line, everuthing is set to NULL and NA for status_line.

    Returns:    NULL if failed to allocate memory for the line;
                hvr_LINE * ptr if succesfully allocated memory
*/
hv_LINE * c_init_hv_line() {
    hv_LINE * init_line;

    init_line = (hv_LINE *)malloc(sizeof(hv_LINE));
    if (init_line != NULL) {
        init_line->strng_head = NULL;
        init_line->status_line = NA;
        init_line->next_line = NULL;
        init_line->prev_line = NULL;
    }
    return init_line;
}

hv_FILE * c_init_hv_file(char *file_name) {
    hv_FILE * init_file;

    init_file = (hv_FILE *)malloc(sizeof(hv_FILE));
    if (init_file != NULL) {
        init_file->file_line_HEAD = NULL;
        init_file->name_file = file_name;
    }
    return init_file;
}


#endif

