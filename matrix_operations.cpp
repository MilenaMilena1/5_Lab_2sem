#include "matrix_operations.h"

void writeMatrixToFile(const std::string& filename, const std::vector<Matrix>& matrices) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return;
    }

    for (const auto& matrix : matrices) {
        for (const auto& row : matrix.data) {
            for (int value : row) {
                file << value << ' ';
            }
            file << '\n';
        }
        file << '\n';
    }

    file.close();
}

std::vector<Matrix> readMatricesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return {};
    }

    std::vector<Matrix> matrices;
    std::vector<std::vector<int>> matrixData;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            if (!matrixData.empty()) {
                matrices.push_back({ matrixData });
                matrixData.clear();
            }
        }
        else {
            std::istringstream iss(line);
            std::vector<int> row;
            int value;
            while (iss >> value) {
                row.push_back(value);
            }
            matrixData.push_back(row);
        }
    }

    if (!matrixData.empty()) {
        matrices.push_back({ matrixData });
    }

    file.close();
    return matrices;
}