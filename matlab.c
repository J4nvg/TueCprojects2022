//Matlab assignment
// Jan van Gestel

#include <stdio.h>
#include <math.h>

// Got me upto a 8 on the testcases

#define MAXSIZE 10
void print (float matrix[MAXSIZE][MAXSIZE], int rows, int columns, char name){
    printf("Matrix %c (%d X %d):\n",name,rows,columns);
    int i, j = 0; // Make counters
    for (i = 0; i < rows; i++){ // Counter for the amount of rows
        for (j = 0; j < columns; j++){ // Counter for the amount of columns
            printf("%8.2f",matrix[i][j]); // Field width 8, accuracy 2
        }
        
        printf("\n"); // New line for new row
    }
}

void mult(
    float matrixA[MAXSIZE][MAXSIZE], int rowsA, int columnsA,
    float matrixB[MAXSIZE][MAXSIZE], int rowsB, int columnsB,
    float matrixC[MAXSIZE][MAXSIZE], int rowsC, int columnsC
    ){
      for (int r = 0; r < rowsA; r++){ 
        for (int c = 0; c < columnsB; c++){ 
            matrixC[r][c] = 0;
            for(int i = 0; i < columnsA; i++){
                matrixC[r][c] = matrixC[r][c] + (matrixA[r][i] * matrixB[i][c]);
            }
        }
    }
    }

int main(){
    //Initialising
    char cmd;
    float matrixA[MAXSIZE][MAXSIZE] ={0} , matrixB[MAXSIZE][MAXSIZE] ={0} , matrixC[MAXSIZE][MAXSIZE] ={0};
    int rowsA= 1, columnsA= 1, rowsB= 1, columnsB= 1, rowsC= 1, columnsC = 1, temprows = 0, tempcolumns = 0;
    do {
        printf("Command? ");
        scanf(" %c",&cmd);
        if (cmd == 'q'){ // Quit command
        break;
        } 
        
         else if (cmd == 'a'){ // Matrix a command
            print (matrixA, rowsA, columnsA, 'A');
        }
        
        else if (cmd == 'b'){ // Matrix B command
            print (matrixB, rowsB, columnsB, 'B');
        }
        
        else if (cmd == 'c'){ // Matrix C command
            print (matrixC, rowsC, columnsC, 'C');
        }
        
        else if (cmd == 'B'){ // Copying matrix A to B
            int i, j= 0;
            rowsB = rowsA;
            columnsB = columnsA;
                for(i=0; i < rowsA; i++){
                    for(j=0; j< columnsA; j++){
                        matrixB[i][j] = matrixA[i][j];
                    }
                }
                
        }
        
        else if (cmd == '+'){ // addition command
        int i, j= 0;
            if (rowsA != rowsB || columnsA != columnsB){
                printf("Dimensions of A & B do not match\n");
            }
            else {
                rowsC = rowsA;
                columnsC = columnsA;
                for(i=0; i < rowsC; i++){
                    for(j=0; j< columnsC; j++){
                        matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
                    }
                }
            }
        }
        // note to self: revise Transpose
        else if (cmd == 't'){// transpose command
            int temprows, tempcolumns = 0;
            int matrixT[MAXSIZE][MAXSIZE];
            temprows = rowsA;
            tempcolumns = columnsA;
            for(int i = 0; i < columnsA; i++){
                for(int j = 0; j< rowsA; j++){
                    matrixT[i][j] = matrixA[j][i];
                }
            }
            rowsA = tempcolumns;
            columnsA = temprows;
            for(int i = 0; i < rowsA; i++){
                for(int j = 0; j< columnsA; j++){
                    matrixA[i][j] = matrixT[i][j];
                }
            }
        }
        
        else if (cmd == '*'){
            if (columnsA == rowsB){
                rowsC = rowsA;
                columnsC = columnsB;
                mult(matrixA, rowsA, columnsA,
                    matrixB, rowsB, columnsB,
                    matrixC, rowsC, columnsC);
            }
            else printf("Dimensions of A & B do not match\n");
        }
        
        else if (cmd == 'I'){
            printf("Size of matrix A (rows columns)? ");
            scanf("%i",&temprows);
            scanf("%i",&tempcolumns);
            if (temprows <= 0 || temprows > MAXSIZE || tempcolumns <= 0 || tempcolumns > MAXSIZE || tempcolumns != temprows){
                printf("Rows & columns must be equal and between 1 and 10\n");
            }
            else {
                int i, j = 0;
                columnsA = tempcolumns;
                rowsA = temprows;
                for(j = 0; j < rowsA; j++){
                    for(i = 0; i< columnsA; i++){
                        if ( i == j){
                            matrixA[i][j] = 1;
                        }
                        else matrixA[i][j] = 0;
                    }
                    
                } // Close for loops
                
            } // Close setting 1 case
        } // Close I command
        
        else if (cmd == 'A'){
            printf("Size of matrix A (rows columns)? ");
            scanf("%i",&temprows);
            scanf("%i",&tempcolumns);
            if (temprows <= 0 || temprows > MAXSIZE || tempcolumns <= 0 || tempcolumns > MAXSIZE){
                printf("Rows & columns must be between 1 and 10\n");
            }
            else {
                int i, j = 0;
                columnsA = tempcolumns;
                rowsA = temprows;
                for( i = 0; i < rowsA; i++){
                    printf("Row %i? ", i);
                    for( j = 0; j < columnsA; j++){
                        scanf("%f",&matrixA[i][j]);
                    }
                }
            }
        }
      
        
        else printf("Unknown command '%c'\n",cmd);
    } while (cmd != 'q');
    printf("Bye!\n");
}
