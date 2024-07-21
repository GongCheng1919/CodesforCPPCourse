#include <iostream>

template<typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    char s1,s2;
    std::cin>>s1;
    if (s1 == 'b') {
        bool n1;
        std::cin>>n1>>s2;
        if (s2 == 'b') {
            bool n2;
            std::cin>>n2;
            std::cout<<add<bool>(n1,n2)<<std::endl;
        } else if (s2 == 'c') {
            char n2;
            std::cin>>n2;
            std::cout<<add<char>(n1,n2)<<std::endl;
        } else if (s2 == 'i') {
            int n2;
            std::cin>>n2;
            std::cout<<add<int>(n1,n2)<<std::endl;
        } else if (s2 == 'f') {
            float n2;
            std::cin>>n2;
            std::cout<<add<float>(n1,n2)<<std::endl;
        } else if (s2 == 'd') {
            double n2;
            std::cin>>n2;
            std::cout<<add<double>(n1,n2)<<std::endl;
        }
    }
    if (s1 == 'c') {
        char n1;
        std::cin>>n1>>s2;
        if (s2 == 'b') {
            bool n2;
            std::cin>>n2;
            std::cout<<add<char>(n1,n2)<<std::endl;
        } else if (s2 == 'c') {
            char n2;
            std::cin>>n2;
            std::cout<<add<char>(n1,n2)<<std::endl;
        } else if (s2 == 'i') {
            int n2;
            std::cin>>n2;
            std::cout<<add<int>(n1,n2)<<std::endl;
        } else if (s2 == 'f') {
            float n2;
            std::cin>>n2;
            std::cout<<add<float>(n1,n2)<<std::endl;
        } else if (s2 == 'd') {
            double n2;
            std::cin>>n2;
            std::cout<<add<double>(n1,n2)<<std::endl;
        }
    }
    if (s1 == 'i') {
        int n1;
        std::cin>>n1>>s2;
        if (s2 == 'b') {
            bool n2;
            std::cin>>n2;
            std::cout<<add<int>(n1,n2)<<std::endl;
        } else if (s2 == 'c') {
            char n2;
            std::cin>>n2;
            std::cout<<add<int>(n1,n2)<<std::endl;
        } else if (s2 == 'i') {
            int n2;
            std::cin>>n2;
            std::cout<<add<int>(n1,n2)<<std::endl;
        } else if (s2 == 'f') {
            float n2;
            std::cin>>n2;
            std::cout<<add<float>(n1,n2)<<std::endl;
        } else if (s2 == 'd') {
            double n2;
            std::cin>>n2;
            std::cout<<add<double>(n1,n2)<<std::endl;
        }
    }
    if (s1 == 'f') {
        float n1;
        std::cin>>n1>>s2;
        if (s2 == 'b') {
            bool n2;
            std::cin>>n2;
            std::cout<<add<float>(n1,n2)<<std::endl;
        } else if (s2 == 'c') {
            char n2;
            std::cin>>n2;
            std::cout<<add<float>(n1,n2)<<std::endl;
        } else if (s2 == 'i') {
            int n2;
            std::cin>>n2;
            std::cout<<add<float>(n1,n2)<<std::endl;
        } else if (s2 == 'f') {
            float n2;
            std::cin>>n2;
            std::cout<<add<float>(n1,n2)<<std::endl;
        } else if (s2 == 'd') {
            double n2;
            std::cin>>n2;
            std::cout<<add<double>(n1,n2)<<std::endl;
        }
    }
    if (s1 == 'd') {
        double n1;
        std::cin>>n1>>s2;
        if (s2 == 'b') {
            bool n2;
            std::cin>>n2;
            std::cout<<add<double>(n1,n2)<<std::endl;
        } else if (s2 == 'c') {
            char n2;
            std::cin>>n2;
            std::cout<<add<double>(n1,n2)<<std::endl;
        } else if (s2 == 'i') {
            int n2;
            std::cin>>n2;
            std::cout<<add<double>(n1,n2)<<std::endl;
        } else if (s2 == 'f') {
            float n2;
            std::cin>>n2;
            std::cout<<add<double>(n1,n2)<<std::endl;
        } else if (s2 == 'd') {
            double n2;
            std::cin>>n2;
            std::cout<<add<double>(n1,n2)<<std::endl;
        }
    }
    
    
    return 0;
}