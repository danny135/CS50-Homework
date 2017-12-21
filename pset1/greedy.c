#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("O hai! ");

    //Get user input for the amount of change needed
    int money;
    do
    {   
        printf("How much change is owed?\n");
        money = (int)(GetFloat() * 100);
    }
    while (money < 0);
    
    int coins = 0;

    while (money > 0)
    {
        if (money >= 25)
        {
            money -= 25;
            coins += 1;
            
        }
        else if (money >= 10)
        {
            money -= 10;
            coins += 1;
        }
        else if (money >= 5)
        {
            money -= 5;
            coins += 1;
        }
        else if (money >= 1)
        {
            money -= 1;
            coins += 1;
        }
        //printf("coins: %d left: %d\n", coins, money);
    }
    
    printf("%d\n", coins);
}
