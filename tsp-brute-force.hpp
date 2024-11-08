#ifndef TSP_BRUTE_FORCE
#define TSP_BRUTE_FORCE

#include "matrix.hpp"

/**
 * Christian Marcellino
 * COP4534 Project 3
 * 10/20/2024
 * 
 * This class is used for running
 * the brute force algorithm.
 */
class TspBruteForce
{
    Matrix<double>* _matrix;

    double get_total_distance(int* path, int length);

public:
    TspBruteForce(Matrix<double>& matrix);
    ~TspBruteForce();
    TspBruteForce(TspBruteForce& other) = delete;
    TspBruteForce& operator=(TspBruteForce& other) = delete;

    /**
     * Finds the shortest path for numberOfCities using brute force.
     */
    double find_shortest_path(int*& path, int numberOfCities);

    /**
     * Helper method for running a brute force algorithm on 10 plus cities
     * until one of the runs exceeds five minutes to run.
     */
    static void run_brute_force_until_five_minutes_exceeded(Matrix<double>& matrix);

    /**
     * Helper method for running a brute force algorithm on numberOfCities.
     */
    static double run_brute_force(Matrix<double>& matrix, int numberOfCities);
};

#endif