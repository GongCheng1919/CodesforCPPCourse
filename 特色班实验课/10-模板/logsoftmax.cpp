/*
实现一个logsoftmax函数，其输入是一个矩阵，输出是对矩阵的每一行进行logsoftmax操作后的结果。
其中，矩阵的行数为N，表示的batchsize大小，列数为C，表示的类别是。
logsoftmax的定义如下（每一行的操作）：
    $$logsoftmax(x_{i,j}) = log(exp(x_{i,j}) / sum_1^j(exp(x_{i,j})))$$
logsoftmax的计算过程中，需要计算每一行的exp和sum，因此需要对矩阵进行遍历。
logsoftmax的反向传播过程中，需要计算softmax的导数，其计算公式（以N=1为例）如下：
    `logsoftmax`函数是一种常用的归一化函数，它将一个实数向量转化为概率分布，并对其取对数。具体的公式如下：

    假设输入向量为 $x = (x_1, x_2, ..., x_n)$，`logsoftmax`的前向计算公式为：

    $$
    \text{logsoftmax}(x_i) = \log\left(\frac{e^{x_i}}{\sum_{j=1}^{n}e^{x_j}}\right)
    $$

    对于`logsoftmax`的反向求导，我们需要计算出其梯度，对于梯度的计算，我们需要分两种情况来讨论：

    1. 当 $i = j$ 时：

    $$
    \frac{\partial \text{logsoftmax}(x_i)}{\partial x_i} = 1 - \exp(\text{logsoftmax}(x_i))
    $$

    2. 当 $i \neq j$ 时：

    $$
    \frac{\partial \text{logsoftmax}(x_i)}{\partial x_j} = - \exp(\text{logsoftmax}(x_j))
    $$

    这里，$\text{logsoftmax}(x_i)$ 和 $\text{logsoftmax}(x_j)$ 分别表示 `logsoftmax` 函数在 $x_i$ 和 $x_j$ 处的值。

你也可以使用log函数和softmax函数来实现logsoftmax函数，但是注意数值稳定性问题，就是注意数值不要溢出到0或者无穷。
*/


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
#include <cmath>
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
    T& operator[](vector<int> indexes) {
        // This is a simple example that returns a 1D tensor.
        // You need to implement this according to your requirements.
        int index =0;
        for (int i = 0; i < indexes.size(); ++i) {
            index = index*shape[i]+indexes[i];
        }
        if(index<0 || index>=size){
            cout<<"error index!"<<endl;
            return data[0];
        }
        return data[index];
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
    bool is_empty() const{
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
    void backward(const Tensor<T>& grad = Tensor<T>());

};

template <typename T>
class Function {
public:
    std::vector<GradTensor<T>*> ctx;
    virtual GradTensor<T>& forward(GradTensor<T>& input1,GradTensor<T>& input2){};
    virtual GradTensor<T>& forward(GradTensor<T>& input1){};
    virtual void backward(const Tensor<T>& grad = Tensor<T>(), bool release_output=true){};
    // virtual void backward(){};
    Function() {
        ctx = std::vector<GradTensor<T>*>();
    }
    GradTensor<T>& operator()(GradTensor<T>& input1,GradTensor<T>& input2) {
        GradTensor<T>& result = this->forward(input1, input2);
        result.grad_fn = this;
        result.inputs.push_back(&input1);
        result.inputs.push_back(&input2);
        return result;
    }
    GradTensor<T>& operator()(GradTensor<T>& input1) {
        GradTensor<T>& result = this->forward(input1);
        result.grad_fn = this;
        result.inputs.push_back(&input1);
        return result;
    }
};


template <typename T>
void GradTensor<T>::backward(const Tensor<T>& grad){
    // if (!grad.is_empty()){
    //     this->grad = grad;
    // }
    // 运行完该backward后会delete掉对象本身，那么其grad_fn和inputs也会被删除，所以需要先保存grad_fn和inputs
    // Function<T>* tmp_grad_fn = this->grad_fn;
    // vector<GradTensor<T>*> tmp_inputs = this->inputs;

    this->grad.printTensor();
    grad_fn->backward(grad, false);
    this->grad.printTensor();
    for (int i = 0; i < inputs.size(); ++i) {
        inputs[i]->backward();
    }
    delete this;
}

template <typename T>
class Add : public Function<T> {
public:
    GradTensor<T>& forward(GradTensor<T>& input1,GradTensor<T>& input2) {
        // Implementation of forward function for addition
        this->ctx.push_back(&input1);
        this->ctx.push_back(&input2);
        GradTensor<T>* result = new GradTensor<T>(input1+input2);
        this->ctx.push_back(result);
        return *result;
    }
    void backward(const Tensor<T>& grad = Tensor<T>(), bool release_output=true) {
        // Implementation of backward function for addition
        GradTensor<T>* input1= this->ctx[0];
        GradTensor<T>* input2= this->ctx[1];
        GradTensor<T>* result= this->ctx[2];
        if (!grad.is_empty()){
            result->grad = grad;
        }
        if (input1->grad.is_empty()){
            input1->grad_zero_();
        }
        if (input2->grad.is_empty()){
            input2->grad_zero_();
        }
        input1->grad += result->grad;
        input2->grad += result->grad;
        // for (int i = 0; i < output.get_size(); ++i) {
        //     input1.grad.data[i] = 1.0;
        //     input2.grad.data[i] = 1.0;
        // }
        // 在这里删除results
        if (release_output){
            delete result;
        }
        this->ctx=std::vector<GradTensor<T>*>();
    }
};

template <typename T>
class Mul : public Function<T> {
public:
    GradTensor<T>& forward(GradTensor<T>& input1,GradTensor<T>& input2) {
        // Implementation of forward function for multiplication
        this->ctx.push_back(&input1);
        this->ctx.push_back(&input2);
        GradTensor<T>* result = new GradTensor<T>(input1*input2);
        this->ctx.push_back(result);
        return *result;
    }

    void backward(const Tensor<T>& grad = Tensor<T>(),bool release_output=true) {
        // Implementation of backward function for multiplication
        GradTensor<T>* input1 = this->ctx[0];
        GradTensor<T>* input2 = this->ctx[1];
        GradTensor<T>* result = this->ctx[2];
        if (!grad.is_empty()){
            result->grad = grad;
        }
        if (input1->grad.is_empty()){
            input1->grad_zero_();
        }
        if (input2->grad.is_empty()){
            input2->grad_zero_();
        }
        input1->grad += *input2*result->grad;
        input2->grad += *input1*result->grad;

        // 在这里删除results
        if (release_output){
            delete result;
        }
        this->ctx=std::vector<GradTensor<T>*>();
    }
};

template <typename T>
class LogSoftmax : public Function<T> {
public:
    GradTensor<T>& forward(GradTensor<T>& input1) {
        // Implementation of forward function for multiplication
        this->ctx.push_back(&input1);
        // return input1*input2;
        // 计算logsoftmax的值
        // step 1： check the input shape is 2D
        GradTensor<T>* result = new GradTensor<T>(input1.get_dims(), input1.get_shape());
        if (input1.get_dims()!=2){
            cout<<"Error: The input shape is not 2D"<<endl;
            return *result;
        }
        // step 2: calculate the softmax value
        // $$logsoftmax(x_{i,j}) = log(exp(x_{i,j}) / sum_1^j(exp(x_{i,j})))$$
        for (int i = 0; i < input1.get_shape()[0]; ++i) {
            T max_value = input1[{i,0}];
            for (int j = 1; j < input1.get_shape()[1]; ++j) {
                // sum += exp(input1[{i,j}]);
                if (input1[{i,j}] > max_value){
                    max_value = input1[{i,j}];
                }
            }
            T sum = 0;
            for (int j = 0; j < input1.get_shape()[1]; ++j) {
                sum += exp(input1[{i,j}]-max_value);
            }
            for (int j = 0; j < input1.get_shape()[1]; ++j) {
                (*result)[{i,j}] = log(exp(input1[{i,j}]-max_value)/sum);
            }
        }
        this->ctx.push_back(result);
        return *result;
    }
    void backward(const Tensor<T>& grad = Tensor<T>(),bool release_output=true){
        std::cout<<"LogSoftmax backward"<<std::endl;
        GradTensor<T>* input1 = this->ctx[0];
        GradTensor<T>* result = this->ctx[1];
        if (!grad.is_empty()){
            result->grad = grad;
        }
        // 计算logsoftmax对input1的梯度，即input1.grad
        /*
        1. 当 $i = j$ 时：
        $$
        \frac{\partial \text{logsoftmax}(x_i)}{\partial x_i} = 1 - \exp(\text{logsoftmax}(x_i))
        $$

        2. 当 $i \neq j$ 时：
        $$
        \frac{\partial \text{logsoftmax}(x_i)}{\partial x_j} = - \exp(\text{logsoftmax}(x_j))
        $$
        */
        if (input1->grad.is_empty()){
            input1->grad_zero_();
        }
        for (int k = 0; k < input1->get_shape()[0]; ++k) {
            for (int i = 0; i < input1->get_shape()[1]; ++i) {
                for (int j = 0; j < input1->get_shape()[1]; ++j) {
                    if (j==i){
                        input1->grad[{k,j}] += (1 - exp((*result)[{k,j}]))*result->grad[{k,i}];
                    }else{
                        input1->grad[{k,j}] += -exp((*result)[{k,j}])*result->grad[{k,i}];
                    }
                }
            }
        }
        // 在这里删除results
        if (release_output){
            delete result;
        }
        this->ctx=std::vector<GradTensor<T>*>();
    };
};


int main() {
    using T=float;
    // Create a GradTensor<T> object A with dimensions [m, n]
    // vector<int>  shape = {1,2,3};
    int m=1,n=2,k=3;
    // cin>>m>>n>>k;
    vector<int>  shape = {n,k};
    GradTensor<T> A(2, shape.data());
    std::cout<<"Tensor A:"<<std::endl;
    A.printTensor();
    

    // // Create instances of Add and Mul classes
    // Add<T> add;
    // Mul<T> mul;

    // // Calculate A + A and A * A using the add and mul objects
    // GradTensor<T> resultMul = mul.forward(A,A);
    // std::cout<<"\nTensor A*A:"<<std::endl;
    // resultMul.printTensor();
    // GradTensor<T> resultAdd = add.forward(resultMul,A);
    // std::cout<<"\nTensor A*A + A:"<<std::endl;
    // resultAdd.printTensor();

    // // Tensor<T> gradA;
    // // // Calculate gradients of A*A + A with respect to A
    // // A.grad=Tensor<T>();
    // add.backward(A);
    // std::cout<<"\nA's grad after add backward:"<<std::endl;
    // A.grad.printTensor();
    // std::cout<<"\n(A*A)'s grad after add backward:"<<std::endl;
    // resultMul.grad.printTensor();
    // // A.grad=Tensor<T>();
    // mul.backward(resultMul.grad);
    // std::cout<<"\nA's grad after (A*A)+A backward:"<<std::endl;
    // A.grad.printTensor();


    // 不使用中间变量而直接使用动态变量试试
    Add<T> add1;
    Mul<T> mul1;
    LogSoftmax<T> logsoftmax;
    A.grad_zero_();
    // GradTensor<T> resultMulAddLogSoftmax = logsoftmax.forward(add1.forward(mul1.forward(A,A),A));
    GradTensor<T> resultMulAddLogSoftmax = logsoftmax(add1(mul1(A,A),A));
    std::cout<<"\nresultMulAddLogSoftmax:"<<std::endl;
    resultMulAddLogSoftmax.printTensor();

    logsoftmax.backward(A);
    std::cout<<"\nOnePass: A's grad after LogSoftmax backward:"<<std::endl;
    A.grad.printTensor();
    add1.backward();
    std::cout<<"\nOnePass: A's grad after add backward:"<<std::endl;
    A.grad.printTensor();
    // A.grad=Tensor<T>();
    mul1.backward();
    std::cout<<"\nOnePass: A's grad after (A*A)+A backward:"<<std::endl;
    A.grad.printTensor();

    // resultMulAddLogSoftmax.backward(A);
    // std::cout<<"\nOnePass: A's grad after (A*A)+A backward:"<<std::endl;
    // A.grad.printTensor();

    return 0;
}