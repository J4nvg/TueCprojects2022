#include <stdio.h>
#include <string.h>
#include <math.h>

// Got me upto a 5 on the testcases


void printArray(char str[], int length)
{
    for(int i = 0; i < length; i++ ){
        if (str[i] == '\0' && i == 0) printf("[\\0");
        else if (i == 0 && str[i] != '\0') printf("[%c", str[i]);
        else if (str[i] == '\0') printf(",\\0");
        else if (str[i] == '\n') printf(",\\n");
        else printf(",%c", str[i]);
        }
        printf("]\n");
    }

void printString(char str[]){
    int i = 0;
    if (i == 0) putchar('"');
    while (str[i] != '\0'){
     putchar(str[i]);
     i++;
    }
    putchar('"');
    putchar('\n');
}
#define LENGTH 30

void readLine(char str[], int length){
    int i= 0;
    char c;
    do {
        c = getchar();
        if(i<LENGTH){
            str[i] = c;
        }
        i++;
    } while(c != '\n');
    if(i<LENGTH){
        str[i-1] = '\0';
    }else{
        str[LENGTH-1] = '\0';
    }
}

int findFirstOccurence(char str[], char aChar)  {  
    int i = 0; // Setup counter
    while (str[i] != '\0'){ // walk trough array and end at the end
        if (aChar == str[i]){   // if aChar == array character
            return(i);          // return the index value
            }
            i++;
        }
        return(-1); // aChar turns out not to be in the array
}

int readInt(char str[], int length){
    int integer = 0;
    int power = 0;
    
    for(int i = length -1; i>= 0;i--){
        if (str[i] != '\0' && str[i]>='0' && str[i]<='9'){
            int value = str[i] - '0';
            integer += value*pow(10,power);
            power++;
        }
       }
       return integer;
    }

int main (void){
    char inputString[LENGTH] = "";
    char inputString1[LENGTH] = "";
    char currString[LENGTH] = "";
    do {
        printf("Command? ");
        readLine(inputString, LENGTH);
        switch (inputString[0]){
            case 'q':
                printf("Bye!\n");
                break;
            case 'p':
            printf("The current string is: ");
            printString(currString);
                break;
            case 'a':
             printf("The current array is: ");
             printArray(currString, LENGTH);
                break;
            case 's':
            currString[0] = '\0';
            printf("Please enter a string? ");
            readLine(currString, LENGTH);
                break;
                
            case 'o':
            printf("Find first occurrence of which character? ");
            readLine(inputString1, LENGTH);
            int firstOccurrence = findFirstOccurence(currString, inputString1[0]);
            printf("The first occurrence of '%c' is at index %d\n", inputString1[0], firstOccurrence);
               break;
            default:
                printf("Unknown command '%c'\n",inputString[0]);
                break;
        }
    } while (inputString[0] != 'q');
}
