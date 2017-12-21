#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    if (argc != 2 || argv[1] < 0)
    {
        printf("Incorrect number of arguments.\n");
        return 1;
    }
    
    int rot = atoi(argv[1]);
    
    char* p = GetString();
    
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        char c = p[i];
        int letter;
        if (p[i] >= 'A' && p[i] <= 'Z')
        {
            letter = p[i] - 'A';
            c = 'A' + (letter + rot) % 26;
        }
        else if (p[i] >= 'a' && p[i] <= 'z')
        {
            letter = p[i] - 'a';
            c = 'a' + (letter + rot) % 26;
        }
        else
        {
            c = p[i];
        }
        printf("%c", c);
    }
    
    printf("\n");
}
