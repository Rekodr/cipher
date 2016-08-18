#include <stdio.h>
#include <stdlib.h>
#include "cipher.h"
#include <string.h>
#include <ctype.h>


#define _DEGUG_ 0

#define precision 80 

int main(int argc, char* argv[]){
    
    if(argc < 2){
    	fprintf(stderr, "no input file.\n");
    	return -1;
    }
    
    if(argc > 3){
        fprintf(stderr, "Too many arguments.\n");
    }

    FILE* fin = NULL; 
    FILE* fout =NULL; 
    if((fin = fopen(argv[1], "r")) == NULL){
    	fprintf(stderr, "File: %s not found.\n", argv[1]);
    	return -2; 
    }
    
    int shift; 
    char foutExtension [] = ".dec";
    char* file_buffer;
    long int fileLength = 0; 
    char freqLetters[] = "etaoinsrhldcumfpgwybvkxjqz" ; 
    char* foutName = (char*) malloc(sizeof(char) * (strlen(argv[1]) + 4)) ; 
    strcpy(foutName,argv[1]);
    strcat(foutName, foutExtension);
    double correctess  = 0 ; 

    fseek(fin, 0, SEEK_END);
    fileLength = ftell(fin);
    rewind(fin);
    file_buffer = (char*) malloc(sizeof(char) * (fileLength)) ; 
    char* outMess = (char*) malloc( sizeof(char) * fileLength); 
    fread(file_buffer, 1, fileLength, fin);
    file_buffer[fileLength] = '\0';
    fclose(fin);

    if(argc == 3){
        if(sscanf(argv[2],"%d", &shift) != 1){
        fprintf(stderr, "input: %s is not a valid shifk key\n", argv[2]);
        return - 1;
        }
    
        if(shift < 0 || shift > 25){
        fprintf(stderr, "%d is not a valid shift key value\n", shift);
        return -1; 
        }
        shift = 26 - shift;
        encrypt(file_buffer, shift, fileLength, outMess); 
    } else{
         for(int i=0; i < 26; i++){
            shift = frequencyAnalyser(file_buffer, fileLength, freqLetters[i]);
            encrypt(file_buffer, shift, fileLength, outMess); 
            correctess =  wordAnalyser(outMess, fileLength);
            if(correctess > precision){
                printf("decryption succeds with %.2lf %% confidence.\n\n", correctess );
                break ;
            }
         }
    }
    
    if((fout = fopen(foutName,"w")) == NULL){
    	fprintf(stderr, "FILE: %s not found\n", foutName);
    }

    fwrite(outMess,1,fileLength, fout);



    #if _DEGUG_
        printf("%s\n\n", file_buffer);
        for(int t=0; t<fileLength;t++){
    	   printf("%c",outMess[t] );
        }
        printf("\n");
    #endif

   
    //dealloction 
    free(file_buffer);
    free(outMess);
    free(foutName);
    fclose(fout);
	return 0 ; 
}

