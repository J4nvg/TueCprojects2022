#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "predefined.h"

#define BUFFSIZE 80

// Got me upto a 6 on the test cases

void addWord(entry_t concordance[],char *word){
    for(int i = 0; i<MAXWORDS;i++){
        if(concordance[i].word != NULL && strcmp(concordance[i].word,word) == 0)return;
    }
    for(int i = MAXWORDS-1; i>=0;i--){
            if(concordance[i].word != NULL){
        if(concordance[i].word != NULL && strcmp(concordance[i].word,word) < 0){
            free(concordance[i+1].word);
            concordance[i+1].word = (char *)malloc((strlen(word)+1)*sizeof(char));
            strcpy(concordance[i+1].word,word);
            return;
        }
        else{
            concordance[i+1].word = (char *)malloc((strlen(concordance[i].word)+1)*sizeof(char));
            strcpy(concordance[i+1].word,concordance[i].word);
            free(concordance[i].word);
            concordance[i].word = NULL;
            for(int n = 0; n<MAXINDEX; n++){
                concordance[i+1].indices[n] = concordance[i].indices[n];
                concordance[i].indices[n] = -1;
            }
        }
        }
        if(i==0 && concordance[i].word == NULL){
            concordance[i].word = (char *)malloc((strlen(word)+1)*sizeof(char));
            strcpy(concordance[i].word,word);
            return;
        }
    }
    
    
}


//Test func
void boebelsort(int a[],int arrlength){
     int temp;
    for(int i = 0; i<arrlength;i++){
       for(int n= 0; n<arrlength-1;n++)
       if(a[n] < a[n+1]){
        temp = a[n];
           a[n] = a[n+1];
           a[n+1] = temp;
       }
   }
      for(int i = 0 ; i< arrlength; i++){
    printf("a[%2.2i] = %d\n",i,a[i]);
   }
}
///////////

void printConcordance(entry_t concordance[]){
    int conc_empty = 1;
    for(int i = 0; i<MAXWORDS;i++){
     if(concordance[i].word != NULL) conc_empty =0;
    }
    if(conc_empty == 1) printf("The concordance is empty\n");
    if(conc_empty == 0){
        printf("Concordance\n");
        for(int i = 0; i<MAXWORDS;i++){
            if(concordance[i].word != NULL){
                printf("%10s:",concordance[i].word);
                for(int n = 0; n<MAXINDEX; n++){
                    if(concordance[i].indices[n] != -1){
                        printf(" %d",concordance[i].indices[n]);
                    }
                }
                 printf("\n");
            }
        }
    }
}

void addIndex(entry_t concordance[], char *word, int index){
    for(int i = 0; i<MAXWORDS ; i++){
        if(concordance[i].word != NULL && strcmp(word,concordance[i].word) == 0){
        for(int n = 0; n<MAXINDEX; n++){
            if(concordance[i].indices[n] == -1){
            concordance[i].indices[n] = index;
            return;
          }
      }
    }
    }
printf("Word %s not found\n",word);
}


void removeWord(entry_t concordance[],char *word){
    // int word_found = 0;
   for(int i = 0; i<MAXWORDS; i++){
   if(concordance[i].word != NULL && strcmp(concordance[i].word,word)==0){
        //  word_found = 1;
       free(concordance[i].word);
       concordance[i].word = NULL;
       for(int n = 0; n<MAXINDEX; n++){
           concordance[i].indices[n] = -1;
       }
       
       return;
    }
   }
}

void readFile(entry_t concordance[], char *filename, int *index){
    char content[BUFFSIZE];
    int wordcounter =0;
    FILE *fh; // filehandle
    fh = fopen(filename, "r");
    if(fh == NULL){ printf("Cannot open file %s\n",filename); return;}
    while(fscanf(fh, " %s", content) == 1){
    addWord(concordance,content);
    addIndex(concordance, content,*index);
    *index = *index + 1;
    wordcounter++;
    }
    printf("Added %i words to concordance\n",wordcounter);
    fclose(fh);
}

char *findWordAtIndex(entry_t concordance[],int index){
    for(int i =0; i< MAXWORDS; i++){
        for(int n =0; n<MAXINDEX; n++){
            if(concordance[i].indices[n] - index == 0){
                return(concordance[i].word);
            }
        }
    }
    return(NULL);
    printf("There is no word at index %i\n",index);
}

void printOriginalText(entry_t concordance[]){
    int maxIndex = 0;
    int index = 0;
    for(int i = 0; i<MAXWORDS;i++){
        for(int n = 0; n<MAXINDEX;n++){
            index = concordance[i].indices[n];
            if(index >= maxIndex){
                maxIndex = index;
            }
        }
    }
    if(maxIndex == 0) return;
    for(int i = 0; i<=maxIndex; i++){
    if(findWordAtIndex(concordance,i) == NULL) printf("? ");
    else{printf("%s ",findWordAtIndex(concordance,i));}
}
    printf("\n");
}


int main (void)
{
    
    // Test 
      
  int a[] = {1,3,7,9,0,2,4,5,8,6};
  int arrlength = 10;
    // test
   char cmd;
   char word[MAXWORDS];
   char filename[MAXWORDS];
   int index=0;
   
   entry_t concordance[MAXWORDS];
   for(int i = 0; i<MAXWORDS; i++){
       concordance[i].word = NULL;
       for(int n = 0; n<MAXINDEX; n++){
           concordance[i].indices[n] = -1;
       }
   }
   
    do{
    printf("Command? ");
    scanf(" %c",&cmd);
    switch(cmd){
        
        case 'q':
        for(int i = 0; i<MAXWORDS; i++){
            free(concordance[i].word);
        }
        printf("Bye!\n");
        break;
        
        case 'w':
        printf("Word? ");
        scanf(" %s", word);
        addWord(concordance, word);
        break;
        
        case 'p':
        printConcordance(concordance);
        break;
        
        case 'i':
        printf("Word index? ");
        scanf(" %s", word);
        scanf(" %i", &index);
        addIndex(concordance,word,index);
        break;
        
        case 'W':
        printf("Word? ");
        scanf(" %s", word);
        removeWord(concordance, word);
        break;
        
          case 'f':
        printf("Index? ");
        scanf(" %i", &index);
        if (findWordAtIndex(concordance, index) == NULL ) printf("There is no word at index %i\n",index);
        else printf("The word at index %i is %s\n",index,findWordAtIndex(concordance, index));
        break;
        
        case 'r':
        printf("File name? ");
        scanf(" %s",filename);
        readFile(concordance,filename,&index);
        break;
        
        case 'b':
        
        boebelsort(a,arrlength);
        break;
        
        case 'o':
        printOriginalText(concordance);
        break;
        
        default:
        printf("Unknown command \'%c\'\n",cmd);
        break;
    }
   }while(cmd != 'q');
 
}
