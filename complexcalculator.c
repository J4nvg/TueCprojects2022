#include <stdio.h>
//Jan van Gestel//
//Got me upto a 10 on the testcases
int main (void)
{
    char cmd;
    float curr_re = 0.0, curr_im = 0.0, new_re = 0.0, new_im = 0.0;
    int power = 0;
    printf("** Complex Calculator **\n");
do {
    printf("Operation [0+-*crpq]? ");
    scanf(" %c", &cmd);
    if (cmd == '+'){ // Plus operator
        printf("Complex operand? ");
        scanf(" %f %f", &new_re, &new_im);
        curr_re = curr_re + new_re;
        curr_im = curr_im + new_im;
    }
    else if (cmd == '-'){ // Minus operator
        printf("Complex operand? ");
        scanf(" %f %f", &new_re, &new_im);
        curr_re = curr_re - new_re;
        curr_im = curr_im - new_im;
    }
    else if (cmd == '0'){
        curr_re = 0;
        curr_im = 0;
    }
    else if (cmd == 'c'){
        curr_im = curr_im * -1;
    }
    else if (cmd == '*'){ // Multiplying
        printf("Complex operand? ");
        scanf(" %f %f", &new_re, &new_im);
       float temp_re = curr_re * new_re - curr_im * new_im;
       float temp_im = curr_re * new_im + curr_im * new_re;
        curr_re = temp_re;
        curr_im = temp_im;
    }
    else if (cmd == 'r'){ // Raising to the power of n
        printf("Natural operand? ");
        scanf(" %d", &power);
        float temp_im = 0.0, temp_re = 0.0, pow_im = 0.0, pow_re = 0.0;
        
        if (power == 0){
            curr_re = 1;
            curr_im = 0;
        }
        else if (power >= 2){
            temp_re = curr_re;
            temp_im = curr_im;
        for (int i = 0; i < power-1; i++){
            pow_re = curr_re * temp_re - curr_im * temp_im;
            pow_im = curr_re * temp_im + curr_im * temp_re;
            temp_re = pow_re;
            temp_im = pow_im;
        } 
        curr_re = temp_re;
        curr_im = temp_im;
        }
    }
    
    else if (cmd == 'p'){ // Plotting inner = y && outer = x
        int temp_re = 0, temp_im = 0;
        temp_im = (int)curr_im, temp_re = (int)curr_re;
        for (int outer=10; outer >= -10; outer--){
            for (int inner=-10; inner <= 10; inner++){
                if (outer == 0 && inner == 0 && outer == temp_im && inner == temp_re){
                    printf("*");
                }
                
                 else if (outer == 0 && inner == 0 ){
                    printf("+");
                }
                
                else if (outer == 0){
                    printf("-");
                }
                
                else if (inner == 0){
                    printf("|");
                }
                
                else if (temp_im == outer && temp_re == inner){
                    printf("*");
                }
               else { 
                   printf(".");
               }
            }
            printf("\n");
        }
    }
    
    else if (cmd != 'q'){ // Quitting
        printf("Invalid command '%c'\n", cmd);
    }
    
    if (curr_im >= 0) {
    printf("Current value is %f+%fi\n",curr_re,curr_im);
    }
    else {
        printf("Current value is %f%fi\n",curr_re,curr_im);
    }
} while(cmd != 'q');
    
printf("Bye!\n");
return 0;
}