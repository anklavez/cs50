/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t  BYTE;

// define structure for FAT block size
typedef struct
{
    BYTE  data[512];
} __attribute__((__packed__))
JPGBLOCK;


// prototypes
bool check_for_jpg_header(JPGBLOCK block);

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 1)
    {
        printf("Usage: ./recover no arguments\n");
        return 1;
    }
    
    // open file with images
    FILE* file = fopen("card.raw", "rb");
    if (file == NULL)
    {
        printf("Could not open %s.\n", "card.raw");
        return 2;
    }
    
    JPGBLOCK block;
    
    // image counter
    int jpg_counter = 0;
    
    // arrays of characters for keeping file name
    char names[8];
    
    FILE* jpgFile = NULL;
    
    while(fread(&block, sizeof(block), 1, file) == 1)
    {
        // check if found new JPEG header
        if (check_for_jpg_header(block))
        {
            // if there is opened file - close it and create new one.
            if (jpgFile != NULL)
            {
                fclose(jpgFile);
                jpgFile = NULL;
            }
            sprintf(names,"%03d.jpg", jpg_counter);
            jpgFile = fopen(names,"wb");
            
            if (file == NULL)
            {
                printf("Could not open %s.\n", names);
                return 2;
            }
            fwrite(block.data,sizeof(block.data),1,jpgFile);

            jpg_counter++;
        }
        else
        {
            // if file already has opened, write data to it
            if (jpgFile != NULL)
            {
                fwrite(block.data,sizeof(block.data),1,jpgFile);  
            }
        }
    }
    if (file != NULL)
    {
        fclose(file);   
    }
    if (jpgFile != NULL)
    {
        fclose(jpgFile);
    }
    
    return 0;
}

/**
 * Check first 4 bytes of block if it JPEG header
 */
bool check_for_jpg_header(JPGBLOCK block)
{
    if (block.data[0] == 0xff && block.data[1] == 0xd8 && block.data[2] == 0xff && (block.data[3] == 0xe0 || block.data[3] == 0xe1))
    {
        return true;
    }else
    {
        return false;
    }
}
