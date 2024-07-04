


#include <iostream>
#include <string>

class Animal {
public:
    std::string name;
    Animal(std::string name) : name(name) {}
    virtual void makeSound() = 0; // Pure virtual function
};

class Lion : public Animal {
public:
    Lion(std::string name) : Animal(name) {}
    void makeSound() override {
        std::cout << "Roar" << std::endl;
    }
};

class Tiger : public Animal {
public:
    Tiger(std::string name) : Animal(name) {}
    void makeSound() override {
        std::cout << "Growl" << std::endl;
    }
};

class Bear : public Animal {
public:
    Bear(std::string name) : Animal(name) {}
    void makeSound() override {
        std::cout << "Grr" << std::endl;
    }
};

int main() {
    std::string name;
    std::cin >> name;
    Animal* ptr;
    if (name == "Lion") {
        ptr = new Lion(name);
        ptr->makeSound();
    }
    else if (name == "Tiger") {
        ptr = new Tiger(name);
        ptr->makeSound();
    }
    else if (name == "Bear") {
        ptr = new Bear(name);
        ptr->makeSound();
    }
    // Lion lion("Simba");
    // Tiger tiger("Rajah");
    // Bear bear("Baloo");

    // lion.makeSound(); // Should print "Roar"
    // tiger.makeSound(); // Should print "Growl"
    // bear.makeSound(); // Should print "Grr"

    return 0;
}