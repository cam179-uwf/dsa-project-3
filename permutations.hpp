/**
 * Christian Marcellino
 * COP4534 Project 3
 * 10/20/2024
 * 
 * Helper methods for permutations.
 */

#ifndef PERMUTATIONS
#define PERMUTATIONS

/**
 * Method for swaping two elements in an array.
 */
static void perm_internal_swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Retrieves the next permutation of a set.
 * Returns true if there is another permutation to be generated, 
 * otherwise returns false.
 */
static bool perm_next(int* arr, int length)
{
    bool isDone = true;

    for (int i = 0; i < length - 1; ++i)
    {
        if (arr[i] < arr[i + 1])
            isDone = false;
    }

    if (isDone)
        return false; // no more permutations

    int m = 0, k = 0, p = 0, q = 0;

    m = length - 2;

    while(arr[m] > arr[m + 1])
    {
        m = m - 1;
    }

    k = length - 1;

    while(arr[m] > arr[k])
    {
        k = k - 1;
    }

    perm_internal_swap(arr + m, arr + k);
    p = m + 1;
    q = length - 1;

    while(p < q)
    {
        perm_internal_swap(arr + p, arr + q);
        p++;
        q--;
    }

    return true; // there are more permutations
}

#endif