#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

int main() {
    std::vector<int> numbers;

    // Read numbers from the user until a negative number is entered
    std::string line;
    
    int n;
    std::vector<int> shape;
    std::getline(std::cin, line);  
    std::istringstream iss(line);  
    while(iss>>n){
        numbers.push_back(n);
    }

    // Find the maximum number in the array
    int maxNum = *std::max_element(numbers.begin(), numbers.end());

    // Create a boolean array to mark the presence of numbers
    std::vector<bool> present(maxNum + 1, false);

    // Mark the presence of numbers in the array
    for (int i : numbers) {
        present[i] = true;
    }

    // Print the numbers that are not present in the array
    // std::cout << "Numbers not present in the array: ";
    for (int i = 0; i <= maxNum; i++) {
        if (!present[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}