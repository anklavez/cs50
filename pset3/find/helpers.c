/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

bool binsearch(int values[], int value, int low, int high);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int low = 0;
    bool result = binsearch(values, value, low, n);
    
    return result;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Bubble sort with O(n^2) and W(n) 
    bool swapped = true;
    int j = 0;
    int temp;
    while (swapped)
    {
        j++;
        swapped = false;
        for (int i = 0; i < n - j; i++)
        {
            if (values[i] > values[i + 1])
            {
                temp = values[i];
                values[i] = values[i + 1];
                values[i + 1] = temp;
                swapped = true;
            }
        }
    }
}

/**
 * Binary search implemented as recursive function
 */
bool binsearch(int values[], int value, int low, int high)
{
    
    int mid;
    
    if (low > high)
    {
        return false;
    }
    
    mid = (low + high) / 2;
    
    if (value == values[mid])
    {
        return true;
    }else if(value < values[mid])
    {
        return binsearch(values,value,low,mid - 1);
    }else
    {
        return binsearch(values,value,mid + 1,high);
    }
}