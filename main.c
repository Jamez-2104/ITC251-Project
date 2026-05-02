#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "search.h"

int main(void) {
        int flag = -1;
        int flag_n = 0;
        int flag_i = 0;
        int flag_w = 0;
        int flag_c = 0;

        char userFolder[256];
        char pattern[256];

        printf("Welcome to grep-lite\n");

        printf("Please enter the folder you want to search in: ");
        scanf("%255s", userFolder);

        printf("Please enter the pattern you want to search for: ");
        scanf("%255s", pattern);

//---------------------------Flag GUI-------------------------------//
        while (flag != 0) {
                printf("--------------------------------------------------------------------\n");
                printf("1:Flag-n (line numbers)\n");
                printf("2:Flag-i (case insensitive)\n");
                printf("3:Flag-w (whole word)\n");
                printf("4:Flag-c (count)\n");
                printf("--------------------------------------------------------------------\n");

                printf("Current selected flags: n:%d, i:%d, w:%d, c:%d\n",
                       flag_n, flag_i, flag_w, flag_c);

                printf("Select what flags you want to use (press 0 to finish): ");
                scanf("%d", &flag);

                if (flag != 0) {
                        printf("\x1b[8A\r");
                }

                if (flag < 5 && flag > 0) {
                        switch (flag) {
                        case 1:
                                flag_n = !flag_n;
                                break;

                        case 2:
                                flag_i = !flag_i;
                                break;

                        case 3:
                                flag_w = !flag_w;
                                break;

                        case 4:
                                flag_c = !flag_c;
                                break;
                        }
                }
        }

//---------------------------Search folder-----------------------------//
        DIR *folder = opendir(userFolder);
        struct dirent *entry;

        if (folder == NULL) {
                printf("Could not open folder: %s\n", userFolder);
                return 1;
        }

        while ((entry = readdir(folder)) != NULL) {
                char path[512];
                struct stat fileInfo;
                FILE *file;

                if (strcmp(entry->d_name, ".") == 0 ||
                    strcmp(entry->d_name, "..") == 0) {
                        continue;
                }

                snprintf(path, sizeof(path), "%s/%s", userFolder, entry->d_name);

                if (stat(path, &fileInfo) != 0) {
                        continue;
                }

                if (!S_ISREG(fileInfo.st_mode)) {
                        continue;
                }

                file = fopen(path, "r");

                if (file == NULL) {
                        printf("Could not open file: %s\n", path);
                        continue;
                }

                process_stream(file, path, pattern, flag_n, flag_i, flag_w, flag_c, 1);

                fclose(file);
        }

        closedir(folder);

        return 0;
}
