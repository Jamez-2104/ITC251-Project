#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./grep-lite [flags] [pattern] '[text]'\n");
        return 1;
    }

    int n_flag = 0;
    int i_flag = 0;
    int w_flag = 0;
    int c_flag = 0;
    char *pattern = NULL;
    char *text = NULL;
    char *patternText = NULL;
    char *userFile = NULL;
    char *line = NULL;

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
        pattern = argv[2];//hardcoded
        text = argv[3];//hardcoded
        }
    }

    if (strstr(text, ".txt")){//I spy with my little eye a text file
        FILE *fptr;
        userFile = text;
        char line[256];
        fptr = fopen(userFile, "r");//I will open the file
        if(fptr == NULL){
                printf("Error opening file.\n");//I couldnt find anyhting
        }
        while (fgets(line, sizeof(line), fptr)){
                if (strstr(line, pattern)){//breaks at first sight of pattern
                        patternText=line; //TODO add method to traverse through more sightings of pattern. mayve sequencial search algo?
                        break;
                }
        }
     }else{
         if (strstr(text, pattern)){//breaks at first sight of pattern
                printf("%s is found within the text: %s\n", pattern, text); //TODO add method to traverse through more sightings of pattern && add frequency count
                patternText = text;
         }
    }


    printf("Pattern: %s\n", pattern);
    printf("Pattern in text: %s\n", patternText);
    printf("Flags: n=%d, i=%d, w=%d, c=%d\n", n_flag, i_flag, w_flag, c_flag);

    return 0;
}
