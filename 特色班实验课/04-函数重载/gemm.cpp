#include<iostream>
#include<random>
using namespace std;

template <typename T>
class Matrix;

// 前向声明友元函数
template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m);

template <typename T>
class Matrix {
private:
    int rows;
    int cols;
    T* data;
    static std::mt19937* generator;
    static std::uniform_real_distribution<T>* fdist;
    // static std::uniform_real_distribution<T>* fdist;
    static std::uniform_int_distribution<T>*idist;

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

    // 赋值构造函数
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
        delete[] data;
    }

    // 重载[]获取元素
    T& operator()(int i, int j) {
        return data[i * cols + j];
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

    friend ostream& operator<< <>(ostream& out, const Matrix& m);
    // {
    //     int rows = m.rows;
    //     int cols = m.cols;
    //     for (int i = 0; i < rows; ++i) {
    //         for (int j = 0; j < cols; ++j) {
    //             out << m.data[i * cols + j];
    //             if (j != cols - 1) {
    //                 out << " ";
    //             }
    //         }
    //         if (i != rows - 1) 
    //             out << std::endl;
    //     }
    //     return out;
    // }

    Matrix operator*(const Matrix& other) {
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
                result.data[i * result.cols + j] = sum;
            }
        }
        return result;
    }

};

template <typename T>
std::mt19937* Matrix<T>::generator = new std::mt19937(0);
template <typename T>
std::uniform_real_distribution<T>* Matrix<T>::fdist = new std::uniform_real_distribution<T>(0.0, 1.0);
template <typename T>
std::uniform_int_distribution<T>* Matrix<T>::idist = new std::uniform_int_distribution<T>(0, 4);

// Specialization for int
template <>
void Matrix<int>::init() {
    for (int i = 0; i < rows * cols; ++i) {
            data[i] = (*idist)(*generator);
        }
}
template <>
void Matrix<char>::init() {
    for (int i = 0; i < rows * cols; ++i) {
            data[i] = (*idist)(*generator);
        }
}

template <typename T>
ostream& operator<<(ostream& out, const Matrix<T>& m)
{
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

template <>
ostream& operator<<(ostream& out, const Matrix<char>& m)
{
    int rows = m.rows;
    int cols = m.cols;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            out << (int)m.data[i * cols + j];
            if (j != cols - 1) {
                out << " ";
            }
        }
        if (i != rows - 1) 
            out << std::endl;
    }
    return out;
}

#define GEMM_TEST {Matrix<T> matrix(m, n); \
        cout << matrix << endl; \
        Matrix<T> matrix2(n, p); \
        cout << matrix2 << endl; \
        Matrix<T> matrix3 = matrix * matrix2; \
        cout << matrix3 << endl; }

int main() {
    int m,n,p;
    char o;
    cin>>m>>n>>p>>o;
    switch (o)
    {
    case /* constant-expression */ 'i':
        /* code */
        {
        using T = int;
        GEMM_TEST
        }
        break;
    case /* constant-expression */ 'f':
        /* code */
        {
        using T = float;
        GEMM_TEST
        }
        break;
    case /* constant-expression */ 'd':
        /* code */
        {
        using T = double;
        GEMM_TEST
        }
        break;
    case /* constant-expression */ 'c':
        /* code */
        {
        using T = char;
        GEMM_TEST
        }
        break;
    default:
        break;
    }
    
    // Matrix<T> matrix(m, n);
    // cout << matrix << endl;
    // T a = matrix.calculateDeterminant();
    // if (a != -1)
    //     std::cout << a << std::endl;
    // Matrix<T> matrix2(n, p);
    // cout << matrix2 << endl;
    // Matrix<T> matrix3 = matrix * matrix2;
    // cout << matrix3 << endl;

    return 0;
}