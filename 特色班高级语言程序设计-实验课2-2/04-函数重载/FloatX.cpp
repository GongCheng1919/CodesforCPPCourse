#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <random>
#include <chrono>
#include <cassert>
#include <cmath>

using namespace std;

string int2bit(int v){
    // 将整数转换为二进制字符串
    string res;
    for (int i = 31; i >= 0; i--) {
        if ((i+1)%8==0){
            res += " ";
        }
        res += to_string((v >> i) & 1);
    }
    return res;

}

void quantize_float(int* exp,int* mant, int exp_bits=-1, int mant_bits=-1){
    exp_bits = exp_bits==-1?8:exp_bits;
    mant_bits = mant_bits==-1?23:mant_bits;
    int mant_mask = ((1<<(mant_bits>23?23:mant_bits))-1)<<(23-mant_bits>0?23-mant_bits:0);
    int mant_hiddent_bit = 1<<23;
    int max_exp = (1<<(exp_bits-1))-1;
    int min_exp = -(1<<(exp_bits-1));
    if (*exp>max_exp+127){
        *exp = max_exp+127;
        *mant = mant_mask;
        return;
    }
    if (*exp<min_exp+127){
        *exp = 0;
        *mant = mant_hiddent_bit;
        return;
    }
    *mant = (*mant & mant_mask)|mant_hiddent_bit;
}


// void parse_float(const float f, int* sign,int* exp,int* mant){
//     // 解析浮点数为三个整型，分别保存其符号位，指数位和尾数位（尾数位记得包含隐藏位1）
//     *sign = (f>0?1:-1);
//     unsigned int u = *(unsigned int*)&f;
//     *exp = ((u>>23) & 0xff);
//     *mant = (u & 0x7fffff)|0x800000;
// }

