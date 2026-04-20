#include <stdio.h>
#include <string.h>

// Function prototype
void process_stream(FILE *file, const char *pattern, int n_flag, int i_flag, int w_flag, int c_flag);

int main(int argc, char *argv[]) {
    // Check if we have at least the program name and a pattern
    if (argc < 2) {
        printf("Usage: ./grep-lite [flags] [pattern] [file...]\n");
        return 1;
    }

    int n_flag = 0;
    int i_flag = 0;
    int w_flag = 0;
    int c_flag = 0;
    int arg_idx = 1;

    // Parse the flags
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

    // Make sure a pattern was provided after the flags
    if (arg_idx >= argc) {
        printf("Error: Missing pattern to search for.\n");
        return 1;
    }
    
    char *pattern = argv[arg_idx];
    arg_idx++;

    // If no files are listed, read from standard input
    if (arg_idx == argc) {
        process_stream(stdin, pattern, n_flag, i_flag, w_flag, c_flag);
    } else {
        // Loop through all provided files
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

// Function to handle reading and matching line by line
void process_stream(FILE *file, const char *pattern, int n_flag, int i_flag, int w_flag, int c_flag) {
    char line[1024]; 

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }
}
