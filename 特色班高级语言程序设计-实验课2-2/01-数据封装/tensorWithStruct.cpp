#include <iostream>
using namespace std;
class Tensor {
  public:
    int *data;    // 数据
    int dim_num;  // 维度
    int arr[999]; // 维数
    int ele[999]; // 找坐标
    int size;
    void GetElement() {
        int index = 0;
        int mutiplier = 1;
        for (int i = dim_num - 1; i >= 0; i--) {
            index += ele[i] * mutiplier;
            mutiplier *= arr[i];
        }
        cout << data[index] << endl;
    }
    void printtensor() {
        /*	int rowSize = arr[0];
            int columnSize = arr[dim_num - 1];
            int matrixSize = rowSize * columnSize;
            int numMatrices = size / matrixSize;
            for (int i = 0; i < numMatrices; i++)
            {
                for (int j = 0; j < matrixSize; j++)
                {
                    cout << data[i * matrixSize + j];
                    if ((j + 1) % columnSize == 0)
                    {
                        cout << endl;
                    }
                    else {
                        cout << " ";
                    }
                }
                if (1 != numMatrices - 1)
                    cout << endl;
            }*/

        int last_dim = arr[dim_num - 1];
        for (int i = 0; i < size; i += last_dim) {
            for (int j = i; j < i + last_dim; j++) {
                cout << data[j] << " \n"[(j + 1) % last_dim == 0];
            }
        }
    }
};
int main() {
    Tensor t;
    cin >> t.dim_num;
    t.size = 1;
    for (int i = 0; i < t.dim_num; i++) {
        cin >> t.arr[i];
        t.size *= t.arr[i]; // 二维   行     列
        // 三维   行    个    列
    }

    t.data = new int[t.size];
    for (int i = 0; i < t.size; i++) {
        t.data[i] = i + 1;
    }
    for (int i = 0; i < t.dim_num; i++) {
        cin >> t.ele[i];
    }
    cout << t.size << endl;
    t.GetElement();
    t.printtensor();
    return 0;
}