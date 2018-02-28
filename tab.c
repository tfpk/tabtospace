// Converts tabs to spaces
// @tfpk
// 2018-02-28

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// arbitrary limit on number of files allowed per program call
#define MAX_FILES 128

// if investigate[i] == 1, process_file will be called with argv[i] as filename
int investigate[MAX_FILES];
int num_spaces = 4;

void help(){
    // print basic help info
    printf("Basic Tab to Space converter.\n");
    printf("Usage:\n");
    printf("Takes any number of file names, and an option `-t n`, the number of spaces per tab.");
    printf("Replaces those filies with only spaces, no tabs.\n");
}

int process_file(char* file_name){
    /* Take filename, and replace that file with
     *
     * */
    FILE *file = NULL, *ftemp = NULL;
    char cur_char;
    int j;
    file = fopen(file_name, "r");
    ftemp = fopen(".temp", "w");
    if (file == NULL || ftemp == NULL) return 1;
    
    while ((cur_char = fgetc(file)) != EOF){
        if (cur_char == '\t'){
            for (j = 0; j < num_spaces; j++){
                fprintf(ftemp, " ");
            } 
        } else {
            fprintf(ftemp, "%c", cur_char);
        }
    }
    fclose(file); fclose(ftemp);
    
    file = fopen(file_name, "w");
    ftemp = fopen(".temp", "r");
    
    while ((cur_char = fgetc(ftemp)) != EOF){
        fprintf(file, "%c", cur_char);
    }
    fclose(file); fclose(ftemp);
    return 0;
}

int main(int argc, char** argv){
    /* Program to convert tabs to spaces
     * Arguments:
     *  - File Name (required): Name of the file to be converted
     *  - Tab Width (-t): How many spaces per tab (default 4)*/

    // if prog name is only argument

    int i, err;

    if (argc == 1){
        printf("No file provided!\n");
        help();
        return 1;
    } else if (argc > MAX_FILES){
        printf("Maximum amount of files is %i!", MAX_FILES);
    }

    // search for -h
    for (i = 1; i < argc; i++){
        if (strcmp(argv[i], "-h") == 0) {
            help();
            return 0;
        }
    }

    // Search for -t
    for (i = 1; i < argc; i++){
        // found argument
        if (argv[i][0] == '-' && strlen(argv[i]) > 1 && argv[i][1] == 't' && argc > i+1){
            if(atoi(argv[i+1]) > 0){
                num_spaces = atoi(argv[i+1]);
                // skip the other part of the flag
                i += 1;
            } else {
                printf("Could not set tab length - is -t a positive number?!\n");
                help();
                return 1;
            }
        } else if (argv[i][0] == '-'){
            printf("Option %s not recognised, or invalid!\n", argv[i]);
        } else{
            investigate[i] += 1;
        }
    }
    
    for (i = 1; i < MAX_FILES; i++){
        if (investigate[i]){
            err = process_file(argv[i]);
            if (err != 0){
                printf("File %s failed to convert.\n", argv[i]);
            }
        }
    }

}
