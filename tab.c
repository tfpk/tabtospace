// Converts tabs to spaces
// @tfpk
// * Arguments:
//     *  - File Name (required): Name of the file to be converted
//     *  - Tab Width (-t): How many spaces per tab (default 4)
// 2018-02-28

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// arbitrary limit on number of files allowed per program call
#define MAX_FILES 128

char TAB_COMMAND = 't';

// if investigate[i] == 1, process_file will be called with argv[i] as filename
int investigate[MAX_FILES];
int num_spaces = 4;

void help(){
    // print basic help info
    printf("Basic Tab to Space converter.\n");
    printf("Usage:\n");
    printf("Takes any number of file names, and an option `-t n`, where `n` is an integer specifying spaces per tab.\n");
    printf("Replaces tabs in those files with `n` times as many spaces\n");
}

int process_file(char* file_name){
    /* Take filename, and replace all tabs in file with spaces.
     * Arguments:
     *  - file_name: name/path for file to edit
     *
     *  Note:
     *   - Side effect: creates .temp file in cwd
     * */
    FILE *file = NULL, *ftemp = NULL;
    char cur_char;
    int j;

    // Create .temp with edited contents of file
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
   
    // Write .temp back
    file = fopen(file_name, "w");
    ftemp = fopen(".temp", "r");
    
    while ((cur_char = fgetc(ftemp)) != EOF){
        fprintf(file, "%c", cur_char);
    }
    fclose(file); fclose(ftemp);
    return 0;
}

int main(int argc, char** argv){
    // Program to convert tabs to spaces

    int i, err;
    int num_processed_files = 0;

    // At least one argument, and not more than the max amount of files
    if (argc == 1){
        printf("No file provided!\n");
        return 1;
    } else if (argc > MAX_FILES){
        printf("Maximum amount of files is %i!", MAX_FILES);
    }

    // search for -h
    for (i = 1; i < argc; i++){
        if (strcmp(argv[i], "-h") == 0 ||  strcmp(argv[i], "--help") == 0 ) {
            return 0;
        }
    }

    // Search for -t
    for (i = 1; i < argc; i++){
        // found argument -TAB_COMMAND, that isn't last.
        if (argv[i][0] == '-' && 
            strlen(argv[i]) > 1 && argv[i][1] == TAB_COMMAND && 
            argc > i+1
        ){
            if(atoi(argv[i+1]) > 0){
                num_spaces = atoi(argv[i+1]);
                // skip the other part of the flag
                i += 1;
            } else {
                printf("Could not set tab length - is -t a positive number?!\n");
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
            num_processed_files++;
            err = process_file(argv[i]);
            if (err != 0){
                printf("File %s failed to convert.\n", argv[i]);
            }
        }
    }

    if (!num_processed_files){
        printf("No files were scanned. Did you mean to input a filename?\n");
    }

}
