#ifndef HIVE_TYPES
#define HIVE_TYPES

#include <stdbool.h>
#include <stdlib.h>
#include <iso646.h>

typedef struct _node_char {
    char                c;            // char to be stored in the node
    struct _node_char   *next_char_n; //next character in line
    struct _node_char   *prev_char_n; //prev character in line
}hv_CHAR;

typedef struct _editor_file {
    char*       name_file;
    size_t      num_char;
    hv_CHAR*    contents_HEAD;
    hv_CHAR*    curr_char_cursor;
}hv_FILE;

typedef hv_CHAR hv_cursor; 


void hv_free_contents(hv_CHAR *);
void hv_free_file(hv_FILE *);
hv_CHAR * hv_create_new_char();
hv_FILE * hv_create_new_file();

/*
    hv_CHAR * hv_create_new_char()
    Init a single node, everything to NULL and \0 for the char value

    Returns:    NULL if failed to allocate memory
                hv_CHAR * ptr if succesfully allocated memory
*/
hv_CHAR *
hv_create_new_char() {
    hv_CHAR * new_v_char;

    new_v_char = (hv_CHAR *)malloc(sizeof(hv_CHAR));
    if (new_v_char != NULL) {
        new_v_char->c = '\0';
        new_v_char->next_char_n = NULL;
        new_v_char->prev_char_n = NULL;
    }
    return new_v_char;
}

/*
    hv_FILE * hv_create_new_file()

    Init a single file, everything to NULL and 0 for the number of lines

    Returns:    NULL if failed to allocate memory
                hv_FILE * ptr if succesfully allocated memory.
*/
hv_FILE *
hv_create_new_file() {
    hv_FILE * new_hv_file;

    new_hv_file = (hv_FILE *)malloc(sizeof(hv_FILE));
    if (new_hv_file != NULL) {
        new_hv_file->num_char = 0;
        new_hv_file->name_file = NULL;
        new_hv_file->contents_HEAD = NULL;
        new_hv_file->curr_char_cursor = NULL;
    }
    return new_hv_file;
}

/*
    hv_free_contents(hv_CHAR *);

    Frees ALL memory used and allocated to each node for each character in a line;
*/
void
hv_free_contents(hv_CHAR * contents_head) {
    hv_CHAR *curr = NULL, *temp = NULL;
    curr = contents_head;
    if (curr != NULL) {
        while(curr != NULL) {
            temp = curr->next_char_n;
            free(curr);
            curr = temp;
        }
    }
    return;
}


/*
    hv_free_file(hv_FILE *);

    Frees ALL memory used and allocated to each node for hv_FILE* type;
*/
void
hv_free_file(hv_FILE *hv_file) {
    hv_FILE * temp_hv_file;

    temp_hv_file = hv_file;

    if(temp_hv_file != NULL) {
        temp_hv_file->name_file = NULL;
        temp_hv_file->contents_HEAD = NULL;
        temp_hv_file->num_char = 0;
    }
    free(hv_file);
    return;
}

#endif

