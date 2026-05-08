#include <stdio.h>
#include <string.h>
#include "search.h"

char make_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32; 
    }
    return c;
}

int is_boundary(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
        return 0; 
    }
    return 1;
}

int check_match(const char line[], const char pattern[], int i_flag, int w_flag) {
    int line_len = (int)strlen(line); 
    int pat_len = (int)strlen(pattern);

    for (int i = 0; i <= line_len - pat_len; i++) {
        int match = 1;
        for (int j = 0; j < pat_len; j++) {
            char l_char = line[i + j];
            char p_char = pattern[j];

            if (i_flag == 1) {
                l_char = make_lower(l_char);
                p_char = make_lower(p_char);
            }
            if (l_char != p_char) {
                match = 0;
                break;
            }
        }

        if (match == 1) {
            if (w_flag == 1) {
                int start_ok = (i == 0 || is_boundary(line[i - 1]));
                
                char next = (i + pat_len < line_len) ? line[i + pat_len] : '\0';
                int end_ok = (next == '\0' || next == '\n' || is_boundary(next));
                
                if (start_ok == 1 && end_ok == 1) return 1;
            } else {
                return 1;
            }
        }
    }
    return 0; 
}

void process_stream(FILE *file, const char filename[], const char pattern[], int n_flag, int i_flag, int w_flag, int c_flag, int multi) {
    char line[1024]; 
    int line_num = 0;
    int matches = 0;

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        int len = (int)strlen(line);
        int flush_needed = 0;

        if (len > 0 && line[len - 1] != '\n' && !feof(file)) {
            int ch;
            while ((ch = fgetc(file)) != '\n' && ch != EOF);
            flush_needed = 1;
        }

        if (check_match(line, pattern, i_flag, w_flag) == 1) {
            matches++;
            if (c_flag == 0) {
                if (multi == 1) printf("%s:", filename);
                if (n_flag == 1) printf("%d:", line_num);
                printf("%s", line);
                
                if (line[len - 1] != '\n' || flush_needed == 1) printf("\n");
            }
        }
    }

    if (c_flag == 1) {
        if (multi == 1) printf("%s:", filename);
        printf("%d\n", matches);
    }
}
