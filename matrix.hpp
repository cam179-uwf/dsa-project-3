#ifndef MATRIX
#define MATRIX

#include <stdexcept>
#include <iostream>
#include <vector>

/**
 * Christian Marcellino
 * COP4534 Project 3
 * 10/20/2024
 * 
 * Matrix can hold values in n by n dimensions.
 * For this project it is used to hold the
 * distances between cities.
 */
template<typename T>
class Matrix
{
    T* _array;
    int _width;
    int _length;

public:
    Matrix(int width, T initialValue)
    {
        _width = width;
        _length = width * width;
        _array = new T[_length];
        
        for (int i = 0; i < _length; ++i)
            _array[i] = initialValue;
    }

    ~Matrix()
    {
        delete[] _array;
    }

    Matrix(Matrix& other) = delete;
    Matrix& operator=(Matrix& other) = delete;

    /**
     * Gets an element at position x and y.
     */
    T& get_element(int x, int y)
    {
        if (x < 0 || y < 0)
        {
            throw std::runtime_error("Cannot get an element outside of the Matrix bounds.");
        }

        int index = x + y * _width;

        if (index >= _length)
        {
            throw std::runtime_error("Cannot get an element outside of the Matrix bounds.");
        }

        return _array[index];
    }

    /**
     * Sets an element at position x and y.
     */
    void set_element(int x, int y, T value)
    {
        if (x < 0 || y < 0)
        {
            throw std::runtime_error("Cannot set an element outside of the Matrix bounds.");
        }

        int index = x + y * _width;

        if (index >= _length)
        {
            throw std::runtime_error("Cannot set an element outside of the Matrix bounds.");
        }

        _array[index] = value;
    }

    /**
     * Prints the matrix to the console.
     */
    void print_elements()
    {
        for (int y = 0; y < _width; ++y)
        {
            for (int x = 0; x < _width; ++x)
            {
                std::cout << _array[x + y * _width] << "\t";
            }

            std::cout << std::endl;
        }
    }

    /**
     * Gets the width of the matrix which is one of the n dimensions.
     * It is assumed that the width of the matrix is the same as its height.
     */
    int get_width() const
    {
        return _width;
    }

    /**
     * Returns the total length of the matrix in linear space.
     */
    int get_length() const
    {
        return _length;
    }

    /**
     * Builds an adjacency matrix with the given values.
     */
    void build_adjacency_matrix(std::vector<T>& values)
    {
        int x = 0;
        int y = 0;
        size_t valuesIndex = 0;

        for (int i = 0; i < _width * _width && valuesIndex < values.size(); ++i)
        {
            x = i % _width;
            y = i / _width;

            if (x != y)
            {
                set_element(x, y, values[valuesIndex]);
                ++valuesIndex;
            }
        }
    }  
};

#endif