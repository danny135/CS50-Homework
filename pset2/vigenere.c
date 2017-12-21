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
    
    char* cipher = argv[1];
    
    //Rotation and cipher length
    int rot, clen = strlen(cipher);
    
    for (int t = 0; t < clen; t++)
    {
        if (!(cipher[t] >= 'A' && cipher[t] <= 'Z') && !(cipher[t] >= 'a' && cipher[t] <= 'z'))
        {
            printf("Bad cipher.");
            return 1;
        }
    }
    
    char* p = GetString();
    
    for (int i = 0, cl = 0, letter, n = strlen(p); i < n; i++)
    {
        char c = p[i];
        if (!(p[i] >= 'A' && p[i] <= 'Z') && !(p[i] >= 'a' && p[i] <= 'z'))
        {
            printf("%c", p[i]);
            continue;
        }
        else if (cipher[cl] >= 'A' && cipher[cl] <= 'Z')
        {
            rot = cipher[cl] - 'A';
            cl += 1;
            cl %= clen;
        }
        else if (cipher[cl] >= 'a' && cipher[cl] <= 'z')
        {
            rot = cipher[cl] - 'a';
            cl += 1;
            cl %= clen;
        }
        
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
        
        printf("%c", c);
        
    }
    
    printf("\n");
}
