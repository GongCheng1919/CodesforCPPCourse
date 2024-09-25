#include <iostream>
#include <random>

int main() {
    /**
     * @brief Random number generator using the Mersenne Twister algorithm.
     * 
     * This generator is initialized with a seed value of 0.
     * It is a standard mersenne_twister_engine (mt19937).
     */
    std::mt19937 generator(0); // mt19937 is a standard mersenne_twister_engine

    int n;
    char s;
    std::cin>>n>>s;

    if (s == 'i') {
        std::uniform_int_distribution<int> distribution(0, 100);
        for (int i = 0; i < n; ++i) {
            std::cout << distribution(generator) << std::endl;
        }
    } else if (s == 'f') {
        std::uniform_real_distribution<float> distribution(0.0, 1.0);
        for (int i = 0; i < n; ++i) {
            std::cout << distribution(generator) << std::endl;
        }
    }else
    {
        std::cout<<"error"<<std::endl;
        return 0;
    }
    
    return 0;
}