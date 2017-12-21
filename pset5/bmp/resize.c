/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }

    // remember filenames
   	int resize = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

	if (resize < 1 || resize > 100)
	{
		printf("n must be between 1 and 100.\n");
		return 4;
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
    int newPadding =  (4 - (bi.biWidth * resize * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //Copy headers
    BITMAPFILEHEADER nbf = bf;
	BITMAPINFOHEADER nbi = bi;
	
	nbi.biWidth *= resize;
	nbi.biHeight *= resize;
	
	nbf.bfSize = 54 + nbi.biWidth * abs(nbi.biHeight) * 3 + abs(nbi.biHeight) *  newPadding;
	nbi.biSizeImage = ((((nbi.biWidth * nbi.biBitCount) + 31) & ~31) / 8) * abs(nbi.biHeight);

    // write outfile's BITMAPFILEHEADER
    fwrite(&nbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&nbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
    		for(int k = 0; k < resize; k++)
			{
				// iterate over pixels in scanline
				for (int j = 0; j < bi.biWidth; j++)
				{
				    // temporary storage
				    RGBTRIPLE triple;

				    // read RGB triple from infile
				    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

				    // write RGB triple to outfile
				    for(int l = 0; l < resize; l++) 
					{
						fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
					}
				}

				// skip over padding, if any
				fseek(inptr, padding, SEEK_CUR);

				// then add it back (to demonstrate how)
				for (int k = 0; k < newPadding; k++)
				{
				    fputc(0x00, outptr);
				}
				fseek(inptr, -((bi.biWidth * 3) + padding), SEEK_CUR);
		   	}
		   	fseek(inptr, (bi.biWidth * 3) + padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
