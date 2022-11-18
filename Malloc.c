#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 30

// Got me upto a 6 on the testcases

struct person {char *name;float height;};

struct person *removeAllPersons(struct person *persons, int nrPersons){
     int n = nrPersons;
    nrPersons = 0;
    for (int i = 0; i<n; i++){
        free(persons[i].name);
        persons[i].name = NULL;
    }
    free(persons);
    persons = NULL;
    return persons;
}

void printPersons (struct person persons[], int nrPersons, int from, int to){
 int first = 1;
  printf("[");
  for(int i = from ; i<to; i++){ 
    if(persons[i].name != NULL && nrPersons > 0){
              if (first > 0){
                  first= -1;
                  printf("(\"%s\"",persons[i].name);
              } 
              else printf(",(\"%s\"",persons[i].name);
              printf(",%.3f)", persons[i].height);
                         }
  }
      printf("]\n");
}

void insertPerson(struct person persons[],int nrPersons, int newEntry, char *newName,float newHeight){
    persons[newEntry].name = (char *) malloc((strlen(newName)+1)*sizeof(char));
    strcpy(persons[newEntry].name, newName);
    persons[newEntry].height = newHeight;
}

void replacePerson(struct person persons[],int nrPersons, int newEntry, char *newName,float newHeight){
    free(persons[newEntry].name);
    persons[newEntry].name = NULL;
    persons[newEntry].name = (char *) malloc((strlen(newName)+1)*sizeof(char));
    strcpy(persons[newEntry].name, newName);
    persons[newEntry].height = newHeight;
}


void maxHeight (struct person persons[], int nrPersons, float *max){
    if (nrPersons != 0){
        *max = persons[0].height;
        for (int i = 1; i < nrPersons; i++){
            if (persons[i].height > *max) *max = persons[i].height;
        }
    }
}

float minHeight (struct person persons[], int nrPersons){
    int n =0;
    float minHeight = 0;
    if (nrPersons == 0) return 0;
    else {
        while (minHeight == 0 && n< nrPersons){
            minHeight = persons[n].height;
            n++;
            
        }
        for (int i = 0; i < nrPersons; i++){
            if (persons[i].height != 0 && persons[i].height < minHeight) minHeight = persons[i].height;
        }
        return minHeight;
    }
}

int main(){
    char cmd;
    char newName[80] = "";
    char Name[80] = "";
    struct person *persons;
    persons = NULL;
    int nrPersons = 0, newEntry = 0,Entry = 0;
    float Height = 0, newHeight = 0., maxheight = 0;
    float *max = &maxheight;
    do{
        printf("Command? ");
        scanf(" %c",&cmd);
        switch(cmd){
            case 'q':
                printf("Bye!\n");
            break;
            
             case 'n':
             removeAllPersons(persons,nrPersons);
                printf("Entries? ");
                scanf(" %d", &nrPersons);
                persons = (struct person *)malloc(nrPersons * sizeof(struct person));
                if (persons == NULL){
                    printf("malloc returned NULL");
                    return 0;
                }
                for (int i = 0; i<nrPersons; i++){
                    persons[i].name = NULL;
                    persons[i].height = 0;
                }
            break;
            
            case 'i':
                  printf("Index? ");
                scanf(" %d",&Entry);
                    printf("Name? ");
                scanf("%s",Name);
                        printf("Height? ");
                    scanf("%f",&Height);
                        if(Height <= 0) printf("Height must be larger than zero\n");
                        else if(persons[Entry].name != NULL || persons[Entry].height != 0 ){
                            printf("Entry %i is already occupied by (\"%s\",%.3f)\n",Entry,persons[Entry].name,persons[Entry].height);
                        }
                        else{
                            newEntry = Entry;
                            newHeight = Height;
                            strcpy(newName,Name);
                            insertPerson(persons,nrPersons,newEntry,newName,newHeight);
                        }
            break;
            
            case 'h':
                printf("Min: %.3f\n",minHeight(persons,nrPersons));
                maxHeight(persons,nrPersons,max);
                printf("Max: %.3f\n", *max);
                printf("Range: %.3f\n", *max - minHeight(persons,nrPersons));
            break;
            
            case 'r':
                printf("Index? ");
                scanf(" %d",&Entry);
                    printf("Name? ");
                scanf("%s",Name);
                        printf("Height? ");
                    scanf("%f",&Height);
                if(Height <= 0) printf("Height must be larger than zero\n");
                 else{
                            newEntry = Entry;
                            newHeight = Height;
                            strcpy(newName,Name);
                            replacePerson(persons,nrPersons,newEntry,newName,newHeight);
                        }
            break;
            
             case 'p':
                printPersons(persons, nrPersons,0,nrPersons);
            break;
            
            default:
                printf("Unknown command \'%c\'\n", cmd);
            break;
        }
    } while(cmd != 'q');
    removeAllPersons(persons,nrPersons);
}