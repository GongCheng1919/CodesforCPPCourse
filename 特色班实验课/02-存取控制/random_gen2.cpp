#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time()

int main() {
    srand(0); // Set the seed to a fixed value

    int n;
    char s;
    std::cin >> n >> s;

    if (s == 'i') {
        for (int i = 0; i < n; ++i) {
            std::cout << (rand() % 101) << std::endl; // Generate a random integer between 0 and 100
        }
    } else if (s == 'f') {
        for (int i = 0; i < n; ++i) {
            std::cout << static_cast<float>(rand()) / static_cast<float>(RAND_MAX) << std::endl; // Generate a random float between 0.0 and 1.0
        }
    } else {
        std::cout << "error" << std::endl;
        return -1;
    }

    return 0;
}