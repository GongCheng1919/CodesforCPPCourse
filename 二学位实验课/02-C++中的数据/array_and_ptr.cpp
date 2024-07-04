#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <random>
#include <chrono>
#include <iostream>

using namespace std;

void sort_input_int(){
    string s;
    int n, *a, *tmp, arr_len=100;
    float ratio=1.5;
    int size=0;
    a=new int[arr_len];
    getline(cin, s);
    std::stringstream ss(s);
    while(ss>>n){
        if (size>=arr_len){
            arr_len=int(arr_len*ratio);
            tmp = a;
            a=new int[arr_len];
            for (int i=0;i<size;i++){
                a[i]=tmp[i];
            }
            delete[] tmp;
            tmp = nullptr;
        }
        a[size++]=n;
    }
    std::sort(a, a+size);

    for (int i = 0; i < size; i++) {
        std::cout << a[i];
        if (i!=size-1) cout<< " ";
        else cout<<endl;
    }
    delete[] a;
    // std::cout << std::endl;
}

void sort_float(){
    int n;
    cin>>n;
    std::mt19937 gen(0); // mt19937 is a standard mersenne_twister_engine
    std::uniform_real_distribution<float> dist(0.0, 1.0);
    // 生成随机浮点数
    float *f = new float[n];
    for (int i = 0; i < n; ++i) {
        f[i] = dist(gen);
    }
    std::sort(f, f+n);

    int num = 10;
    
    for (int i = 0; i < (n>num?num:n); i++) {
        std::cout << f[i];
        if (i!=n-1) cout<< endl;
        else cout<<endl;
    }
    // cout<<endl<<count<<endl;
    delete[] f;
    // std::cout << std::endl;
}

void parse_float(const float f, int* sign,int* exp,int* mant){
    // 解析浮点数为三个整型，分别保存其符号位，指数位和尾数位（尾数位记得包含隐藏位1）
    *sign = (f>0?1:-1);
    unsigned int u = *(unsigned int*)&f;
    *exp = (u>>23) & 0xff;
    *mant = (u & 0x7fffff)|0x800000;
    // std::cout<<*sign<<" "<<*exp<<" "<<*mant<<std::endl;
}

void construct_float(const int sign,const int exp,const int mant, float* f){
    // 将整型的符号位，指数位和尾数位转换为浮点数，记得尾数位的隐藏位1
    unsigned int u = (sign>0?0:0x80000000) | (exp<<23) | (mant&0x7fffff);
    // std::cout<<"mant="<<mant<<std::endl;
    *f = *(float*)&u;
    // std::cout<<sign<<" "<<exp<<" "<<mant<<std::endl;
}

// add two float numbers
void add_decomposed_float(int* dst_sign, int* dst_exp, int* dst_mant, int src_sign, int src_exp, int src_mant){
    // 计算两个浮点数的和
    // 1、对阶 
    if (*dst_exp < src_exp) {
        *dst_mant >>= (src_exp - *dst_exp);
        *dst_exp = src_exp;
    } else {
        src_mant >>= (*dst_exp - src_exp);
    }

    // 2、尾数相加
    src_mant = src_sign*src_mant;
    *dst_mant = (*dst_sign)*(*dst_mant);
    // std::cout<<"src_mant="<<src_mant<<std::endl;
    // std::cout<<"dst_mant="<<*dst_mant<<std::endl;
    *dst_mant += src_mant;
    // std::cout<<"dst_mant="<<*dst_mant<<std::endl;
    if (*dst_mant<0){
        *dst_mant = -(*dst_mant);
        *dst_sign = -1;
    }else{
        *dst_sign = 1;
    }

    // 3、规格化：获取最高位1的位置，然后和23位对齐，如果大于23则右移，小于23则左移
    int pos = 0;
    for (int i = 0; i < 32; i++) {
        if (*dst_mant & (1 << i)) {
            pos = i;
        }
    }
    if (pos > 23) {
        *dst_mant >>= (pos - 23);
        *dst_exp += pos - 23;
    } else {
        *dst_mant <<= (23 - pos);
        *dst_exp -= 23 - pos;
    }
    // if (*dst_mant & 1<<24) {
    //     *dst_mant >>= 1;
    //     (*dst_exp)++;
    // }
    // std::cout<<"dst_mant="<<*dst_mant<<std::endl;
    // 4、舍入
    // 5、溢出判断
    if (*dst_exp >= 255) {
        // Overflow, return infinity
        *dst_exp = 255;
        *dst_mant = 0;
    }
}

