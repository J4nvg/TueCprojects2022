#include <stdio.h>
#include <math.h>
#include <string.h>
#define LENGTH 100

// Got me upto a 6 on the testcases

void printString(char string[]){
    for(int i = 0; i < LENGTH; i++){
         if(string[i] == '\0') printf("\\0");
        else printf("%c",string[i]);
    }
    printf("\n");
}

void insertName(char *startPos[], int *pnrNames, char newName[]){
    strcpy(startPos[*pnrNames],newName);
    startPos[*pnrNames+1] = startPos[*pnrNames] + strlen(newName) + 1;
    (*pnrNames)++;
}

void printName(char names[], char *startPos[], int nrNames){
    for(int i=0; i< nrNames; i++){
        printf("startPos[%d]=%02ld ",i, startPos[i]-startPos[0]);
        printf("length=%02ld ", strlen(startPos[i])+1);
        printf("string=\"%s\"\n",startPos[i]);
    }
}

int totalLength(char *startPos[], int nrNames){
      int sum = 0;
    for(int i=0; i<nrNames; i++){
        sum = sum + (strlen(startPos[i])+1);
    }
    return sum;
}

int lookupNamePos(char names[], char *startPos[], int nrNames, char name[]){
    int place = 0; int found = 0;
    for(int i=0; i<nrNames; i++){
        if (strcmp(startPos[i],name) == 0 ) {
            found = 1;
            place = startPos[i] - startPos[0];
        }
    }
    if (found == 1)return place;
        else return -1;
}

void removeName(char *startPos[], int *pnrNames, char remName[]){
    for(int i=0; i<*pnrNames; i++){
        if(strcmp(startPos[i],remName) == 0){
            startPos[i] = startPos[*pnrNames-1];
            startPos[*pnrNames-1] = startPos[*pnrNames];
            (*pnrNames)--;
            break;
        }
        else if(i == *pnrNames) break;
    }
}

int main(){
    char names[LENGTH] = "";
    char name[LENGTH] = "";
    char cmd;
    char * startPos[LENGTH];
    *startPos = names;
    int nrNames= 0;
    int *pnrNames = &nrNames;
    do{
        printf("Command? ");
        scanf(" %c",&cmd);
            if (cmd == 'q'){
                break;
            }
            
            else if (cmd == 'p'){
                printString(names);
            }

            else if (cmd == 'i'){
                printf("Name? ");
                scanf("%s", name);
                insertName(startPos, pnrNames, name);
            }

             else if (cmd == 'n'){
                printName(names,startPos,nrNames);
            }

            else if (cmd == 'e'){
                printf("Total length is %i\n",totalLength(startPos,nrNames));
            }
            
            else if (cmd == 'l'){
                printf("Name? ");
                scanf("%s", name);
                printf("\"%s\" has index %i\n",name,lookupNamePos(names,startPos,nrNames,name));
            }
            
            else if (cmd == 'r'){
                 printf("Name? ");
                 scanf("%s", name);
                 removeName(startPos, pnrNames,name);
            }   
            
        else printf("Unknown command '%c'\n",cmd);
    } while(cmd != 'q');
    printf("Bye!\n");
}