void parse_float(const float f, int* sign,int* exp,int* mant){
    // 解析浮点数为三个整型，分别保存其符号位，指数位和尾数位（尾数位记得包含隐藏位1）
    // 我们这里先用模拟的算哈，如果exp_bit是4bit，那么其范围应该是-8->7，对应的8bit指数位就是
    // exp_bits = exp_bits==-1?8:exp_bits;
    // mant_bits = mant_bits==-1?23:mant_bits;
    // mant_bits = mant_bits+1;
    // int mant_mask = ((1<<(mant_bits>23?23:mant_bits))-1)<<(23-mant_bits>0?23-mant_bits:0);
    // cout<<"mant_bits = "<<mant_bits<<" mant_mask = "<<mant_mask<<" mant_mask bit string = "<<int2bit(mant_mask)<<endl;
    // int mant_hiddent_bit = 1<<23;
    *sign = (f>0?1:-1);
    unsigned int u = *(unsigned int*)&f;
    *exp = ((u>>23) & 0xff);
    // int max_exp = (1<<(exp_bits-1))-1;
    // int min_exp = -(1<<(exp_bits-1));
    // if (*exp>max_exp+127){
    //     *exp = max_exp+127;
    //     *mant = mant_mask;
    //     // cout<<"exp = "<<*exp<<endl;
    //     // cout<<"mant = "<<*mant<<" mant bit string = "<<int2bit(*mant)<<endl;
    //     return;
    // }
    // if (*exp<min_exp+127){
    //     *exp = 0;
    //     *mant = mant_hiddent_bit;
    //     // cout<<"exp = "<<*exp<<endl;
    //     // cout<<"mant = "<<*mant<<" mant bit string = "<<int2bit(*mant)<<endl;
    //     return;
    // }
    // cout<<"exp = "<<*exp<<endl;
    // cout<<"u = "<<u<<" u bit string = "<<int2bit(u)<<endl;
    // *mant = (u & mant_mask)|mant_hiddent_bit;
    *mant = (u & 0x7fffff)|0x800000;
    // cout<<"mant = "<<*mant<<" mant bit string = "<<int2bit(*mant)<<endl;
    // if (*exp==0 && *mant==0x800000){
    //     // *exp = 0;
    //     // 浮点数是0
    // }
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
    if (*dst_exp==0 && *dst_mant==0x800000){
        // 浮点数是0
        *dst_sign = src_sign;
        *dst_exp = src_exp;
        *dst_mant = src_mant;
        return;
    }
    if (src_exp==0 && src_mant==0x800000){
        // 浮点数是0
        return;
    }

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
    // 计算两个浮点数
    // cout<<"dst_exp = "<<*dst_exp<<" dst_mant = "<<int2bit(*dst_mant)<<endl;
    // cout<<"src_exp = "<<src_exp<<" src_mant = "<<int2bit(src_mant)<<endl;
    if ((*dst_exp==0 && *dst_mant==0x800000) ||src_exp==0 && src_mant==0x800000){
        // 浮点数是0
        // cout<<"Test zero multiplication"<<endl;
        *dst_sign = src_sign;
        *dst_exp = 0;
        *dst_mant = 0x800000;
        return;
    }
    // if (src_exp==0 && src_mant==0x800000){
    //     // 浮点数是0
    //     return;
    // }

    // 计算两个浮点数的积
    *dst_sign = *dst_sign * src_sign;
    // 1、计算指数
    *dst_exp += src_exp - 127 - 23; // 注意尾数位应该是1.X*2^23 * 1.X*2^23 = XX, 所以对这个乘法的结果，还要-23个指数
    // 2、计算尾数
    long long tmp =((long long)(*dst_mant)) * ((long long)(src_mant)); 
    // *dst_mant = ((*dst_mant & 0x007fffff) | 0x00800000) * ((src_mant & 0x007fffff) | 0x00800000);
    // cout<<*dst_sign<<" "<<*dst_exp<<" "<<tmp<<endl;
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
    // 计算两个浮点数
    if ((*dst_exp==0 && *dst_mant==0x800000)){
        // 浮点数是0
        *dst_sign = src_sign;
        *dst_exp = 0;
        *dst_mant = 0x800000;
        return;
    }
    if (src_exp==0 && src_mant==0x800000){
        // 浮点数是0
        // *dst_sign = src_sign*(*dst_sign);
        *dst_exp = 255;
        *dst_mant = 0x800000;
        return;
    }
    
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
    // cout<<*dst_sign <<" "<<*dst_exp<<" "<<tmp<<endl;
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

    Float() : value(0.0f) {
        parse_float(value, &sign, &exp, &mant);
    }

    Float& operator=(const Float& other) {
        if (this != &other) {
            value = other.value;
            sign = other.sign;
            exp = other.exp;
            mant = other.mant;
        }
        return *this;
    }

    Float& operator=(const float val) {
        value = val;
        parse_float(value, &sign, &exp, &mant);
        return *this;
    }

    Float(float val) : value(val) {
        parse_float(value, &sign, &exp, &mant);
    }

    Float operator+(const Float& other) const {
        int result_sign = sign, result_exp = exp, result_mant = mant;
        add_decomposed_float(&result_sign, &result_exp, &result_mant, other.sign, other.exp, other.mant);
        float result_value;
        construct_float(result_sign, result_exp, result_mant, &result_value);
        return Float(result_value);
    }

    Float operator-(const Float& other) const {
        int result_sign = sign, result_exp = exp, result_mant = mant;
        add_decomposed_float(&result_sign, &result_exp, &result_mant, -other.sign, other.exp, other.mant);
        float result_value;
        construct_float(result_sign, result_exp, result_mant, &result_value);
        return Float(result_value);
    }

    Float operator*(const Float& other) const {
        int result_sign = sign, result_exp = exp, result_mant = mant;
        mul_decomposed_float(&result_sign, &result_exp, &result_mant, other.sign, other.exp, other.mant);
        float result_value;
        construct_float(result_sign, result_exp, result_mant, &result_value);
        return Float(result_value);
    }

    Float operator/(const Float& other) const {
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

    friend ostream& operator<<(ostream& out, const Float& m)
    {
        out << m.value;
        return out;
    }

protected:
    int sign, exp, mant;
};

class FloatX:public Float{
    
protected:
    int exp_bits, mant_bits;

public:
    float value;

    FloatX() : value(0.0f), exp_bits(8), mant_bits(23){
        parse_float(value, &sign, &exp, &mant);
    }
    
    FloatX& operator=(const FloatX& other) {
        if (this != &other) {
            value = other.value;
            sign = other.sign;
            exp = other.exp;
            mant = other.mant;
        }
        return *this;
    }

    FloatX& operator=(const float val) {
        value = val;
        parse_float(value, &sign, &exp, &mant);
        quantize_float(&exp, &mant, exp_bits, mant_bits);
        construct_float(sign, exp, mant, &value);
        return *this;
    }

    FloatX(float val, int exp_bits, int mant_bits) : value(val), exp_bits(exp_bits), mant_bits(mant_bits){
        parse_float(value, &sign, &exp, &mant);
        quantize_float(&exp, &mant, exp_bits, mant_bits);
        construct_float(sign, exp, mant, &value);
    }

    FloatX operator+(const FloatX& other) const {
        int result_sign = sign, result_exp = exp, result_mant = mant;
        add_decomposed_float(&result_sign, &result_exp, &result_mant, other.sign, other.exp, other.mant);
        
        quantize_float(&result_exp, &result_mant, exp_bits, mant_bits);
        float result_value;
        construct_float(result_sign, result_exp, result_mant, &result_value);

        return FloatX(result_value, exp_bits, mant_bits);
    }

    FloatX operator-(const FloatX& other) const {
        int result_sign = sign, result_exp = exp, result_mant = mant;
        add_decomposed_float(&result_sign, &result_exp, &result_mant, -other.sign, other.exp, other.mant);
        
        quantize_float(&result_exp, &result_mant, exp_bits, mant_bits);
        float result_value;
        construct_float(result_sign, result_exp, result_mant, &result_value);
        return FloatX(result_value, exp_bits, mant_bits);
    }

    FloatX operator*(const FloatX& other) const {
        int result_sign = sign, result_exp = exp, result_mant = mant;
        mul_decomposed_float(&result_sign, &result_exp, &result_mant, other.sign, other.exp, other.mant);
        quantize_float(&result_exp, &result_mant, exp_bits, mant_bits);
        float result_value;
        construct_float(result_sign, result_exp, result_mant, &result_value);
        return FloatX(result_value, exp_bits, mant_bits);
    }

    FloatX operator/(const FloatX& other) const {
        int result_sign = sign, result_exp = exp, result_mant = mant;
        div_decomposed_float(&result_sign, &result_exp, &result_mant, other.sign, other.exp, other.mant);
        quantize_float(&result_exp, &result_mant, exp_bits, mant_bits);
        float result_value;
        construct_float(result_sign, result_exp, result_mant, &result_value);
        return FloatX(result_value, exp_bits, mant_bits);
    }

    FloatX& operator+=(const FloatX& other) {
        int result_sign = sign, result_exp = exp, result_mant = mant;
        add_decomposed_float(&result_sign, &result_exp, &result_mant, other.sign, other.exp, other.mant);
        quantize_float(&result_exp, &result_mant, exp_bits, mant_bits);
        float result_value;
        construct_float(result_sign, result_exp, result_mant, &result_value);
        value = result_value;
        return *this;
    }

    friend ostream& operator<<(ostream& out, const FloatX& m)
    {
        out << m.value;
        return out;
    }

};

void testFLoat(){
    // Test constructor
    Float f1(3.14f);
    assert(std::abs(f1.value - 3.14f) < 1e-6);

    // Test addition
    Float f2(1.5f);
    Float f3(2.5f);
    Float f4 = f2 + f3;
    assert(std::abs(f4.value - 4.0f) < 1e-6);

    // Test subtraction
    Float f5(5.0f);
    Float f6(3.0f);
    Float f7 = f5 - f6;
    assert(std::abs(f7.value - 2.0f) < 1e-6);

    // Test multiplication
    Float f8(2.0f);
    Float f9(3.0f);
    Float f10 = f8 * f9;
    assert(std::abs(f10.value - 6.0f) < 1e-6);

    // Test division
    Float f11(6.0f);
    Float f12(2.0f);
    Float f13 = f11 / f12;
    assert(std::abs(f13.value - 3.0f) < 1e-6);

    // Test addition assignment
    Float f14(1.5f);
    Float f15(2.5f);
    f14 += f15;
    assert(std::abs(f14.value - 4.0f) < 1e-6);

    // Test negative number
    Float f101(-3.14f);
    assert(std::abs(f101.value + 3.14f) < 1e-6);

    // Test zero
    Float f102(0.0f);
    assert(std::abs(f102.value - 0.0f) < 1e-6);

    // Test addition with zero
    Float f103 = f101 + f102;
    assert(std::abs(f103.value + 3.14f) < 1e-6);

    // Test subtraction with zero
    Float f104 = f101 - f102;
    assert(std::abs(f104.value + 3.14f) < 1e-6);

    // Test multiplication with zero
    Float f105 = f101 * f102;
    assert(std::abs(f105.value - 0.0f) < 1e-6);

    // Test division by zero
    Float f106 = f101 / f102;
    assert(std::isinf(f106.value));

    // Test division of zero
    Float f107 = f102 / f101;
    assert(std::abs(f107.value - 0.0f) < 1e-6);

    // cout the Test Pass
    cout<<"Test Pass!"<<endl;

}

void TestLowPrecisionFloat(){
    float a, b, result, re_a, re_b;
    int exp_bits, mant_bits;
    cin>>exp_bits>>mant_bits;
    char op;
    int sign1, exp1, mant1, sign2, exp2, mant2;
    cin>>a>>b>>op;
    FloatX A(a,exp_bits,mant_bits), B(b,exp_bits,mant_bits), C(0,exp_bits,mant_bits);
    // cin>>a>>b;
    parse_float(a, &sign1, &exp1, &mant1);
    quantize_float(&exp1, &mant1, exp_bits, mant_bits);
    parse_float(b, &sign2, &exp2, &mant2);
    quantize_float(&exp2, &mant2, exp_bits, mant_bits);

    construct_float(sign1, exp1, mant1, &re_a);
    construct_float(sign2, exp2, mant2, &re_b);
    cout<<re_a<<endl<<re_b<<endl;
    cout<<A<<endl<<B<<endl;
    // cout<<sign1<<" "<<exp1<<" "<<mant1<<endl;
    // cout<<sign2<<" "<<exp2<<" "<<mant2<<endl;
    switch (op)
    {
    case '+':
        add_decomposed_float(&sign1, &exp1, &mant1, sign2, exp2, mant2);
        C+=A+B;
        // 计算两个浮点数的和
        break;
    case '-':
        add_decomposed_float(&sign1, &exp1, &mant1, -sign2, exp2, mant2);
        C+=A-B;
        // 计算两个浮点数的差
        break;
    case '*':
        mul_decomposed_float(&sign1, &exp1, &mant1, sign2, exp2, mant2);
        C+=A*B;
        // 计算两个浮点数的积
        break;
    case '/':
        div_decomposed_float(&sign1, &exp1, &mant1, sign2, exp2, mant2);
        C+=A/B;
        // 计算两个浮点数的商
        break;
    default:
        break;
    }
    // construct float
    // cout<<sign1<<" "<<exp1<<" "<<mant1<<endl;
    quantize_float(&exp1, &mant1, exp_bits, mant_bits);
    construct_float(sign1, exp1, mant1, &result);
    cout<<result<<endl;
    cout<<C<<endl;
    // return result;
}

template<typename T>
void gemm(const T* A, const T* B, T* C, int m, int n, int k) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int p = 0; p < k; ++p) {
                C[i*n+j] += A[i*k+p] * B[p*n+j];
                // T tmp = A[i*k+p] * B[p*n+j];
                // C[i*n+j] =  C[i*n+j]+tmp;
            }
        }
    }
}

