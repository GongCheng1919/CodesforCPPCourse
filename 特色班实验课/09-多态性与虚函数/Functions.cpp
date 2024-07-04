/*
首先你需要实现一个Tensor类，用于存储张量的数据。
设计一个可以自动求导的Function基类，其包含forward和backward两个虚函数，分别用于计算函数值和梯度。
并且包含一个ctx的成员变量，其是一个vector对象，用于存储Tensor对象，Tensor对象是一个包含高维度的张量。
Function还重载了()运算符，其直接调用forward函数用于计算输出Tensor。
然后你需要实现一个add和一个mul类，分别用于实现Tensor加法和乘法的自动求导。
输入一个Tensor的A维度[m,n]（假设为2维），然后调用add类分别计算A+A和A*A的结果，
然后通过Function的backward，计算A+A和A*A分别对A的梯度。
记住，如果对A有多个梯度，需要将其累加。
*/
#include <vector>
#include <iostream>
#include <random>
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
    int get_dims(){
        return dims;
    }
    int get_size(){
        return size;
    }
    int* get_shape(){
        return shape;
    }
    int* get_data(){
        return data;
    }

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
    Tensor(const Tensor& other) {
        // std::cout<<"Test Here"<<std::endl;
        if (other.data!=nullptr) {
            dims = other.dims;
            size = other.size;
            ownsData = true;
            refCount = new int(1);
            shape = new int[dims];
            for (int i = 0; i < dims; ++i) {
                shape[i] = other.shape[i];
            }
            data = new T[size];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }else{
            data = nullptr;
            shape = nullptr;
            refCount = nullptr;
            dims = 0;
            size = 0;
            ownsData=false;
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
        // std::cout<<"Test Here"<<std::endl;
        if (this != &other) {
            if (data!=nullptr){
                delete[] data;
                delete[] shape;
                delete refCount;
            }
            if (other.data!=nullptr) {
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
            }else{
                data = nullptr;
                shape = nullptr;
                refCount = nullptr;
                dims = 0;
                size = 0;
                ownsData=false;
            }
        }
        return *this;
    }

    T* get_data_ptr() {
        return data;
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

    // + operator
    Tensor operator+(const Tensor& other) const {
        // This is a simple example that returns a 1D tensor.
        // You need to implement this according to your requirements.
        if (dims != other.dims) {
            std::cout << "Error: Tensors have different dimensions!" << std::endl;
            return Tensor();
        }
        for (int i = 0; i < dims; ++i) {
            if (shape[i] != other.shape[i]) {
                std::cout << "Error: Tensors have different shapes!" << std::endl;
                return Tensor();
            }
        }
        Tensor result(dims, shape);
        for (int i = 0; i < size; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    Tensor operator+=(const Tensor& other) {
        *this = *this + other;
        return *this;
    }

    // * operator
    Tensor operator*(const Tensor& other) const {
        // This is a simple example that returns a 1D tensor.
        // You need to implement this according to your requirements.
        if (dims != other.dims) {
            std::cout << "Error: Tensors have different dimensions!" << std::endl;
            return Tensor();
        }
        for (int i = 0; i < dims; ++i) {
            if (shape[i] != other.shape[i]) {
                std::cout << "Error: Tensors have different shapes!" << std::endl;
                return Tensor();
            }
        }
        Tensor result(dims, shape);
        for (int i = 0; i < size; ++i) {
            result.data[i] = data[i] * other.data[i];
        }
        return result;
    }

    // Print function
    void printTensor() {
        if(data==nullptr) {std::cout << "Empty tensor" << std::endl; return;}
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
    bool is_empty(){
        return data==nullptr;
    }
};

template <typename T>
std::mt19937* Tensor<T>::generator = new std::mt19937(0);
template <typename T>
std::uniform_real_distribution<T>* Tensor<T>::fdist = new std::uniform_real_distribution<T>(0.0, 1.0);

template <typename T>
class Function;

template <typename T>
class GradTensor: public Tensor<T> {
public:
    Tensor<T> grad;
    // 记录计算得到本tensor的所有之前的tensor，以用于反向计算图推导
    vector<GradTensor<T>*> inputs;
    // 定义一个Function对象指针列表用于存储计算得到的该函数的function对象
    Function<T>* grad_fn;

    // Tensor<T> data;
    GradTensor() : Tensor<T>() {
        grad = Tensor<T>();
        // data = *this;
    }
    GradTensor(int dims, int* shape) : Tensor<T>(dims, shape) {
        grad = Tensor<T>();
        // data = *this;
    }

    GradTensor(int dims, std::vector<int> shape) : Tensor<T>(dims, shape.data()) {
        grad = Tensor<T>();
        // data = *this;
    }

    GradTensor(const Tensor<T>& other) : Tensor<T>(other) {
        grad = Tensor<T>();
        // data = *this;
    }

    GradTensor(const GradTensor<T>& other) : Tensor<T>(other) {
        grad = other.grad;
        // data = other.data;
    }

    // Assignment operator
    GradTensor& operator=(const GradTensor& other) {
        if (this != &other) {
            // Tensor<T>::operator=(other);
            *this = other;
            grad = other.grad;
        }
        return *this;
    }

    GradTensor& operator=(const Tensor<T>& other) {
        if (this != &other) {
            // Tensor<T>::operator=(other);
            *this = other;
            grad = Tensor<T>();
            // data = *this;
        }
        return *this;
    }

    void grad_zero_(){
        if (grad.is_empty()){
            grad = Tensor<T>(this->dims, this->shape);
        }
        for (int i = 0; i < grad.get_size(); ++i) {
            grad.get_data_ptr()[i] = T(0);
        }
    }

    // 如果输出是一个标量，则不需要添加最后一层的结果
    void backward();
    void backward(Tensor<T> grad);

};

template <typename T>
class Function {
public:
    std::vector<GradTensor<T>*> ctx;
    virtual GradTensor<T> forward(GradTensor<T>& input1,GradTensor<T>& input2) = 0;
    virtual void backward(const Tensor<T>& grad) = 0;
    virtual void backward() = 0; 
    Function() {
        ctx = std::vector<GradTensor<T>*>();
    }
    GradTensor<T> operator()(GradTensor<T>& input1,GradTensor<T>& input2) {
        GradTensor<T> result = this->forward(input1, input2);
        result.grad_fn = this;
        result.inputs.push_back(&input1);
        result.inputs.push_back(&input2);
        return result;
    }
};

template <typename T>
void GradTensor<T>::backward(){
    grad_fn->backward();
    for (int i = 0; i < inputs.size(); ++i) {
        inputs[i]->backward(inputs[i]->grad);
    }
}

template <typename T>
void GradTensor<T>::backward(Tensor<T> grad){
    if (this->grad.is_empty()){
        this->grad = grad;
    }
    grad_fn->backward(grad);
    for (int i = 0; i < inputs.size(); ++i) {
        inputs[i]->backward(inputs[i]->grad);
    }
}

template <typename T>
class Add : public Function<T> {
public:
    GradTensor<T> forward(GradTensor<T>& input1,GradTensor<T>& input2) {
        // Implementation of forward function for addition
        this->ctx.push_back(&input1);
        this->ctx.push_back(&input2);
        return input1+input2;
    }
    void backward(){};
    void backward(const Tensor<T>& grad) {
        // Implementation of backward function for addition
        GradTensor<T>* input1= this->ctx[0];
        GradTensor<T>* input2= this->ctx[1];
        if (input1->grad.is_empty()){
            input1->grad_zero_();
        }
        if (input2->grad.is_empty()){
            input2->grad_zero_();
        }
        input1->grad += grad;
        input2->grad += grad;
        // for (int i = 0; i < output.get_size(); ++i) {
        //     input1.grad.data[i] = 1.0;
        //     input2.grad.data[i] = 1.0;
        // }
    }
};
template <typename T>
class Mul : public Function<T> {
public:
    GradTensor<T> forward(GradTensor<T>& input1,GradTensor<T>& input2) {
        // Implementation of forward function for multiplication
        this->ctx.push_back(&input1);
        this->ctx.push_back(&input2);
        return input1*input2;
    }
    void backward(){};

    void backward(const Tensor<T>& grad) {
        // Implementation of backward function for multiplication
        GradTensor<T>* input1 = this->ctx[0];
        GradTensor<T>* input2 = this->ctx[1];
        if (input1->grad.is_empty()){
            input1->grad_zero_();
        }
        if (input2->grad.is_empty()){
            input2->grad_zero_();
        }
        input1->grad += *input2*grad;
        input2->grad += *input1*grad;
    }
};

int main() {
    using T=float;
    // Create a GradTensor<T> object A with dimensions [m, n]
    // vector<int>  shape = {1,2,3};
    int m,n,k;
    cin>>m>>n>>k;
    vector<int>  shape = {m,n,k};
    GradTensor<T> A(3, shape.data());
    std::cout<<"Tensor A:"<<std::endl;
    A.printTensor();
    

    // Create instances of Add and Mul classes
    Add<T> add;
    Mul<T> mul;

    // Calculate A + A and A * A using the add and mul objects
    GradTensor<T> resultMul = mul.forward(A,A);
    std::cout<<"\nTensor A*A:"<<std::endl;
    resultMul.printTensor();
    GradTensor<T> resultAdd = add.forward(resultMul,A);
    std::cout<<"\nTensor A*A + A:"<<std::endl;
    resultAdd.printTensor();

    // Tensor<T> gradA;
    // // Calculate gradients of A*A + A with respect to A
    // A.grad=Tensor<T>();
    add.backward(A);
    std::cout<<"\nA's grad after add backward:"<<std::endl;
    A.grad.printTensor();
    std::cout<<"\n(A*A)'s grad after add backward:"<<std::endl;
    resultMul.grad.printTensor();
    // A.grad=Tensor<T>();
    mul.backward(resultMul.grad);
    std::cout<<"\nA's grad after (A*A)+A backward:"<<std::endl;
    A.grad.printTensor();

    // A.grad_zero_();
    // std::cout<<"\nA's grad after grad_zero_: "<<std::endl;
    // A.grad.printTensor();
    // GradTensor<T> FWresult1 = mul(A,A);
    // GradTensor<T> FWresult2 = add(FWresult1,A);
    // std::cout<<"\nFWresult2's values: "<<std::endl;
    // FWresult2.printTensor();
    // FWresult2.backward(A);
    // std::cout<<"\nA's grad after FWresult2.backward(A): "<<std::endl;
    // A.grad.printTensor();

    return 0;
}

