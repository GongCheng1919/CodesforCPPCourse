#include <cmath>
#include <iostream>
#include <string>
using namespace std;

class Student {
  private:
    // 学号，姓名，数学，英语，计算机
    string m_id;
    string m_name;
    int m_math, m_eng, m_cs;

  public:
    // 读取数据
    void GetData() {
        cin >> m_id >> m_name >> m_math >> m_eng >> m_cs;
    }

    // 计算总和成绩和平均成绩
    int SumGra() {
        int sum = m_math + m_eng + m_cs;
        return sum;
    }

    int AveGra() {
        int sum = SumGra();
        int ave = (int)round(sum / 3.0);
        return ave;
    }

    // 输出数据
    void Display() {
        int sum = SumGra();
        int ave = AveGra();
        cout << m_id << " " << m_name << " " << m_math << " " << m_eng << " " << m_cs << " ";
        cout << sum << " " << ave;
    }
};

int main() {
    class Student student;

    student.GetData();
    student.Display();

    return 0;
}