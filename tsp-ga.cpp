/**
 * Christian Marcellino
 * COP4534 Project 3
 * 10/20/2024
 * 
 * Source file for tsp-ga.hpp.
 */

#include "tsp-ga.hpp"
#include "m.hpp"
#include "stopwatch.hpp"

TspGa::TspGa(
    Matrix<double>& matrix,
    int numberOfCitiesToRun,
    int numberOfGenerationsToRun,
    int numberOfToursInAGeneration,
    double percentageOfGenerationComprisedOfMutations)
{
    _matrix = &matrix;
    _numberOfCitiesToRun = numberOfCitiesToRun;
    _numberOfGenerationsToRun = numberOfGenerationsToRun;
    _numberOfToursInAGeneration = numberOfToursInAGeneration;
    _pMutations = percentageOfGenerationComprisedOfMutations;
}

TspGa::~TspGa()
{

}

std::vector<int> TspGa::get_random_permutation()
{
    std::vector<int> cities;

    for (int i = 0; i < _numberOfCitiesToRun; ++i)
        cities.push_back(i + 1);

    std::vector<int> path;

    while (cities.size() > 0)
    {
        size_t index = m_rand01() * cities.size();

        // guard just in case
        if (index >= cities.size())
            index = cities.size() - 1;

        path.push_back(cities[index]);
        cities.erase(cities.begin() + index);
    }

    return path;
}

void TspGa::swap(std::vector<int>& path, int index1, int index2)
{
    int temp = path[index1];
    path[index1] = path[index2];
    path[index2] = temp;
}

double TspGa::get_total_distance(std::vector<int>& path)
{
    double result = _matrix->get_element(0, path[1]);

    for (size_t i = 0; i < path.size() - 1; ++i)
    {
        result += _matrix->get_element(path[i], path[i + 1]);
    }

    result += _matrix->get_element(path[path.size() - 1], 0);

    return result;
}

std::string TspGa::path_to_str(std::vector<int>& path)
{
    std::string result = "0 ";

    for (auto i : path)
        result += std::to_string(i) + " ";

    result += "0";

    return result;
}

void TspGa::initialize_first_generation(Generation& generation)
{
    for (int i = 0; i < _numberOfToursInAGeneration; ++i)
        generation.paths.push_back(get_random_permutation());
}

double TspGa::run_generations()
{
    std::cout << "Estimating a tour of " << _numberOfCitiesToRun << " cities.\n";

    double minDistance = 0;
    std::vector<int> elite;

    Generation generation;

    Stopwatch sw;
    sw.start();

    initialize_first_generation(generation);

    int numberOfGenerationsSimulated = 0;

    while (numberOfGenerationsSimulated < _numberOfGenerationsToRun)
    {
        if (generation.paths.size() <= 0) break;

        // find the most fit
        minDistance = get_total_distance(generation.paths[0]);
        int mostFitIndex = 0;

        for (size_t i = 0; i < generation.paths.size(); ++i)
        {
            double distance = get_total_distance(generation.paths[i]);

            if (distance < minDistance)
            {
                mostFitIndex = i;
                minDistance = distance;
            }
        }

        // remember the elite path and forget it in the current paths for now
        elite = generation.paths[mostFitIndex];
        generation.paths.erase(generation.paths.begin() + mostFitIndex);

        // mutate some of the paths
        int numberOfPathsToMutate = generation.paths.size() * _pMutations;

        for (int i = 0; i < numberOfPathsToMutate; ++i)
        {
            // get a random number of elements in the path to swap
            int numberOfElementsToSwap = m_rand01() * _numberOfCitiesToRun;

            // swap those elements
            for (int j = 0; j < numberOfElementsToSwap; ++j)
            {
                int randIndex1 = m_rand01() * (_numberOfCitiesToRun - 1);
                int randIndex2 = m_rand01() * (_numberOfCitiesToRun - 1);

                swap(generation.paths[i], randIndex1, randIndex2);
            }
        }

        // erase all of the paths that were not mutated
        for (int i = generation.paths.size() - 1; i > numberOfPathsToMutate; --i)
        {
            generation.paths.erase(generation.paths.begin() + i);
        }

        // add the elite path back into the generation
        generation.paths.push_back(elite);

        // re-fill the paths to get them back up to _numberOfToursInAGeneration
        while (generation.paths.size() < (size_t)_numberOfToursInAGeneration)
        {
            generation.paths.push_back(get_random_permutation());
        }

        // run the next generation
        ++numberOfGenerationsSimulated;
    }

    std::cout << "Most Elite Path: " << path_to_str(elite) << '\n'; 
    std::cout << "Total Cost: " << minDistance << '\n';

    sw.stop();
    std::cout << "Runtime for generations: " << sw.elapsed_milliseconds() << " ms" << std::endl;

    return minDistance;
}