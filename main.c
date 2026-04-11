#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./grep-lite [flags] pattern\n");
        return 1;
    }

    int n_flag = 0;
    int i_flag = 0;
    int w_flag = 0;
    int c_flag = 0;
    char *pattern = NULL;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'n') {
                n_flag = 1;
            } else if (argv[i][1] == 'i') {
                i_flag = 1;
            } else if (argv[i][1] == 'w') {
                w_flag = 1;
            } else if (argv[i][1] == 'c') {
                c_flag = 1;
            }
        } else {
            pattern = argv[i];
        }
    }

    printf("Pattern: %s\n", pattern);
    printf("Flags: n=%d, i=%d, w=%d, c=%d\n", n_flag, i_flag, w_flag, c_flag);

    return 0;
}
