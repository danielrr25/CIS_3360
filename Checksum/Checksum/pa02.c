/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Daniel Rodriguez
| Language: c
|
| To Compile: javac pa02.java
| gcc -o pa02 pa02.c
| g++ -o pa02 pa02.cpp
| go build pa02.go
| python pa02.py //Caution - expecting input parameters
|
| To Execute: java -> java pa02 inputFile.txt 8
| or c++ -> ./pa02 inputFile.txt 8
| or c -> ./pa02 inputFile.txt 8
| or go -> ./pa02 inputFile.txt 8
| or python-> python pa02.py inputFile.txt 8
| where inputFile.txt is an ASCII input file
| and the number 8 could also be 16 or 32
| which are the valid checksum sizes, all
| other values are rejected with an error message
| and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Spring 2022
CIS3360-McAlpin PA 2 3
| Instructor: McAlpin
| Due Date: per assignment
|
+=============================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>



uint8_t eightbits(char *inputFile)
{
    uint8_t first = 0;
    int i;
    for (i=0; i<strlen(inputFile); i++)
    {
        first += inputFile[i];
    }
    return first;
}
uint16_t sixteenbits(char *inputFile)
{
    int i;
    uint16_t frame1 = 0;
    uint16_t frame2 = 0;
    
    for (i=0; i<strlen(inputFile); i++)
    {
        frame1 = inputFile[i];
        frame1 = frame1 << 8;
        frame1 += inputFile[++i];
        
        frame2 += frame1;
    }
    
    return frame2;
}
uint32_t thirtytwobits(char *inputFile)
{
    int i;
    uint32_t frameA = 0;
    uint32_t frameB = 0;
    
    for (i = 0; i < strlen(inputFile); i++)
    {
        frameA = inputFile[i];
        frameA = frameA << 8;
        frameA += inputFile[++i];
        frameA = frameA << 8;
        frameA += inputFile[++i];
        frameA = frameA << 8;
        frameA += inputFile[++i];        
        frameB += frameA;

        
    }
    return frameB;
}
void printInputfiles(char *inputFile)
{
    int i;
    for (i = 0; i < strlen(inputFile); i++ )
    {
        if (i % 80 == 0)
        {
            printf("\n");
        }
        printf("%c", inputFile[i]);
    }
}

int main(int argc, char **argv)
{
    //printf("whats your input size: 8, 16, 32? ");
    
    if (atoi(argv[2]) != 8 && atoi(argv[2]) != 16 && atoi(argv[2]) != 32)
    {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }
    
    if (argc != 3) {

           fprintf(stderr, "The number of arguments entered is not sufficient, try again!\n");
           return -999;

       }
    //the variables for each function
    uint8_t first = 0;
    uint16_t second = 0;
    uint32_t third = 0;
    
    
    int checkSumSize = atoi(argv[2]);
    //length of the string
    int strnum;
    //Array to store the characters
    char *inputFile;
    
    //file pointer to open the file, "r" for read
    FILE *file = fopen(argv[1], "r");
    //allocate memory for the array
    inputFile = malloc(sizeof(char)*2000);
    //get all the charcters from the file
    fread(inputFile, 2000, sizeof(char), file);
    
    
    //the length of the string
    strnum = strlen(inputFile);
    
    if (atoi(argv[2]) == 8)
    {
        first = eightbits(inputFile);
        
        printInputfiles(inputFile);
        printf("\n");
       // printf("%s\n", inputFile);
        printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, (unsigned long int)first, strnum);
    }
    else if (atoi(argv[2]) == 16)
    {
        if (strnum % 2 != 0)
        {
            //string concatination
            strcat(inputFile, "X");
           //inputFile[strnum] = 'X';
        }
        strnum = strlen(inputFile);

        second = sixteenbits(inputFile);
        
        printInputfiles(inputFile);
        printf("\n");
        printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, (unsigned long int)second, strnum);
    }
    else if (atoi(argv[2]) == 32)
    {
        strnum = strlen(inputFile);

        while (strnum % 4 != 0)
        {
            inputFile[strnum] = 'X';
            strnum = strlen(inputFile);
        }

        third = thirtytwobits(inputFile);
        printInputfiles(inputFile);
        printf("\n");
        printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, (unsigned long int)third, strnum);
    }

    return 0;
}
    
/*=============================================================================
| I [Daniel Rodriguez] (da007002) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
