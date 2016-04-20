#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    int height;
    printf("height: ");
    do{
        height = GetInt();
        if(height==0){
            return 0;
        }
        if(height<1||height>23){
            printf("Height: %d\n",height); 
        }
    }while(height<1||height>23);
    
    int initial_hashes_lenght = 2;
    
    for(int i = 0; i < height; i++){
        
        int spaces_lenght = height-initial_hashes_lenght+1;
        
        //print spaces
        for(int s = 0; s < spaces_lenght; s++){
            printf(" ");
        }
        
        //print hashes
        for(int h = 0; h < initial_hashes_lenght; h++){
            printf("#");
        }
        
        printf("\n");
        
        initial_hashes_lenght++;
    }
}


