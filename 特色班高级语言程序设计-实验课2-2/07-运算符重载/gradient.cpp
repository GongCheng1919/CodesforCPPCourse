/*
题目：运算符重载：计算浮点矩阵乘法的均值和输入矩阵的梯度

描述： 请创建一个名为Matrix的类，用于表示浮点数矩阵。
这个类需要重载乘法运算符*，以便能够进行矩阵的乘法运算。
该类还需要重载目运算符!，以便能够计算矩阵的均值。
你需要实现A和B两个矩阵的乘法得到乘积C矩阵,并计算乘积C矩阵的均值.
你需要实现分别实现名为gradient_dot, gradient_mean的方法，分别用于计算矩阵的求均值和求乘积的梯度。

输入: 三个整数m,n,p，表示两个矩阵A和B的行数和列数(mxn, nxp),所有值是在0-1之间的float数,需要你随机生成浮点数,并按行优先分别填充A和B矩阵。
输出: 第一行输出两个矩阵乘积的均值,
接下来m行, n列,表示A梯度.
空一行
接下来n行, p列,表示B梯度.

其他信息: 
矩阵乘法是一种二元运算，它接受两个矩阵作为输入，并生成一个新的矩阵作为输出。如果我们有两个矩阵A和B，其中A的形状为(m, n)，B的形状为(n, p)，那么他们的乘积C=AB的形状为(m, p)。A和B矩阵的每个元素是通过将A的行向量与B的列向量对应求内积得到的。
矩阵乘法的梯度可以通过链式法则来计算:
如果我们有一个标量输出m，它是通过矩阵乘法得到的，即m = mean(C), C=A*B，其中mean表示矩阵的均值（即所有元素的和除以元素的数量）,求m对A和B的梯度，即df/dA和df/dB可以通过两步来完成。
第一步:求解m对C的梯度，即gC。
    m 是 C 的所有元素的平均值，所以 m 对 C 的每个元素的偏导数都是 1/(mn)，其中 m 和 n 是 C 的行数和列数。因此，gC 是一个与 C 形状相同的矩阵，所有元素都是 1/(mn)。
第二步,求解gC 对 A 和 B 的梯度gA和gB。
    根据矩阵乘法的链式法则，我们有：
    gC 对 A 的梯度：gA = gC * B^T，其中 * 表示矩阵乘法，B^T 表示 B 的转置。
    gC 对 B 的梯度：gB = A^T * gC，其中 A^T 表示 A 的转置。
    注意着两步都是矩阵乘法。

注意:如果计算超时,请注意优化计算过程.
*/

#include<iostream>
#include<random>
using namespace std;

template <typename T>
class Matrix {
private:
    int rows;
    int cols;
    T* data;
    static std::mt19937* generator;
    static std::uniform_real_distribution<T>* fdist;

    void init(){
        for (int i = 0; i < rows * cols; ++i) {
            data[i] = (*fdist)(*generator);
        }
    }

public:


    // 构造函数
    Matrix(int m, int n) : rows(m), cols(n) {
        data = new T[rows * cols];
        init();
    }

    // 空构造函数
    Matrix() : rows(0), cols(0), data(nullptr) {}

    // 复制构造函数
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new T[rows * cols];
        std::copy(other.data, other.data + rows * cols, data);
    }

    // 赋值构造函数
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            delete[] data;
            rows = other.rows;
            cols = other.cols;
            data = new T[rows * cols];
            std::copy(other.data, other.data + rows * cols, data);
        }
        return *this;
    }

    // 析构函数
    ~Matrix() {
        if (data != nullptr)
            delete[] data;
    }

    // 重载[]获取元素
    T& operator()(int i, int j) {
        return data[i * cols + j];
    }

    // 重载*运算符
    Matrix operator* (const Matrix& other) const {
        if (cols != other.rows) {
            // throw std::runtime_error("error");
            std::cout << "error" << std::endl;
            return Matrix();
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                T sum = 0;
                for (int k = 0; k < cols; ++k) {
                    sum += data[i * cols + k] * other.data[k * other.cols + j];
                }
                result.data[i * other.cols + j] = sum;
            }
        }
        return result;
    }

    // 重载!运算符
    T mean() {
        T sum = 0;
        for (int i = 0; i < rows * cols; ++i) {
            sum += data[i];
        }
        return sum / (rows * cols);
    }

    // 计算!梯度
    Matrix gradient_mean(T mean) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; ++i) {
            result.data[i] = 1.0 / (rows * cols);
        }
        return result;
    }

    static void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    // transpose
    Matrix operator!() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[j * rows + i] = data[i * cols + j];
            }
        }
        return result;
    }

    Matrix& transpose_() {
        // Matrix result(cols, rows);
        // this = reinterpret_cast<Matrix*> this;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < i; ++j) {
                swap(this->data[i * cols + j], this->data[j * cols + i]);
            }
        }
        return (*this);
    }

    // 计算*梯度
    friend void gradient_dot(const Matrix& grad, const Matrix& input1, const Matrix& input2, Matrix& grad1, Matrix& grad2) {
        // return grad*(!(*this));
        grad1 = grad * (!input2);
        grad2 = (!input1) * grad;
    }

    // submatrix obtained by removing the row and column of the element
    Matrix cofactor(int i, int j) {
        Matrix result(rows - 1, cols - 1);
        for (int k = 0; k < rows; ++k) {
            for (int l = 0; l < cols; ++l) {
                if (k != i && l != j) {
                    result.data[(k < i ? k : k - 1) * (cols - 1) + (l < j ? l : l - 1)] = data[k * cols + l];
                }
            }
        }
        return result;
    }

    // 计算行列式
    T calculateDeterminant() {
        if (rows != cols) {
            // throw std::runtime_error("error");
            std::cout << "error" << std::endl;
            return -1;
        }
        if (rows == 1) {
            return data[0];
        }
        if (rows == 2) {
            return data[0] * data[3] - data[1] * data[2];
        }
        T det = 0;
        for (int i = 0; i < cols; ++i) {
            det += data[i] * cofactor(0, i).calculateDeterminant() * (i % 2 == 0 ? 1 : -1);
        }
        return det;
    }

    friend ostream& operator<<(ostream& out, const Matrix& m) {
        int rows = m.rows;
        int cols = m.cols;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                out << m.data[i * cols + j];
                if (j != cols - 1) {
                    out << " ";
                }
            }
            if (i != rows - 1) 
                out << std::endl;
        }
        return out;
    }
};

template <typename T>
std::mt19937* Matrix<T>::generator = new std::mt19937(0);
template <typename T>
std::uniform_real_distribution<T>* Matrix<T>::fdist = new std::uniform_real_distribution<T>(0.0, 1.0);


int main() {
    int m,n,p;
    using T = float;
    cin>>m>>n>>p;
    Matrix<T> A(m, n);
    Matrix<T> B(n, p);
    Matrix<T> C = A * B;
    // cout << A << endl<< endl<< !A << endl << endl;
    // cout << B << endl<< endl<< !B << endl << endl;
    // cout<< C << endl<< endl << !C << endl << endl;

    T mean = C.mean();
    cout << mean << endl << endl;
    Matrix<T> gradC = C.gradient_mean(mean);
    Matrix<T> gradA(m,n);
    Matrix<T> gradB(n,p);
    gradient_dot(gradC, A, B, gradA, gradB);
    // cout << gradC << endl<< endl;
    cout << gradA << endl<< endl << gradB << endl;
    // cout << matrix << endl;
    // T a = matrix.calculateDeterminant();
    // if (a != -1)
    //     std::cout << a << std::endl;
    
    return 0;
}