/**
 * Christian Marcellino
 * COP4534 Project 3
 * 10/20/2024
 * 
 * Entry point for the project.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

#include "matrix.hpp"
#include "tsp-brute-force.hpp"
#include "permutations.hpp"
#include "stopwatch.hpp"
#include "tsp-ga.hpp"

#define MATRIX_SIZE 20

void read_distances_from_file(std::vector<double>& distances);
void test_permutation();

int main(int argc, char** argv)
{
    std::cout << std::fixed << std::setprecision(2);

    std::vector<double> distances;
    read_distances_from_file(distances);

    Matrix<double> matrix(MATRIX_SIZE, 0);
    matrix.build_adjacency_matrix(distances);

    int numberOfCitiesToRun = 0;
    int numberOfGenerationsToRun = 0;
    int numberOfToursInAGeneration = 0;
    double percentageOfGenerationComprisedOfMutations = 0;

    std::cout << "Number of cities to run? (input should be an integer greater than 0): ";
    std::cin >> numberOfCitiesToRun;

    std::cout << "Number of generations to run? (input should be an integer greater than 0): ";
    std::cin >> numberOfGenerationsToRun;

    std::cout << "Number of tours in a generation? (input should be an integer greater than 0): ";
    std::cin >> numberOfToursInAGeneration;

    std::cout << "What percentage of a generation should be comprised of mutations? (input should be a decimal number between 0 and 1): ";
    std::cin >> percentageOfGenerationComprisedOfMutations;
    
    std::cout << std::endl;

    /**
     * RUN BRUTE FORCE METHOD
     */

    double bfCost = TspBruteForce::run_brute_force(matrix, numberOfCitiesToRun);

    std::cout << std::endl;

    /**
     * RUN GENERATIONAL METHOD
     */

    TspGa tspGa(
        matrix,
        numberOfCitiesToRun, 
        numberOfGenerationsToRun, 
        numberOfToursInAGeneration, 
        percentageOfGenerationComprisedOfMutations);

    double gaCost = tspGa.run_generations();

    std::cout << "\nPercent of optimal that the ga produced: " << (gaCost / bfCost * 100) << "%" << std::endl;
}

/**
 * Reads in all of the distances from the distance.txt file.
 */
void read_distances_from_file(std::vector<double>& distances)
{
    double distance;

    std::ifstream ifs("distances.txt");

    while (!ifs.eof())
    {
        ifs >> distance;
        distances.push_back(distance);
    }

    ifs.close();
}

/**
 * Simple method to test if termination of permutations is working correctly.
 */
void test_permutation()
{
    int s[] = { 0, 1, 2 };

    while (perm_next(s, 3))
    {
        for (int i = 0; i < 3; ++i)
            std::cout << s[i] << " ";
        std::cout << std::endl;
    }
}