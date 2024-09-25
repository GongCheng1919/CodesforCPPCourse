
/*
根据给出的维度和各维度的值创建Tensor对象，并使用随机数生成器为Tensor赋初始值，
然后将Tensor打印到屏幕，
打印规则为将高维Tensor展开为多个大小为Tensor最后两个维度的多个矩阵，
向屏幕打印每个矩阵，相邻的两个矩阵间多一空行隔开。
*/
// 之前已经写过tensor类这里稍加改动即可

#include <cstdio>
#include <iostream>
#include <random>
#include <vector>

// 用using定义新的数据类型
// using vi = vector<int>;
#define vf vector<float>
#define vi vector<int>

using namespace std;

// 用随机数生成器给tensor初始化
std::mt19937 generator(0); // 这一行是什么意思？

// 均匀分布，distribution有什么作用？
uniform_real_distribution<float> distribution(0.0, 1.0);

class Tensor {
  private:
    // 指定张量维度
    int m_dim_num;

    // 存储tensor
    vf m_data;

    // 表示tensor的各个维数
    vi m_dim;

  public:
    // 创建tensor
    void CreatTensor(vi ivec) {
        // 根据同一个类创建的对象都是共享同一个数据？也许表述不准确
        // 所以我们需要使用新的随机数生成器对象来为每个对象独立赋值

        // m_data.clear();
        // m_dim.clear();

        // 没有指定的维度了，只有给个维度的数据
        m_dim_num = ivec.size();
        for (int i = 0; i < m_dim_num; i++) {
            m_dim.push_back(ivec[i]);
        }
    }

    void RandomTensor() {

        int tensorsize = GetSize();
        for (int i = 0; i < tensorsize; i++) {
            float temp = distribution(generator);
            m_data.push_back(temp);
        }
    }

  public:
    // 获取尺寸
    int GetSize() {
        int size = 1;
        for (int i = 0; i < m_dim_num; i++)
            size *= m_dim[i];
        return size;
    }

    // 按照最后两维打印tensor,也即是把最后两维作为单元输出
    void Display() {
        int unit = m_dim[m_dim_num - 1] * m_dim[m_dim_num - 2];
        int totalMatrices = GetSize() / unit;
        for (int i = 0; i < GetSize(); i += unit) {
            for (int j = i; j < i + unit; j += m_dim[m_dim_num - 1]) {
                for (int k = j; k < j + m_dim[m_dim_num - 1]; k++) {
                    cout << m_data[k];
                    if ((k + 1) % m_dim[m_dim_num - 1] == 0 && k != 0) // 最后一组数据输出后也没有空格
                        cout << '\n';
                    else
                        cout << " ";
                }
            }
            // 只有相邻矩阵之间换行分割，最后一个矩阵没有换行
            if (i / unit != totalMatrices - 1)
                cout << '\n';
        }
    }

    // 本来想使用操作符重载的，但是还是直接写个函数更加简单
    // 以后优化肯定要使用操作符重载的
    void AddTensor(Tensor &tensor1, Tensor &tensor2) {
        for (int i = 0; i < GetSize(); i++)
            m_data.push_back(tensor1.m_data[i] + tensor2.m_data[i]);
    }
};

int main() {
    int temp;
    vi ivec;

    do {
        cin >> temp;
        ivec.push_back(temp);
    } while (EOF != getchar()); // OJ根据文件结尾为EOF来判定结束

    Tensor tensor1, tensor2, tensor3;

    tensor1.CreatTensor(ivec);
    tensor1.RandomTensor();
    cout << "Tensor 1:" << '\n';
    tensor1.Display();

    cout << '\n';
    tensor2.CreatTensor(ivec);
    tensor2.RandomTensor();
    cout << "Tensor 2:" << '\n';
    tensor2.Display();

    cout << '\n';
    tensor3.CreatTensor(ivec);
    cout << "Tensor 1 + Tensor 2:" << '\n';
    tensor3.AddTensor(tensor1, tensor2);
    tensor3.Display();
    return 0;
}
