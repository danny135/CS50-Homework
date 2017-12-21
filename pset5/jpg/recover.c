/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 #include <stdio.h>
 #include <stdbool.h>

bool isNewImage(const char a, const char b, const char c, const char d)
{
	if (a == (char)0xff && b == (char)0xd8 && c == (char)0xff && (d == (char)0xe0 || d == (char)0xe1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main(int argc, char* argv[])
{
    FILE *card = fopen("card.raw", "r");
    FILE *image = NULL;
    
    //Keep track of how many images have been recovered
    int currentImage = 0;
    //512 byte blocks
    char buffer[512];
    char imageName[8];
    
    //Read the whole file
    while (fread(buffer, sizeof(buffer), 1, card) == 1)
    {
    	//If a new image has been reached
    	if (isNewImage(buffer[0], buffer[1], buffer[2], buffer[3]))
    	{
    		if (image)
    		{
    			fclose(image);
    		}
    		sprintf(imageName, "%03d.jpg", currentImage);
    		currentImage++;
    		image = fopen(imageName, "w");
    	}
    	
    	if (image)
		{
			fwrite(buffer, 1, sizeof(buffer), image);
		}
    }
    
    if (image)
	{
		fclose(image);
	}
    
    fclose(card);
}