void mul_decomposed_float(int* dst_sign, int* dst_exp, int* dst_mant, int src_sign, int src_exp, int src_mant){
    // 计算两个浮点数的积
    *dst_sign = *dst_sign * src_sign;
    // 1、计算指数
    *dst_exp += src_exp - 127 - 23; // 注意尾数位应该是1.X*2^23 * 1.X*2^23 = XX, 所以对这个乘法的结果，还要-23个指数
    // 2、计算尾数
    long long tmp =((long long)(*dst_mant)) * ((long long)(src_mant)); 
    // *dst_mant = ((*dst_mant & 0x007fffff) | 0x00800000) * ((src_mant & 0x007fffff) | 0x00800000);
    cout<<*dst_sign<<" "<<*dst_exp<<" "<<tmp<<endl;
    // 3、规格化
    // 找到最高位1的位置
    int pos = 0;
    long long tmp1 = 1;
    for (int i = 0; i < 64; i++) {
        // cout<<(tmp1<<i)<<endl;
        if (tmp & (tmp1 << i)) {
            pos = i;
        }
    }
    // cout<<tmp<<",--"<<(tmp>>40)<<endl;
    // cout<<pos<<endl;
    if (pos > 23) {
        tmp = (tmp >> (pos - 23));
        *dst_exp += pos - 23;
    } else {
        tmp = (tmp << (23 - pos));
        *dst_exp -= 23 - pos;
    }
    *dst_mant = (int)tmp;
    // cout<<"tmp="<<tmp<<", *dst_mant="<<*dst_mant<<endl;
    // *dst_mant = (tmp >> (pos - 23)) & 0x007fffff;
    // *dst_exp += pos - 23;
    // 4、舍入
    // 5、溢出判断
    if (*dst_exp >= 255) {
        // Overflow, return infinity
        *dst_exp = 255;
        *dst_mant = 0;
    }
}

void div_decomposed_float(int* dst_sign, int* dst_exp, int* dst_mant, int src_sign, int src_exp, int src_mant){
    // 计算两个浮点数的商
    *dst_sign = *dst_sign * src_sign;
    // 1、计算指数
    *dst_exp = *dst_exp - src_exp + 127-(39-23);
    // 2、计算尾数
    long long tmp = (long long)(*dst_mant);
    tmp = (tmp << 39);
    // cout<<tmp<<endl; 
    tmp = tmp / (src_mant);
    // 3、规格化
    // 找到最高位1的位置
    int pos = 0;
    long long tmp1 = 1;
    for (int i = 0; i < 64; i++) {
        // cout<<(tmp1<<i)<<endl;
        if (tmp & (tmp1 << i)) {
            pos = i;
        }
    }
    // 输出未规格化的，最高精度的中间指数和尾数结果
    cout <<*dst_exp<<" "<<tmp<<endl;
    // cout<<tmp<<",--"<<(tmp>>23)<<endl;
    // cout<<pos<<endl;
    if (pos > 23) {
        tmp = (tmp >> (pos - 23));
        *dst_exp += pos - 23;
    } else {
        tmp = (tmp << (23 - pos));
        *dst_exp -= 23 - pos;
    }
    *dst_mant = (int)tmp;
}



