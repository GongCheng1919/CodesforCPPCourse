#include <iostream>
#include<random>
using namespace std;

class Tensor {
protected:
    std::vector<float> data;
    std::vector<int> shape;
    int size;

    static std::mt19937* generator;
    static std::uniform_real_distribution<float>* fdist;

    void init(){
        for (int i = 0; i < size; ++i) {
            data[i] = (*fdist)(*generator);
        }
    }

public:
    // Empty constructor
    Tensor() : data({}), shape({}), size(0) {}

    // Regular constructor
    Tensor(std::vector<int> shape) : {
        this->shape = shape;
        size = 1;
        for (int i = 0; i < shape.size(); ++i) {
            size *= shape[i];
        }
        init();
    }

    Tensor(int index, Tensor& t) {   
        size = t.size/t.shape[0];
        shape.resize(t.shape.size()-1);
        data.resize(size);
        for (int i = 0; i<size; i++){
            data[i] = t.data[i+index*size];
        }
    }

    Tensor(std::vector<int> shape, std::vector<float> data) : shape(shape), data(data) {
        size = 1;
        for (int i = 0; i < shape.size(); ++i) {
            size *= shape[i];
        }
    }

    // Copy constructor
    Tensor(const Tensor& other) : size(other.size){
        shape = other.shape;
        data = other.data;
    }

    // Destructor
    ~Tensor() {    }

    // Assignment operator
    Tensor& operator=(const Tensor& other) {
        if (this != &other) {
            shape = other.shape;
            data = other.data;
            size = other.size;
        }
        return *this;
    }

    float* get_data_ptr() {
        return data.data();
    }

    int* get_shape(){
        return shape.data();
    }
    int get_dims(){
        return shape.size();
    }

    // [] operator
    const Tensor& operator[](int index) {
        // This is a simple example that returns a 1D tensor.
        // You need to implement this according to your requirements.
        if(index<0 || index>=shape[0]){
            cout<<"error"<<endl;
            return Tensor();
        }
        return Tensor(index, *this);
        // return Tensor(index, )
    }

    // covert size_index to shape_index
    static std::vector<int> id2index(int id, std::vector<int> shape){
        std::vector<int> index;
        index.resize(shape.size());
        int temp = id;
        for (int i = shape.size() - 1; i >= 0; i--) {
            index[i] = (temp % shape[i]);
            temp /= shape[i];
        }
        return index;
    }
    // convert shape_index to size_index
    static int index2id(std::vector<int> index, std::vector<int> shape){
        int id = 0;
        int stride = 1;
        for (int i = shape.size() - 1; i >= 0; i--) {
            id += index[i] * stride;
            stride *= shape[i];
        }
        return id;
    }

    // 实现Tensor的切片操作，比如A[1:3,4,5:9]表示取TensorA的1-3行，4列，5-9列的数据
    Tensor tensor_split(std::vector<int> start, std::vector<int> end) {
        std::vector<int> new_shape;
        // std::vector<int> new_data;
        assert(start.size() == end.size());
        for (int i = 0; i < start.size(); i++) {
            assert(start[i] < end[i]);
            new_shape.push_back(end[i] - start[i]);
        }
        int size = 1;
        for (int dim : new_shape) {
            size *= dim;
        }
        Tensor result(new_shape);
        result.data.resize(size);
        // std::cout<<"new_shape: "<<new_shape[0]<<new_shape[1]<<new_shape[2]<<std::endl;

        // copy data to new Tensor
        for (int i = 0; i < size; i++) {
            int target_index = 0;
            // 首先从i获得对应的result Tensor的indexs
            std::vector<int> indexs = id2index(i, new_shape);
            // 然后根据indexs计算出对应的原Tensor的indexs
            for (int j = 0; j < start.size(); j++) {
                indexs[j]+=start[j];
            }
            // 根据原Tensor的indexs计算出对应的size
            target_index = index2id(indexs, shape);
            result.data[i] = data[target_index];
        }

        return result;
    }

    // Print function
    void printTensor() {
        int rowSize = shape[shape.size() - 2];
        int columnSize = shape[shape.size() - 1];
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

std::mt19937* Tensor::generator = new std::mt19937(0);
std::uniform_real_distribution<float>* Tensor::fdist = new std::uniform_real_distribution<float>(0.0, 1.0);

int main() {
    // 创建一个3维的Tensor
    vector<int> shape = {2, 2, 2};
    
    Tensor tensor1(shape);
    cout << "tensor1:" << endl;
    tensor1.printTensor();

    // 测试[]运算符
    Tensor tensor2 = tensor1[0];
    cout << "tensor2:" << endl;
    tensor2.printTensor();
    cout << "tensor1[0]:" << endl;
    tensor1[0].printTensor();
    cout << "tensor1[0][0][0]:" << endl;
    tensor1[0][0].printTensor();

    // 创建一个共享内存的Tensor
    float* data = new float[8];
    for (int i = 0; i < 8; ++i) {
        data[i] = float(i);
    }
    Tensor tensor3(shape, data);
    cout << "tensor3:" << endl;
    tensor3.printTensor();
    // 输出data和tensor3.data的地址,看是否相同
    cout << "data.ptr: " << data << endl;
    cout << "tensor3.data.ptr: " << tensor3.get_data_ptr() << endl;

    // 测试拷贝构造函数
    Tensor tensor4 = tensor3;
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