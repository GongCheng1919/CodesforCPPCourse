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

void parse_float(const float f, int* sign,int* exp,int* mant){
    // 解析浮点数为三个整型，分别保存其符号位，指数位和尾数位（尾数位记得包含隐藏位1）
    *sign = (f>0?1:-1);
    unsigned int u = *(unsigned int*)&f;
    *exp = ((u>>23) & 0xff);
    *mant = (u & 0x7fffff)|0x800000;
}

void construct_float(const int sign,const int exp,const int mant, float* f){
    // 将整型的符号位，指数位和尾数位转换为浮点数，记得尾数位的隐藏位1
    unsigned int u = (sign>0?0:0x80000000) | (exp<<23) | (mant&0x7fffff);
    *f = *(float*)&u;
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
    *dst_mant += src_mant;
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
    // 4、溢出判断
    if (*dst_exp >= 255) {
        // Overflow, return infinity
        *dst_exp = 255;
        *dst_mant = 0;
    }
}

void mul_decomposed_float(int* dst_sign, int* dst_exp, int* dst_mant, int src_sign, int src_exp, int src_mant){
    if ((*dst_exp==0 && *dst_mant==0x800000) ||src_exp==0 && src_mant==0x800000){
        // 浮点数是0
        // cout<<"Test zero multiplication"<<endl;
        *dst_sign = src_sign;
        *dst_exp = 0;
        *dst_mant = 0x800000;
        return;
    }

    *dst_sign = *dst_sign * src_sign;
    // 1、计算指数
    *dst_exp += src_exp - 127 - 23; // 注意尾数位应该是1.X*2^23 * 1.X*2^23 = XX, 所以对这个乘法的结果，还要-23个指数
    // 2、计算尾数
    long long tmp =((long long)(*dst_mant)) * ((long long)(src_mant)); 

    // 3、规格化
    // 找到最高位1的位置
    int pos = 0;
    long long tmp1 = 1;
    for (int i = 0; i < 64; i++) {
        if (tmp & (tmp1 << i)) {
            pos = i;
        }
    }
    if (pos > 23) {
        tmp = (tmp >> (pos - 23));
        *dst_exp += pos - 23;
    } else {
        tmp = (tmp << (23 - pos));
        *dst_exp -= 23 - pos;
    }
    *dst_mant = (int)tmp;

    // 4、溢出判断
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
    if (pos > 23) {
        tmp = (tmp >> (pos - 23));
        *dst_exp += pos - 23;
    } else {
        tmp = (tmp << (23 - pos));
        *dst_exp -= 23 - pos;
    }
    *dst_mant = (int)tmp;
    // 4、溢出判断
    if (*dst_exp >= 255) {
        // Overflow, return infinity
        *dst_exp = 255;
        *dst_mant = 0;
    }
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

int main(){
    testFLoat();
    return 0;
}