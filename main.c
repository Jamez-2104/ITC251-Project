#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <stdbool.h>
#include <getopt.h> // Added this to fix the red error!

int main(int argc, char *argv[]) {
    int opt;
    
    // Your 'on/off' switches for the flags
    bool flag_line_nums = false;
    bool flag_case_insens = false;
    bool flag_whole_word = false;
    bool flag_count = false;
    
    // Parse the letters the user types
    while ((opt = getopt(argc, argv, "niwc")) != -1) {
        switch (opt) {
            case 'n': flag_line_nums = true; break;
            case 'i': flag_case_insens = true; break;
            case 'w': flag_whole_word = true; break;
            case 'c': flag_count = true; break;
            default:
                fprintf(stderr, "Usage: %s [-niwc] pattern [file...]\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    // We print the variables here so the strict compiler stops complaining!
    printf("Skeleton built! Flags: n=%d, i=%d, w=%d, c=%d\n", 
            flag_line_nums, flag_case_insens, flag_whole_word, flag_count);

    return EXIT_SUCCESS;
}
