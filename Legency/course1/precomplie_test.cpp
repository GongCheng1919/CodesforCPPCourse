#include <iostream>
#define WHITE 0
#define BLACK 1
#define COLOR WHITE
using namespace std;
int main( ){
 #if COLOR==WHITE
    cout<<"Select white stone "<<endl;
 #elif COLOR==BLACK
    cout<<"Select black stone "<<endl;
 #else
    #error you select color incorrectly;
 #endif
    return 0;
}