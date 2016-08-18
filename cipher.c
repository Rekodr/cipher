/*
* Author: Recodeo Rekod
* project name: caesar cipher
*
*/

#include "cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DICTIONARYPATH "/usr/share/dict/words"


/*************************************************************************************************
* This function (de)encrypes txt passed as char* by shifting the characters by the shiftkey.
* param:
*       inputMessage(char*) : message "text" to be encryted. 
*       shiftkey(int) : indicate by how much the character in inputMessage will be shifted.
*       length(int) : size of inputMessage
*       outputMsg(char*) : the encrypted mgs
* 
**************************************************************************************************/
char* encrypt(const char* inputMessage, const int shiftKey,const long int length, char* outputMsg){
   
    //loop through the entire char* 
    for(int i=0; i < length; i++){
    	//low case char 
    	if(inputMessage[i] >= 'A' && inputMessage[i] <= 'Z'){

    		outputMsg[i] = ( (inputMessage[i] - 'A') + shiftKey ) % 26 + 'A'; //(de)encryption happens here.
    	}
    	else if(inputMessage[i] >= 'a' && inputMessage[i] <= 'z'){
    			outputMsg[i] = ( (inputMessage[i] - 'a') + shiftKey ) % 26 + 'a'; //(de)encryption happens here.
    	}
    	//none alphebit char are just letf as they are. You could change this. 
    	else
    			outputMsg[i] =  inputMessage[i] ; 
    	
    }
  return outputMsg; 
}


/*************************************************************************************************
* This function analyzes the frequency of each character in the input char* and return a 
* suggestion of the encryption key. 
* param:
*       inpu(char*) : intput to be analyzed. 
*       length(int) : size of inputMessage.
*       c(char) : post used character in a language.
*
* return:
        int : suggested key 
**************************************************************************************************/
int frequencyAnalyser(const char* input, const long int length, const char c){

    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    /*
     * freq : keeps track of the frequency of each char
     * mode : stores the index of the most used char
    */ 
    int freq[26], mode, maxFreq = 0, shiftKey = 0, decryptionKey = 0;  
    
    //basic array initialization
    for(int i=0; i<26; i++){
        freq[i] = 0;
    }
    
    for(int i=0; i<length; i++){
        for(int j = 0; j<26; j++){
        	// check for matching characters. 
            if(alphabet[j] == tolower(input[i])){
                freq[j] ++; //if matched, increase the frep of the corresponding char
                break; 
            }
        }
    }

    // this section under this comment just print the freq of each char in the input(char*)
    printf("\n---------------------------------------\n");
    printf("Frequency Analyser results\n");
    for(int i=0; i<26; i++){
        printf("\t%c: %d\n", alphabet[i], freq[i] );
        if(freq[i] >  maxFreq){
            maxFreq = freq[i]; 
            mode = i; 
        }
    }
    
    shiftKey =  alphabet[mode] - c ; // suggesting a key 
    decryptionKey = 26 - shiftKey; 

    printf("\nMode: %c\n", alphabet[mode]);
    printf("Suggested shiftkey: %d\nDecryption key: %d\n", shiftKey, decryptionKey); 
    printf("---------------------------------------\n\n");
    return decryptionKey;
}

/*************************************************************************************************
* This function analyzes world in the input char* using a dictionary. 
* param:
*       input(char*) : intput to be analyzed. 
*       length(int) : size of input.
*
* return:
        double : percentage of coorect worlds
**************************************************************************************************/

#define n_world 150000 
#define max_world_size 20

double wordAnalyser(const char* input, const long int length){

    long int count = 0, nValidWords = 0, input_nWords = 0;
    int n = 0; 
    char word[n_world][max_world_size]; //
    char temp[max_world_size];
    double correctness = 0; 
    FILE* systWord = NULL;

    char path[] = DICTIONARYPATH; 

    

    if((systWord=fopen(path,"r")) == NULL){
        //wtf no file found
        printf("File not found booooooooooom\n");
    }
    
    //loading the entire dictonay in memory --> doing this increase speed actually
    while(!feof(systWord)){
         fscanf(systWord,"%s\n", word[count]);
         count++; 
    } 

    //read char by char from the input
    for(int i=0; i< length ; i++){
       if(tolower(input[i]) >= 'a' && tolower(input[i]) <= 'z' ){
         temp[n] = input[i];
         n++; 
       }
       else{
            temp[n] = '\0'; //if an none char is found this means a world was read 
            if(strlen(temp) >0 ){
               input_nWords++; 
               for(int j=0; j< count;j++ ){
               	// checking to see if the world in temp is exiisting in the dictionary
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
   
     
    //don't forget to close the file
    fclose(systWord);
    return correctness ; 
}