

class Tensor {
protected:
    T* data;
    int* shape;
    int dims;
    int size;
    // Add a reference count to the Tensor class
    bool ownsData;
    int* refCount;
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
};

// std::mt19937* Tensor::generator = new std::mt19937(0);
// std::uniform_real_distribution<float>* Tensor::fdist = new std::uniform_real_distribution<float>(0.0, 1.0);

class GradTensor: public Tensor {
public:
    Tensor grad;
};

class Function {
public:
    std::vector<GradTensor*> ctx;
    virtual GradTensor forward(GradTensor& input1,GradTensor& input2) = 0;
    virtual void backward(const GradTensor& output) = 0;
    Function() {
        ctx = std::vector<GradTensor*>();
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
    add.backward(A);
    std::cout<<"\nA's grad after add backward:"<<std::endl;
    A.grad.printTensor();
    std::cout<<"\n(A*A)'s grad after add backward:"<<std::endl;
    resultMul.grad.printTensor();
    mul.backward(resultMul.grad);
    std::cout<<"\nA's grad after (A*A)+A backward:"<<std::endl;
    A.grad.printTensor();

    return 0;
}