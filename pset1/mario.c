#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        printf("Height: ");
        n = GetInt();
    }
    while (n > 23 || n < 0);
    //n += 1;
    
    for (int i = 0; i < n+1; i++)
    {   
        if (i > 0)
        {
            for (int j = n-i-1; j >= 0; j--)
            {
                printf(" ");
            }
        }
        
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        
        if (i > 0)
        {
            printf("#\n");
        }
    }
}
