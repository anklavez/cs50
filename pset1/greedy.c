#include <stdio.h>
#include <cs50.h>
#include <math.h>

/* function declaration */
void modulo(int *cents, int coin, int *count);

int main(void)
{
    printf("O hai! How much change is owed?");
    
    int cents = 0;
    
    //user input process
    do{
        float input = GetFloat();
        if(input < 0){
            printf("How much change is owed?\n");
        }else{
            input = input*100;
            double d = round(input);
            cents = (int)d;
        }
    }while(cents <= 0);
    
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    
    int count = 0;
    
    int step = 1;
    
    do{
        switch(step){
            case 1:
                    modulo(&cents,quarter,&count);
                    step++;
                    break;
            case 2: 
                    modulo(&cents,dime,&count);
                    step++;
                    break;
            case 3:
                    modulo(&cents,nickel,&count);
                    step++;
                    break;
            case 4:
                    modulo(&cents,penny,&count);
                    break;
        }
    }while(cents!=0);
    
    printf("%d\n",count);
}

void modulo(int *cents, int coin, int *count){
    int modulo_value =(*cents)%coin;
    if(modulo_value >= 0 && modulo_value != (*cents)){
        int int_part = (*cents)/(coin);
        *count += int_part;
        *cents = (*cents) - ((coin)*int_part);
    }
}