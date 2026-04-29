#include <stdio.h>
#include <string.h>
#include "search.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./grep-lite [flags] [pattern] [file...]\n");
        return 1;
    }

    int n_flag = 0, i_flag = 0, w_flag = 0, c_flag = 0;
    int arg_idx = 1;

    while (arg_idx < argc && argv[arg_idx][0] == '-') {
        int j = 1;
        while (argv[arg_idx][j] != '\0') {
            if (argv[arg_idx][j] == 'n') n_flag = 1;
            else if (argv[arg_idx][j] == 'i') i_flag = 1;
            else if (argv[arg_idx][j] == 'w') w_flag = 1;
            else if (argv[arg_idx][j] == 'c') c_flag = 1;
            else {
                fprintf(stderr, "grep-lite: unknown option -- '%c'\n", argv[arg_idx][j]);
                return 1;
            }
            j++;
        }
        arg_idx++;
    }

    if (arg_idx >= argc) {
        fprintf(stderr, "grep-lite: missing pattern argument\n");
        return 1;
    }
    
    char *pattern = argv[arg_idx];
    
    if (strlen(pattern) == 0) {
        fprintf(stderr, "grep-lite: pattern cannot be empty\n");
        return 1;
    }
    
    arg_idx++;

    int num_files = argc - arg_idx;
    int multi = (num_files > 1) ? 1 : 0;

    if (num_files == 0) {
        process_stream(stdin, "(standard input)", pattern, n_flag, i_flag, w_flag, c_flag, 0);
    } else {
        for (int i = arg_idx; i < argc; i++) {
            FILE *f = fopen(argv[i], "r");
            if (f == NULL) {
                fprintf(stderr, "grep-lite: %s: No such file or directory\n", argv[i]);
                continue; 
            }
            process_stream(f, argv[i], pattern, n_flag, i_flag, w_flag, c_flag, multi);
            fclose(f);
        }
    }
    return 0;
}
