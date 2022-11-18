#include <stdio.h>
#include <stdlib.h>

#define START           'S'
#define DESTINATION     'D'
#define PATH            '+'
#define WALL            '#'
#define UNSEEN          '.'
#define SEEN            '~'

// Got me upto a 7.5 on the testcases

typedef struct{
    char *grid;
    int maxX;
    int maxY;
} navigation_t;

typedef struct {
    int x;
    int y;
} position_t;

void freeGrid(navigation_t *nav){
    if(nav->grid == NULL){
    return;
    }
    free (nav->grid);
}


void inputGrid(navigation_t nav){
    char input[nav.maxX+1];
    int start_set = 0;
    for(int y = 0; y < nav.maxY; y++){
        printf("Input row %i: ",y);
        scanf(" %s",input );
        for(int x=0; x< nav.maxX; x++){
            nav.grid[y*nav.maxX+x] = input[x];
        if(input[x] == START && start_set == 1){
        printf("Extra starting point\n");
        nav.grid[y*nav.maxX+x] = WALL;
          }
         if (input[x] == START) start_set=1;
          } 
    } 
} 

void newGrid(navigation_t *nav){
    printf("Number of rows? ");
    scanf(" %i",&nav->maxY);
    printf("Number of columns? ");
    scanf(" %i",&nav->maxX);
    if (nav->maxX < 2 || nav->maxY < 2){
        printf("The number of rows and columns must be at least two\n");
    }else {
        freeGrid(nav);
        nav->grid = (char*) malloc(nav->maxX * nav->maxY * sizeof(char));
        inputGrid(*nav);
    }
}

void printGrid(navigation_t nav){
    for(int y = 0; y < nav.maxY; y++){
        for(int x=0; x<nav.maxX; x++){
            if(nav.grid[y*nav.maxX+x] == START ) printf("S");
           else if(nav.grid[y*nav.maxX+x] == DESTINATION ) printf("D");
           else if(nav.grid[y*nav.maxX+x] == PATH ) printf("+");
            else if(nav.grid[y*nav.maxX+x] == WALL ) printf("#");
            else if(nav.grid[y*nav.maxX+x] == UNSEEN ) printf(".");
            else if(nav.grid[y*nav.maxX+x] == SEEN ) printf("~");
        }
        printf("\n");
    }
}
position_t findStart(navigation_t nav){
    position_t pos;
    int contains_s =0, contains_d =0;
    if (nav.grid != NULL){
    for(int y = 0; y< nav.maxY; y++){
    for(int x = 0; x< nav.maxX; x++){
    if (nav.grid[y*nav.maxX+x] == START){
        contains_s = 1;
        pos.x = x;
        pos.y = y;
         }
    if (nav.grid[y*nav.maxX+x] == DESTINATION){
        contains_d =1;
         }
        }
    }
    if (contains_s == 0) printf("Grid contains no starting point\n");
    if (contains_d == 0) printf("Grid contains no destination\n");
    if (contains_s == 0 || contains_d == 0) {
        pos.x = -1;
        pos.y = -1;
    }
    }
    return pos;
}

int findPath(navigation_t nav, int x, int y, int length){
   if(nav.grid != NULL){
        if (x >= nav.maxX || y >= nav.maxY ||x < 0 || y < 0 ) return 0;
        if (nav.grid[y*nav.maxX+x] == WALL || nav.grid[y*nav.maxX+x] == SEEN || nav.grid[y*nav.maxX+x] == PATH )return 0;
        if (nav.grid[y*nav.maxX+x] == START && length > 0) return 0;
        if (nav.grid[y*nav.maxX+x] == DESTINATION) return length;
        if (nav.grid[y*nav.maxX+x] != START) nav.grid[y*nav.maxX+x] = PATH; 
    
        int nlength, elength, slength, wlength;
        
        if ((nlength = findPath(nav,x,y-1,length+1))) return nlength; 
        if ((elength = findPath(nav,x+1,y,length+1))) return elength; 
        if ((slength = findPath(nav,x,y+1,length+1))) return slength; 
        if ((wlength = findPath(nav,x-1,y,length+1))) return wlength; 
        if(nav.grid[y*nav.maxX+x] != START) nav.grid[y*nav.maxX+x] = SEEN;
    }
    return 0;
}

int longestPath(navigation_t nav, int x, int y, int length){
   if(nav.grid != NULL){
        if (x >= nav.maxX || y >= nav.maxY ||x < 0 || y < 0 ) return 0;
        if (nav.grid[y*nav.maxX+x] == WALL || nav.grid[y*nav.maxX+x] == SEEN || nav.grid[y*nav.maxX+x] == PATH )return 0;
        if (nav.grid[y*nav.maxX+x] == START && length > 0) return 0;
        if (nav.grid[y*nav.maxX+x] == DESTINATION) {return length;}
        if (nav.grid[y*nav.maxX+x] != START) nav.grid[y*nav.maxX+x] = PATH; 
    
        int nlength, elength, slength, wlength;
        
        if ((nlength = findPath(nav,x,y-1,length+1))) return nlength; 
        if ((elength = findPath(nav,x+1,y,length+1))) return elength; 
        if ((slength = findPath(nav,x,y+1,length+1))) return slength; 
        if ((wlength = findPath(nav,x-1,y,length+1))) return wlength; 
        if(nav.grid[y*nav.maxX+x] != START) nav.grid[y*nav.maxX+x] = SEEN;
    }
    return 0;
}
void resetPath(navigation_t nav){
    for(int y = 0; y<nav.maxY; y++){
    for(int x = 0; x<nav.maxX; x++){
    if(nav.grid[y*nav.maxX+x] == PATH ||nav.grid[y*nav.maxX+x] == SEEN ) nav.grid[y*nav.maxX+x] = UNSEEN;
        
    }
    }
}

int main(){
    char cmd;
    int length;
    navigation_t nav;
    nav.grid = NULL;
    nav.maxX = 0;
    nav.maxY = 0;
    position_t pos;
   
do{
    printf("Command? ");
    scanf(" %c", &cmd);
        switch(cmd){
        case 'q':
            printf("Bye!\n");
        break;
        
        case 'i':
             newGrid(&nav);
        break;
        
        case 'p':
            printGrid(nav);
        break;
        
        case 's':
            pos = findStart(nav);
            if (pos.x != -1 && pos.y !=-1 ){
                printf("The start is at x=%i and y=%i\n",pos.x,pos.y);
            }
        break;
        
        case 'f':
            pos = findStart(nav);
            length = findPath(nav,pos.x,pos.y,0);
            if (length == 0 ) printf("No path found\n");
            else printf("Found a path of length %i\n",length);
            printGrid(nav);
        break;
               
        case 'r':
            resetPath(nav);
        break; 
        
        case 'l':
        pos = findStart(nav);
            length = longestPath(nav,pos.x,pos.y,0);
        break;
                
        default:
            printf("Unknown command \'%c\'\n",cmd);
        break;
            }
        
    }while(cmd != 'q');
            freeGrid(&nav);
}
