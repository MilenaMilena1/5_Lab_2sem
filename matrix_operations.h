#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

struct Matrix {
    std::vector<std::vector<int>> data;
};

void writeMatrixToFile(const std::string& filename, const std::vector<Matrix>& matrices);
std::vector<Matrix> readMatricesFromFile(const std::string& filename);

#endif