int test_Float_gemm() {
    std::mt19937 generator = std::mt19937(0);
    std::uniform_real_distribution<float> fdist = std::uniform_real_distribution<float>(0.0, 1.0);
    int n = 100;
    int exp_bits=2, mant_bits=4;
    cin>>n >> exp_bits >> mant_bits;
    // std::vector<std::vector<float>> A(n, std::vector<float>(n, 1.0f));
    // std::vector<std::vector<float>> B(n, std::vector<float>(n, 1.0f));
    // std::vector<std::vector<float>> C(n, std::vector<float>(n, 0.0f));
    float A[n*n], B[n*n], C[n*n];
    FloatX A_float[n*n], B_float[n*n], C_float[n*n];

    for (int i = 0; i < n*n; ++i) {
        A[i] = fdist(generator);
        B[i] = A[i];
        C[i] = 0.0f;
        A_float[i] = FloatX(A[i], exp_bits, mant_bits);
        B_float[i] = FloatX(A[i], exp_bits, mant_bits);
        C_float[i] = FloatX(0.0f, exp_bits, mant_bits);
        cout<<exp_bits<<" "<<mant_bits<<" "<<A[i]<<" "<<A_float[i]<<endl;
    }

    auto start = std::chrono::high_resolution_clock::now();
    gemm<float>(A, B, C, n, n, n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    // std::cout << "Time to perform GEMM with float: " << diff.count() << " s\n";
    int rows = n;
    int cols = n;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << C[i * cols + j];
            if (j != cols - 1) {
                cout << " ";
            }
        }
        // if (i != rows - 1) 
            cout << std::endl;
    }
    cout << std::endl;
    start = std::chrono::high_resolution_clock::now();
    gemm<FloatX>(A_float, B_float, C_float, n, n, n);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    // std::cout << "Time to perform GEMM with Float: " << diff.count() << " s\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << C_float[i * cols + j];
            if (j != cols - 1) {
                cout << " ";
            }
        }
        // if (i != rows - 1) 
            cout << std::endl;
    }
    // cout << std::endl;
    return 0;
}


int main() {
    
    // sort_input_int();
    // sort_float();
    // compute_float_with_int();
    // testFLoat();
    // TestLowPrecisionFloat();
    test_Float_gemm();

    return 0;
}