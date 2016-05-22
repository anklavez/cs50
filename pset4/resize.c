/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

const int PIXEL_SIZE = 3;

const int HEADER_OFFSET = 54;

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize resizeNumber infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    int resizeNumber = strtol(argv[1], NULL, 10);
    
    if (resizeNumber < 1 || resizeNumber > 100)
    {
        printf("Factor of n should be positive number less or equals to 100\n");
        return 0;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine padding for scanlines
    int paddingOutput =  (4 - ((bi.biWidth * resizeNumber) * sizeof(RGBTRIPLE)) % 4) % 4;
    
    int inputHeight = abs(bi.biHeight);
    
    int inputWidth = bi.biWidth;

    // set proper values for file header
    bi.biWidth = bi.biWidth * resizeNumber;
    
    bi.biHeight = bi.biHeight * resizeNumber;
    
    bi.biSizeImage = ((bi.biWidth * PIXEL_SIZE) + paddingOutput) * abs(bi.biHeight);
    
    bf.bfSize = bi.biSizeImage + HEADER_OFFSET;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = inputHeight; i < biHeight; i++)
    {
        for(int k = 0; k < resizeNumber; k++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < inputWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
                for(int n = 0; n < resizeNumber; n++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr); 
                }
            }
        
            // then add it back (to demonstrate how)
            for (int p = 0; p < paddingOutput; p++)
            {
                fputc(0x00, outptr);
            }
        
            if (k < (resizeNumber - 1))
            {
                int negativeWidth  = (0 - (inputWidth * PIXEL_SIZE));
                fseek(inptr, negativeWidth, SEEK_CUR);  
            }
        }
        
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