float compute_float_with_int(){
// 通过手动获取float类型的符号位，指数位和尾数位并存储为整型，使用整型算术运算来实现浮点数的四则运算（+-*/）。
/*需要按以下步骤完成浮点的四则运算：
1、输入两个浮点数，和一个四则运算符；
2、解析浮点数为三个整型，分别保存其符号位，指数位和尾数位；
3、根据计算规则，使用解析后的整型完成对应浮点因子的四则运算；
4、将计算结果转换为浮点值，并输出到屏幕（保留6位有效数组）。

输入：两个浮点数一个运算符
输出：浮点数的运算结果。
     * 
     */
    float a, b, result, re_a, re_b;
    char op;
    int sign1, exp1, mant1, sign2, exp2, mant2;
    cin>>a>>b>>op;
    parse_float(a, &sign1, &exp1, &mant1);
    parse_float(b, &sign2, &exp2, &mant2);
    // construct_float(sign1, exp1, mant1, &re_a);
    // construct_float(sign2, exp2, mant2, &re_b);
    // cout<<re_a<<endl<<re_b<<endl;
    cout<<sign1<<" "<<exp1<<" "<<mant1<<endl;
    cout<<sign2<<" "<<exp2<<" "<<mant2<<endl;
    switch (op)
    {
    case '+':
        add_decomposed_float(&sign1, &exp1, &mant1, sign2, exp2, mant2);
        // 计算两个浮点数的和
        break;
    case '-':
        add_decomposed_float(&sign1, &exp1, &mant1, -sign2, exp2, mant2);
        // 计算两个浮点数的差
        break;
    case '*':
        mul_decomposed_float(&sign1, &exp1, &mant1, sign2, exp2, mant2);
        // 计算两个浮点数的积
        break;
    case '/':
        div_decomposed_float(&sign1, &exp1, &mant1, sign2, exp2, mant2);
        // 计算两个浮点数的商
        break;
    default:
        break;
    }
    // construct float
    cout<<sign1<<" "<<exp1<<" "<<mant1<<endl;
    construct_float(sign1, exp1, mant1, &result);
    cout<<result<<endl;
    return result;
}

class Float {
public:
    float value;

    Float(float val) : value(val) {
        parse_float(value, &sign, &exp, &mant);
    }

    Float operator+(const Float& other) {
        int result_sign = sign, result_exp = exp, result_mant = mant;
        add_decomposed_float(&result_sign, &result_exp, &result_mant, other.sign, other.exp, other.mant);
        float result_value;
        construct_float(result_sign, result_exp, result_mant, &result_value);
        return Float(result_value);
    }

    Float operator-(const Float& other) {
        int result_sign = sign, result_exp = exp, result_mant = mant;
        add_decomposed_float(&result_sign, &result_exp, &result_mant, -other.sign, other.exp, other.mant);
        float result_value;
        construct_float(result_sign, result_exp, result_mant, &result_value);
        return Float(result_value);
    }

    Float operator*(const Float& other) {
        int result_sign = sign, result_exp = exp, result_mant = mant;
        mul_decomposed_float(&result_sign, &result_exp, &result_mant, other.sign, other.exp, other.mant);
        float result_value;
        construct_float(result_sign, result_exp, result_mant, &result_value);
        return Float(result_value);
    }

    Float operator/(const Float& other) {
        int result_sign = sign, result_exp = exp, result_mant = mant;
        div_decomposed_float(&result_sign, &result_exp, &result_mant, other.sign, other.exp, other.mant);
        float result_value;
        construct_float(result_sign, result_exp, result_mant, &result_value);
        return Float(result_value);
    }

    Float& operator+=(const Float& other) {
        int result_sign = sign, result_exp = exp, result_mant = mant;
        add_decomposed_float(&result_sign, &result_exp, &result_mant, other.sign, other.exp, other.mant);
        float result_value;
        construct_float(result_sign, result_exp, result_mant, &result_value);
        value = result_value;
        return *this;
    }

private:
    int sign, exp, mant;
};


template<typename T>
void gemm(const T* A, const T* B, T* C, int m, int n, int k) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int p = 0; p < k; ++p) {
                C[i*n+j] += A[i*k+p] * B[p*n+j];
            }
        }
    }
}

int test_Float_gemm() {
    int n = 100;
    std::vector<std::vector<float>> A(n, std::vector<float>(n, 1.0f));
    std::vector<std::vector<float>> B(n, std::vector<float>(n, 1.0f));

    auto start = std::chrono::high_resolution_clock::now();
    auto C = gemm(A, B);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to perform GEMM with float: " << diff.count() << " s\n";

    std::vector<std::vector<Float>> A_float(n, std::vector<Float>(n, Float(1.0f)));
    std::vector<std::vector<Float>> B_float(n, std::vector<Float>(n, Float(1.0f)));

    start = std::chrono::high_resolution_clock::now();
    auto C_float = gemm(A_float, B_float);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "Time to perform GEMM with Float: " << diff.count() << " s\n";

    return 0;
}


int main() {
    
    // sort_input_int();
    // sort_float();
    // compute_float_with_int();
    // Float a(1.5), b(3.0);
    // Float c = a / b;
    // cout << c.value << endl;
    test_Float_gemm();

    return 0;
}