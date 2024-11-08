/**
 * Christian Marcellino
 * COP4534 Project 3
 * 10/20/2024
 * 
 * Source file for tsp-brute-force.hpp.
 */

#include "tsp-brute-force.hpp"
#include "permutations.hpp"
#include "stopwatch.hpp"

TspBruteForce::TspBruteForce(Matrix<double>& matrix)
{
    _matrix = &matrix;
}

TspBruteForce::~TspBruteForce()
{
    
}

double TspBruteForce::get_total_distance(int* path, int length)
{
    double result = _matrix->get_element(0, path[1]);

    for (int i = 0; i < length - 1; ++i)
    {
        result += _matrix->get_element(path[i], path[i + 1]);
    }

    result += _matrix->get_element(path[length - 1], 0);

    return result;
}

double TspBruteForce::find_shortest_path(int*& path, int numberOfCities)
{
    if (path != nullptr)
    {
        delete[] path;
    }

    path = new int[numberOfCities];
    auto pathCopy = new int[numberOfCities];

    for (int i = 0; i < numberOfCities; ++i)
    {
        path[i] = i + 1;
        pathCopy[i] = path[i];
    }

    double minDistance = get_total_distance(path, numberOfCities);

    while (perm_next(path, numberOfCities))
    {
        double distance = get_total_distance(path, numberOfCities);

        if (distance < minDistance)
        {
            for (int i = 0; i < numberOfCities; ++i)
                pathCopy[i] = path[i];

            minDistance = distance;
        }
    }

    delete[] path;
    path = pathCopy;

    return minDistance;
}

void TspBruteForce::run_brute_force_until_five_minutes_exceeded(Matrix<double>& matrix)
{
    TspBruteForce bruteForce(matrix);

    int* path = nullptr;

    for (int i = 10; i < 20; ++i)
    {
        std::cout << "Number of cities: " << i << '\n';

        Stopwatch sw;
        sw.start();

        double distance = bruteForce.find_shortest_path(path, i);

        sw.stop();
        std::cout << "Elapsed: " << sw.elapsed_milliseconds() << " ms\n";

        std::cout << "Path: 0 ";
        for (int j = 0; j < i; ++j)
        {
            std::cout << path[j] << " ";
        }
        std::cout << "0\nDistance: " << distance << '\n';

        if (sw.elapsed_milliseconds() > 300000)
        {
            break;
        }

        std::cout << std::endl;
    }

    delete[] path;
}

double TspBruteForce::run_brute_force(Matrix<double>& matrix, int numberOfCities)
{
    std::cout << "Brute forcing a tour of " << numberOfCities << " cities." << std::endl;

    TspBruteForce bruteForce(matrix);

    int* path = nullptr;

    Stopwatch sw;
    sw.start();

    double distance = bruteForce.find_shortest_path(path, numberOfCities);

    sw.stop();

    std::cout << "Path: 0 ";
    for (int j = 0; j < numberOfCities; ++j)
    {
        std::cout << path[j] << " ";
    }
    std::cout << "0\nOptimal Total Cost: " << distance << std::endl;

    std::cout << "Runtime for brute force: " << sw.elapsed_milliseconds() << " ms\n";

    delete[] path;

    return distance;
}