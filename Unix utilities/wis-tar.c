#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
    
    if(argc <= 2){
        printf("wis-tar: tar-file file [...]\n");
        exit(1);
    } else{
        
        FILE *target;
        FILE *source;
        char fileName[100];
        target = fopen (argv[1] , "w");
 
              if(target == NULL){
                  printf("wisc-tar: cannot open file");
                 exit(1);
              }

        
        for (int i = 2; i < argc; ++i ){
            
            
            source = fopen(argv[i], "r");
            
            if(source == NULL){      
                printf("wis-tar: cannot open file\n");
                exit(1);
            }
            
            
            //write file name to target file
            strncpy(fileName, argv[i], 100);
            fwrite(&fileName, 1 , 100 , target);
            
            

            //create stat struct
            struct stat sb;
            //check struct
            if(stat(argv[i], &sb) == -1){
                printf("wis-tar: cannot get file size\n");
                exit(1);
            }

            //save file size
            long fileSize = sb.st_size;
            //write fileSize to file
            fwrite(&fileSize, 1 , sizeof(long), target);
            //copy contents of file
            
            //copy contents and write contents from source file to target
            char * line;
            size_t len = 0;
            while (getline(&line, &len, source) != -1) {
                //write to target file
                fprintf(target, "%s", line );
            }

            free(line);
            fclose(source);
            
           
        }
        fclose(target);
       
    }
    return 0;
  }
