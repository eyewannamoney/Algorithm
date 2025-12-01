#include <stdio.h>

unsigned int sumAsciiValues(char* key){
    int number = 0;
    while(*key){
        number += *key++;
    }

    return number;
}

unsigned int asciiShiftSum(char* key){
    int number = 0;
    while(*key){
        number += *key++;
        if(*key){
            number += ((int) *key++) << 8;
        }
    }
    return number;
}