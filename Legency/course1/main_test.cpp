//main_test.cpp
#include<iostream>
using namespace std;
int main(int argcount, char* argvalues[]){
    for(int i = 0; i<argcount; i++){
        cout<<"arg["<<i<<"]: "<<argvalues[i]<<endl;
    }
}