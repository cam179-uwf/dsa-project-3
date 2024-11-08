/**
 * Christian Marcellino
 * COP4534 Project 3
 * 10/20/2024
 * 
 * Basic math functions.
 */

#ifndef CUSTOM_MATH
#define CUSTOM_MATH

#include <stdlib.h>
#include <math.h>

/**
 * Gets a random value between 0 and 1.
 */
static float m_rand01()
{
    return (float)(rand()) / (float)(RAND_MAX);
}

#endif