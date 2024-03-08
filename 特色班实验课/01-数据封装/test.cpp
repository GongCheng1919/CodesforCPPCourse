#include <iostream>
#include <vector>
#include <random>
#include <numeric>

// Function to generate a random tensor
std::vector<float> generateTensor(const std::vector<int>& dimensions) {
    int totalSize = std::accumulate(dimensions.begin(), dimensions.end(), 1, std::multiplies<int>());

    std::random_device rd;
    std::mt19937 generator(0);
    std::uniform_real_distribution<float> distribution(0.0, 1.0);

    std::vector<float> tensor(totalSize);
    for (int i = 0; i < totalSize; ++i) {
        tensor[i] = distribution(generator);
    }

    return tensor;
}

// Function to print a tensor
void printTensor(const std::vector<float>& tensor, const std::vector<int>& dimensions) {
    int rowSize = dimensions.back();
    int columnSize = dimensions[dimensions.size() - 2];
    int matrixSize = rowSize * columnSize;
    int numMatrices = tensor.size() / matrixSize;

    for (int i = 0; i < numMatrices; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << tensor[i * matrixSize + j] << " ";
            if ((j + 1) % columnSize == 0) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    // Read the dimensions
    std::vector<int> dimensions;
    int dim,size;
    std::cin>>dim;
    while (dim--) {
        std::cin>>size;
        dimensions.push_back(size);
    }

    // Generate the tensor
    std::vector<float> tensor = generateTensor(dimensions);

    // Print the tensor
    printTensor(tensor, dimensions);

    return 0;
}