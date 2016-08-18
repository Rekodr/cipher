#include "cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void encrypt(const char* inputMessage, int shiftKey,const long int length, char* outputMess){
    //decrypting or encrypting
    for(int i=0; i < length; i++){
    	//low case char 
    	if(inputMessage[i] >= 'A' && inputMessage[i] <= 'Z'){
    		outputMess[i] = ( (inputMessage[i] - 'A') + shiftKey ) % 26 + 'A';
    	}
    	else if(inputMessage[i] >= 'a' && inputMessage[i] <= 'z'){
    			outputMess[i] = ( (inputMessage[i] - 'a') + shiftKey ) % 26 + 'a';
    	}
    	//other char
    	else
    			outputMess[i] =  inputMessage[i] ; 
    	
    }
 
}

int frequencyAnalyser(const char* input, const long int length, const char c){
    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int freq[26], mode, maxFreq = 0, shiftKey = 0, decryptionKey = 0;  

    for(int i=0; i<26; i++){
        freq[i] = 0;
    }
    
    for(int i=0; i<length; i++){
        for(int j = 0; j<26; j++){
            if(alphabet[j] == tolower(input[i])){
                freq[j] ++; 
                break; 
            }
        }
    }
    printf("\n---------------------------------------\n");
    printf("Frequency Analyser results\n");
    for(int i=0; i<26; i++){
        printf("\t%c: %d\n", alphabet[i], freq[i] );
        if(freq[i] >  maxFreq){
            maxFreq = freq[i]; 
            mode = i; 
        }
    }
    shiftKey =  alphabet[mode] - c ; 
    decryptionKey = 26 - shiftKey; 
    printf("\nMode: %c\n", alphabet[mode]);
    printf("Suggested shiftkey: %d\nDecryption key: %d\n", shiftKey, decryptionKey); 
    printf("---------------------------------------\n\n");
    return decryptionKey;
}


double wordAnalyser(const char* input, const long int length){
    long int count = 0, nValidWords = 0, input_nWords = 0;
    int n = 0; 
    FILE* systWord = NULL;
    char path[] ="/usr/share/dict/words";
    char word[150000][20]; 
    char temp[20];
    double correctness = 0; 

    if((systWord=fopen(path,"r")) == NULL){
        //wtf no file found
        printf("File not found booooooooooom\n");
    }

    while(!feof(systWord)){
         fscanf(systWord,"%s\n", word[count]);
         count++; 
    } 

    //read word by word from the input
    for(int i=0; i< length ; i++){
       if(tolower(input[i]) >= 'a' && tolower(input[i]) <= 'z' ){
         temp[n] = input[i];
         n++; 
       }
       else{
            temp[n] = '\0';
            if(strlen(temp) >0 ){
               input_nWords++; 
               for(int j=0; j< count;j++ ){
                if(strcasecmp(temp,word[j]) == 0){
                     nValidWords++; 
                     break;
                }; 
               }
            }
            n = 0;
       }
    }
    
    correctness =  (100.0 * nValidWords)/ input_nWords ; 

     printf("---------------------------------------\n");
     printf("Words Analyser results\n");
     printf("\tnumber of input words: %ld\n", input_nWords);
     printf("\tnumber of valid words: %ld\n", nValidWords);
     printf("\tpercentage correct: %.2lf\n", correctness);
     printf("---------------------------------------\n");
    for(int i=0; i< length; i++){

    }

    fclose(systWord);
    return correctness ; 
}