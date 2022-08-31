#ifndef SRC_STATE_SORT_H_
#define SRC_STATE_SORT_H_

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct mystruct {
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    int status;
    int id;
} mystruct;

int skip_spaces();
void read_from_stdin(char* path);
int comparison(mystruct elem_1, mystruct elem_2);
void sort(FILE *fp);
void add(char *path);
void output(FILE *fp);
mystruct read_record_from_file(FILE* pfile, int index);
void write_record_in_file(FILE* pfile, const mystruct* record_to_write,
                          int index);
void swap_records_in_file(FILE* pfile, int record_index1, int record_index2);
int get_file_size_in_bytes(FILE* pfile);
int get_records_count_in_file(FILE* pfile);

#endif  // SRC_STATE_SORT_H_
