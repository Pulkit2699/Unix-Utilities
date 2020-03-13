#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    
    if(argc < 2){
        printf("wis-grep: searchterm [file ...]\n");
        //program has an error
        exit(1);
    }
    
    char* searchTerm = argv[1];
    
    if(argc == 2){
        //array of characters that store user input
        char input[1000];
        
        while(1){
            //read user input
           if(fgets(input, 1000, stdin) == NULL){
             
              exit(1);   
            }
            //check if search term is in the user input
            if(strstr(input, searchTerm) != NULL){
                printf("%s", input);
            }

        }

        return 0;

    } else{
        //store line and length of line read from a specific file
        char* line = NULL;
        size_t len = 0;
        // loop through all files line by line for search term
        for(int i = 2; i < argc; ++i){
            //store fileName
            char* fileName = argv[i];
            //open file
            FILE* f = fopen(fileName, "r");
            //check if file can be opened
            if(f == NULL){
                printf("wis-grep: cannot open file\n");
                exit(1);
            }
            //read file line by line
            while(getline(&line, &len, f) != -1){
                //print line if it contains the search term
                if(strstr(line, searchTerm) != NULL){
                    printf("%s", line);
                }
               
            }
            
            free(line);
            fclose(f);
        }
    }
    
    return 0;
}
