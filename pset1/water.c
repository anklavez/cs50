#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Constant
    int bottles_of_water_per_min = 12;
    
    printf("Please provide the time for taking your shower (in minutes): ");
    
    int time = GetInt();
    
    printf("minutes: %d\n",time);
    printf("bottles: %d\n",bottles_of_water_per_min*time);
}