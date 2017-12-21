/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <stdio.h>
#include <cs50.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

bool binarySearch(int value, int values[], int min, int max)
{	
	if (max < min)
	{
		return false;
	}
	else
	{
		int center = (int) ((min + max) / 2);
		if (values[center] > value)
		{
			return binarySearch(value, values, min, center-1);
		}
		else if (values[center] < value)
		{
			return binarySearch(value, values, center+1, max);
		}
		else
		{
			return true;
		}
	}
}

bool search(int value, int values[], int n)
{
	return binarySearch(value, values, 0, n);
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int i = 1; i < n; i++)
    {
    	int j = i;
    	while (values[j] > 0 && values[j - 1] > values[j])
    	{
    		swap(&values[j], &values[j-1]);
    		j -= 1;
    	}
    }
   	
   	for (int i = 1; i < n; i++)
    {
    	printf("%d\n", values[i]);
    }
    return;
}
