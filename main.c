#include <stdio.h>
#include <string.h>

void process_stream(FILE *file, const char *pattern, int n_flag, int i_flag, int w_flag, int c_flag);

int main(int argc, char *argv[]) {
    // check argument count
    if (argc < 2) {
        printf("Usage: ./grep-lite [flags] [pattern] [file...]\n");
        return 1;
    }

    int n_flag = 0;
    int i_flag = 0;
    int w_flag = 0;
    int c_flag = 0;
    int arg_idx = 1;

    // check for flags
    while (arg_idx < argc && argv[arg_idx][0] == '-') {
        if (argv[arg_idx][1] == 'n') {
            n_flag = 1;
        } else if (argv[arg_idx][1] == 'i') {
            i_flag = 1;
        } else if (argv[arg_idx][1] == 'w') {
            w_flag = 1;
        } else if (argv[arg_idx][1] == 'c') {
            c_flag = 1;
        } else {
            printf("Unknown flag: %s\n", argv[arg_idx]);
            return 1;
        }
        arg_idx++;
    }

    // get the pattern
    if (arg_idx >= argc) {
        printf("Error: Missing pattern to search for.\n");
        return 1;
    }
    
    char *pattern = argv[arg_idx];
    arg_idx++;

    // check if reading from stdin or file
    if (arg_idx == argc) {
        process_stream(stdin, pattern, n_flag, i_flag, w_flag, c_flag);
    } else {
        // loop through files
        for (int i = arg_idx; i < argc; i++) {
            FILE *fptr = fopen(argv[i], "r");
            if (fptr == NULL) {
                printf("grep-lite: %s: No such file or directory\n", argv[i]);
                continue; 
            }
            process_stream(fptr, pattern, n_flag, i_flag, w_flag, c_flag);
            fclose(fptr);
        }
    }

    return 0;
}

// function to search file
void process_stream(FILE *file, const char *pattern, int n_flag, int i_flag, int w_flag, int c_flag) {
    char line[1024]; 

    // read line by line
    while (fgets(line, sizeof(line), file)) {
        // check if pattern is in the line
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }
}
