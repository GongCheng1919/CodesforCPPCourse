// signs_and_operators.h
#include <iostream> 
using namespace std;

void test_equal_sign(){
    int a=1,b=2,c,d;
    d=(c=a+b);
    cout<<"c="<<c<<", d="<<d<<endl;
}

void test_int_div(){
    int a = 3, b=2;
    float y = 2.0;
    cout<<"a/b="<<a/b<<", a/y="<<a/y<<endl;
}

void test_int_mod(){
    int a = 3, b=2;
    cout<<"a - b *(a / b)="<<(a-b*(a / b))<<"\na % b="<<a % b<<endl;
}

class TypeA{
public: float a=1;
    TypeA(int a){this->a=a;}
};

void test_relation_op(){
    bool a = (2>=2.5); 
    bool b = (int(2)>=int(2.5));
    bool c = 7;
    int d = true;
    // TypeA e(1);
    // bool f = (2>e));
    cout<<"a = "<<a 
        <<", b = "<<b 
        <<", c = "<<c 
        <<", d = "<<d 
        <<endl;
}

void test_logic_op(){
    int a = 2, b = 5;
    cout <<"!a = "<< !a << ", !(b/a-a) = " << !(b / a - a)<< endl;
    cout <<"a&&b = "<< (a && b) << ", (a&&(b/a-a)) = " << (a && (b / a - a)) << endl;
    cout <<"a||b = "<< (a || b )<< ", (a||(b/a-a)) = " << (a || (b / - a) )<< endl;
}

template<class T>
void display_var_bits(T var){
    // 获取一个类型的长度
    int Bs = sizeof(T);
    // 强制转换一块内存地址的解码方式
    unsigned int* var_ptr = (unsigned int*)((void*)(&var));
    // 设置一个mask掩码值来每一次捕获低8位的二进制：
    // 0x00000000 00000000 00000000 11111111 = 
    // 0x11111111 = 
    // 255 = 
    // (256-1) = 
    // ((1<<8)-1)
    unsigned char filter1 = 255;
    // 设置另外一个掩码值来每一次捕获低1位的二进制：0x00000001
    unsigned char filter = 1;
    // 取内容运算获得var_ptr指向的地址，按照int类型解码获得的值
    unsigned int tmp_var = *var_ptr, b;
    cout<<"bit string of "<<var<<" is: ";
    // 按照8位一个字节，依次打印每一个位的值（1或者0）
    char* bit_str = new char[Bs*8+1];
    for (int i=0;i<Bs*8;i++){
        b = tmp_var & filter;
        tmp_var = tmp_var>>1;
        bit_str[Bs*8-i-1] = b?'1':'0';
        // cout<<b;
    }
    bit_str[Bs*8]='\0';
    for (int i=0;i<Bs*8;i++){
        if (i%8==0 && i!=0) cout<<"-";
        cout<<bit_str[i];
    }
    cout<<endl;
}

void test_bitlogic_op(){
    unsigned int var = 32;
    display_var_bits(var);
    float f = 3.141592;
    display_var_bits(f);
    int n = -7;
    display_var_bits(n);
    double d = -7.5e34;
    display_var_bits(d);
    int i = 7;
    display_var_bits(i);
    bool b = 7;
    display_var_bits(b);    
    cout<<i<<"&"<<b<<"="<<(i&b)<<endl;
    display_var_bits((i&b));
}
