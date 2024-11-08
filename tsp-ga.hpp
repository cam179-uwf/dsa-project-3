#ifndef TSP_GA
#define TSP_GA

#include <string>
#include <iostream>
#include <vector>

#include "matrix.hpp"

/**
 * Christian Marcellino
 * COP4534 Project 3
 * 10/20/2024
 * 
 * Class used for running the generations
 * simulation.
 */
class TspGa
{
    struct Generation
    {
        std::vector<std::vector<int>> paths;
    };

    Matrix<double>* _matrix;

    int _numberOfCitiesToRun = 0;
    int _numberOfGenerationsToRun = 0;
    int _numberOfToursInAGeneration = 0;
    double _pMutations = 0;

    /**
     * Gets a random permuation of length _numberOfCitiesToRun.
     */
    std::vector<int> get_random_permutation();

    /**
     * Swaps two elements in a vector given their indecies.
     */
    void swap(std::vector<int>& path, int index1, int index2);

    /**
     * Gets the total distance for the given path.
     */
    double get_total_distance(std::vector<int>& path);

    /**
     * Converts a path to a string for printing.
     */
    std::string path_to_str(std::vector<int>& path);

    /**
     * Returns a generation with _numberOfToursInAGeneration initialized.
     */
    void initialize_first_generation(Generation& generation);

public:
    TspGa(
        Matrix<double>& matrix,
        int numberOfCitiesToRun,
        int numberOfGenerationsToRun,
        int numberOfToursInAGeneration,
        double percentageOfGenerationComprisedOfMutations
    );
    ~TspGa();
    TspGa(TspGa& other) = delete;
    TspGa& operator=(TspGa& other) = delete;

    /**
     * Runs the generations simulation and returns the cost of the best tour found.
     */
    double run_generations();
};

#endif