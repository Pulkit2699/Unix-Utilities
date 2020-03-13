#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>




int main(int argc, char *argv[]){
    
    if(argc == 1 || argc > 2){
        printf("wis-untar: tar-file\n");
        exit(1);
    }
    
    FILE *tar_file;
    FILE *untar_file;
    
    tar_file = fopen(argv[1], "r");
    
    if(tar_file == NULL){
        printf("wis-untar: cannot open file\n");
        exit(1);
    }
    char extractFileName[100];
    long fileSize;
    
    while(fread(extractFileName, 100, 1, tar_file) != 0){
        //get file name
        //skip 8 bytes to skip file size
        fread(&fileSize, 8, 1, tar_file);
        
        //convert file size from binary to long
        //open file and create correct size
        //temp array to store contents
        char contents[1024];
        untar_file = fopen(extractFileName,"w+");
        if (untar_file == NULL) {
            printf("wis_untar: cannot open file\n");
            exit(1);
        }
        //copy rest of contents
        fread(contents, fileSize , 1, tar_file);
        fwrite(contents, fileSize, 1 , untar_file);
        fclose(untar_file);
        
    }
    fclose(tar_file);
    exit(0);
}
