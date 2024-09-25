
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Box {
  private:
    // 设置立方体边长
    double m_a;

  public:
    // 设置立方体边长

    void SetA() {
        cin >> m_a;
    }

    // 计算体积
    double GetVolume() {
        double Volume = m_a * m_a * m_a;
        return Volume;
    }

    // 计算表面积
    double GetArea() {
        double Area = m_a * m_a * 6;
        return Area;
    }

    // 输出计算结果
    void Display() {
        double Volume = GetVolume();
        double Area = GetArea();

        cout << Volume << endl;
        cout << Area << endl;
    }
};
int main() {

    class Box box;

    box.SetA();
    box.Display();

    return 0;
}