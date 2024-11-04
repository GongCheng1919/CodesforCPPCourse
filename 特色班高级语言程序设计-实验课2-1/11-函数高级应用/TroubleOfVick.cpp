#include <iostream>
#include <math.h>

using namespace std;

struct point {
    int x;
    int y;
};

double operator- (const point &a, const point &b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    point a, b, c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    cout << (a - b) + (c - b) + (c - a);
}
