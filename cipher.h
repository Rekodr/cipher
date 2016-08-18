#ifndef ENCRYPTOR_H_
#define ENCRYPTOR_H_

void encrypt(const char* inputMessage, const int shiftKey, const long int length, char* outMessage);
int frequencyAnalyser(const char* input, const long int length, const char c);
double wordAnalyser(const char* input, const long int length);
#endif