#include <iostream>
#include<random>
using namespace std;

template <typename T>
class Tensor {
protected:
    T* data;
    int* shape;
    int dims;
    int size;
    // Add a reference count to the Tensor class
    bool ownsData;
    int* refCount;

    static std::mt19937* generator;
    static std::uniform_real_distribution<T>* fdist;

    void init(){
        if (ownsData){
            for (int i = 0; i < size; ++i) {
                data[i] = (*fdist)(*generator);
            }
        }
    }

public:
    // Empty constructor
    Tensor() : data(nullptr), shape(nullptr), dims(0), size(0), ownsData(false), refCount(nullptr) {}

    // Regular constructor
    Tensor(int dims, int* shape) : dims(dims) {
        this->shape = new int[dims];
        size = 1;
        for (int i = 0; i < dims; ++i) {
            this->shape[i] = shape[i];
            size *= shape[i];
        }
        data = new T[size];
        ownsData = true;
        refCount = new int(1);
        init();
    }

    Tensor(int index, Tensor& t) {   
        dims = t.dims - 1; 
        size = t.size/t.shape[0];
        data = t.data + index * size;
        shape = t.shape + 1;
        refCount = t.refCount;
        ownsData = false;
        *refCount++;
    }

    Tensor(int dims, int* shape, T* data, int* refCount=nullptr) : dims(dims), shape(shape), data(data),ownsData(false), refCount(refCount) {
        size = 1;
        for (int i = 0; i < dims; ++i) {
            size *= shape[i];
        }
        if (refCount != nullptr) {
            *refCount ++;
        }
    }

    // Copy constructor
    Tensor(const Tensor& other) : dims(other.dims), size(other.size), ownsData(true), refCount(new int(1)){
        shape = new int[dims];
        for (int i = 0; i < dims; ++i) {
            shape[i] = other.shape[i];
        }
        data = new T[size];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Destructor
    ~Tensor() {
        if (ownsData) {
            if (refCount != nullptr) {
                if (--(*refCount) == 0) {
                    delete[] data;
                    delete[] shape;
                    delete refCount;
                }
            } 
        }
        // delete[] data;
        // delete[] shape;
    }

    // Assignment operator
    Tensor& operator=(const Tensor& other) {
        if (this != &other) {
            delete[] data;
            delete[] shape;
            delete refCount;

            dims = other.dims;
            size = other.size;
            shape = new int[dims];
            size = 1;
            for (int i = 0; i < dims; ++i) {
                shape[i] = other.shape[i];
                size *= shape[i];
            }
            data = new T[size];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
            ownsData = true;
            refCount = new int(1);
        }
        return *this;
    }

    T* get_data_ptr() {
        return data;
    }

    int* shape(){
        return shape;
    }
    int dims(){
        return dim;
    }

    // [] operator
    Tensor operator[](int index) {
        // This is a simple example that returns a 1D tensor.
        // You need to implement this according to your requirements.
        if(index<0 || index>=shape[0]){
            cout<<"error"<<endl;
            return Tensor();
        }
        return Tensor(index, *this);
        // return Tensor(index, )
    }

    // Print function
    void printTensor() {
        int rowSize = shape[dims - 2];
        int columnSize = shape[dims - 1];
        int matrixSize = rowSize * columnSize;
        int numMatrices = size / matrixSize;

        for (int i = 0; i < numMatrices; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                std::cout << data[i * matrixSize + j];
                if ((j + 1) % columnSize == 0) {
                    std::cout << std::endl;
                }else
                {
                    std::cout<<" ";
                }
            }
            if (i != numMatrices - 1)
                std::cout << std::endl;
        }
    }
};

template <typename T>
std::mt19937* Tensor<T>::generator = new std::mt19937(0);
template <typename T>
std::uniform_real_distribution<T>* Tensor<T>::fdist = new std::uniform_real_distribution<T>(0.0, 1.0);

template <typename T>
class FlexTensor: public Tensor<T> {
protected:
    // add the current dim shape shape_off  and  of the tensor
    int* shape_off;
    int cur_dim;
    int cur_shape;
    int cur_size;
public:
    int* shape(){
        return cur_shape;
    }
    int dims(){
        return cur_dim;
    }
    Tensor& split(int* start_index, int* end_index, int dim){
        // split the tensor according to the start_index and end_index
        // and return the new tensor

    }

    // [] operator
    Tensor& operator[](int index) {
        // This is a simple example that returns a 1D tensor.
        // You need to implement this according to your requirements.
        if(index<0 || index>=shape[0]){
            cout<<"error"<<endl;
            return Tensor();
        }
        this->cur_dim = this->cur_dims - 1;
        this->cur_size = this->cur_size/this->cur_shape[0];
        this->cur_shape = this->cur_shape + 1;
        return *this;
        // return Tensor(index, )
    }

    void printTensor(){
        // print the tensor
        int cur_rowSize = cur_shape[dims - 2];
        int cur_columnSize = cur_shape[dims - 1];
        int cur_matrixSize = cur_rowSize * cur_columnSize;
        int cur_numMatrices = cur_size / cur_matrixSize;

        for (int i = 0; i < numMatrices; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                std::cout << data[i * matrixSize + j];
                if ((j + 1) % columnSize == 0) {
                    std::cout << std::endl;
                }else
                {
                    std::cout<<" ";
                }
            }
            if (i != numMatrices - 1)
                std::cout << std::endl;
        }
    }

};


int main() {
    // 创建一个3维的Tensor
    int shape[3] = {2, 2, 2};
    
    using T = float;
    Tensor<T> tensor1(3, shape);
    cout << "tensor1:" << endl;
    tensor1.printTensor();

    // 测试[]运算符
    Tensor<T> tensor2 = tensor1[0];
    cout << "tensor2:" << endl;
    tensor2.printTensor();
    cout << "tensor1[0]:" << endl;
    tensor1[0].printTensor();
    cout << "tensor1[0][0][0]:" << endl;
    tensor1[0][0].printTensor();

    // 创建一个共享内存的Tensor
    T* data = new T[8];
    for (int i = 0; i < 8; ++i) {
        data[i] = float(i);
    }
    Tensor<T> tensor3(3, shape, data);
    cout << "tensor3:" << endl;
    tensor3.printTensor();
    // 输出data和tensor3.data的地址,看是否相同
    cout << "data.ptr: " << data << endl;
    cout << "tensor3.data.ptr: " << tensor3.get_data_ptr() << endl;

    // 测试拷贝构造函数
    Tensor<T> tensor4 = tensor3;
    cout << "tensor4:" << endl;
    tensor4.printTensor();

    // 测试赋值运算符
    tensor1 = tensor4;
    cout << "tensor1:" << endl;
    tensor1.printTensor();

    // 测试析构函数
    // 当tensor1, tensor3, tensor4离开作用域时，析构函数会自动被调用

    delete[] data;

    return 0;
}