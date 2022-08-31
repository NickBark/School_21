#include "state_sort.h"

#define SIZE_OF_PATH 200

int main() {
    int exit = 0;
    int menu = 0;
    int mode = 0;

    FILE* fp = NULL;
    char path[SIZE_OF_PATH];

    while (!exit) {
        read_from_stdin(path);
        fp = fopen(path, "rb+");
        if (fp != NULL) {
            exit = 1;
            menu = 1;
            break;
        } else {
            printf("n/a\n");
            break;
        }
    }

    while (menu) {
        int res = scanf("%d", &mode);
        int blank = skip_spaces();
        if (res != 1 || !blank) {
            printf("n/a\n");
            fclose(fp);
            break;
        }

        switch (mode) {
        case 0:
            output(fp);
            fclose(fp);
            break;

        case 1:
            sort(fp);
            output(fp);
            fclose(fp);
            break;

        case 2:
            fclose(fp);
            add(path);
            fp = fopen(path, "rb+");
            sort(fp);
            output(fp);
            fclose(fp);
            break;

        default:
            printf("n/a\n");
            fclose(fp);
            break;
        }

        return 0;
    }
}

void read_from_stdin(char* path) {
    int i = 0, ch;
    while ((ch = getchar()) != '\n') {
        path[i++] = ch;
    }
    path[i] = '\0';
}

int skip_spaces() {
    int spaces = 1, ch;
    while ((ch = getchar()) != '\n') {
        if (isspace(ch)) {
            spaces = 0;
        }
    }
    return spaces;
}

void add(char* path) {
    FILE* fp = fopen(path, "ab");
    mystruct record;
    int records_count = get_records_count_in_file(fp);
    int res = scanf("%d %d %d %d %d %d %d %d", &record.year, &record.month,
                    &record.day, &record.hour, &record.min, &record.sec,
                    &record.status, &record.id);
    if (res == 8) {
        write_record_in_file(fp, &record, records_count);
    } else {
        printf("n/a\n");
    }
    fclose(fp);
}

void sort(FILE* fp) {
    int records_count = get_records_count_in_file(fp);
    int min;
    mystruct min_elem;
    mystruct elem;
    int offset = 0;

    for (int i = 0; i < records_count - 1; i++) {
        min_elem = read_record_from_file(fp, i);
        for (int j = i + 1; j < records_count; j++) {
            elem = read_record_from_file(fp, j);
            min = comparison(min_elem, elem);
            if (min) {
                min_elem = elem;
                offset = j;
            }
        }
        fseek(fp, offset * sizeof(mystruct), SEEK_SET);
        swap_records_in_file(fp, i, offset);
    }
}

void output(FILE* fp) {
    mystruct elem;
    int records_count = get_records_count_in_file(fp);
    for (int i = 0; i < records_count; i++) {
        elem = read_record_from_file(fp, i);
        printf("%d %d %d %d %d %d "
               "%d %d\n",
               elem.year, elem.month, elem.day, elem.hour, elem.min, elem.sec,
               elem.status, elem.id);
    }
}

mystruct read_record_from_file(FILE* pfile, int index) {
    int offset = index * sizeof(mystruct);
    fseek(pfile, offset, SEEK_SET);
    mystruct record;
    fread(&record, sizeof(mystruct), 1, pfile);
    rewind(pfile);

    return record;
}

void write_record_in_file(FILE* pfile, const mystruct* record_to_write,
                          int index) {
    int offset = index * sizeof(mystruct);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(mystruct), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

void swap_records_in_file(FILE* pfile, int record_index1, int record_index2) {
    mystruct record1 = read_record_from_file(pfile, record_index1);
    mystruct record2 = read_record_from_file(pfile, record_index2);

    write_record_in_file(pfile, &record1, record_index2);
    write_record_in_file(pfile, &record2, record_index1);
}

int get_file_size_in_bytes(FILE* pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);

    return size;
}

int get_records_count_in_file(FILE* pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(mystruct);
}

int comparison(mystruct elem_1, mystruct elem_2) {
    int res = 0;

    if (elem_1.year > elem_2.year) {
        res = 1;
    } else if (elem_1.year < elem_2.year) {
        res = 0;
    } else if (elem_1.month > elem_2.month) {
        res = 1;
    } else if (elem_1.month < elem_2.month) {
        res = 0;
    } else if (elem_1.day > elem_2.day) {
        res = 1;
    } else if (elem_1.day < elem_2.day) {
        res = 0;
    } else if (elem_1.hour > elem_2.hour) {
        res = 1;
    } else if (elem_1.hour < elem_2.hour) {
        res = 0;
    } else if (elem_1.min > elem_2.min) {
        res = 1;
    } else if (elem_1.min < elem_2.min) {
        res = 0;
    } else if (elem_1.sec > elem_2.sec) {
        res = 1;
    } else if (elem_1.sec < elem_2.sec) {
        res = 0;
    } else {
        res = 0;
    }

    return res;
}
