#include <iostream>
int main() {
    char inputChar[1000];
    std::cout << "Please enter a character: ";
    std::cin >> inputChar;
    std::cout << "You entered: " << inputChar << std::endl;
    return 0;
}
