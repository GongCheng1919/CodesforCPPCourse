#include <iostream>
using namespace std;

void func(){
    cout<<"hello world!"<<endl;
}

class graphelem
{ // �Զ����� graphelem������Ϊ����ͼԪ��Ļ���
protected:
    int color; // ��ɫ color
public:
    graphelem()
    {
        color = 0;
    }
    void draw()
    {
        cout << "draw graphelem" << endl;
    }; // �����к���һ���麯��
};

class line : public graphelem
{ // �Զ����� line��Ϊ���� graphelem �������� 
    public: // �麯�� draw ���𻭳���line��
    void draw() { cout << "draw line" << endl; }; 
};
class circle : public graphelem
{ // �Զ����� circle��Ϊ���� graphelem ��������
    public: // �麯�� draw�����𻭳���circle�� 
    void draw(){ cout << "draw circle" << endl; }; 
};
class triangle : public graphelem
{ // �� triangle��Ϊ���� graphelem ��������
    public: // �麯�� draw ���𻭳���triangle��
    void draw(){ cout << "draw triangle" << endl; }; 
};

class triangle2 : public triangle
{ // �� triangle��Ϊ���� graphelem ��������
    public: // �麯�� draw ���𻭳���triangle��
    void draw(){ cout << "draw triangle2" << endl; }; 
};

int main()
{
    // line ln1; circle cir1; triangle tri1;
    // ln1.draw(); cir1.draw(); tri1.draw();
    graphelem *p[4]; // ����һ��ָ�����飬����Ԫ��Ϊ���� graphelem ��ָ��
    p[0] = new line(); // ָ������ĵ�һ��Ԫ��ָ�������� line �Ķ���
    p[1] = new circle(); // ָ������ĵڶ���Ԫ��ָ�������� circle �Ķ���
    p[2] = new triangle(); // ָ������ĵ�����Ԫ��ָ�������� triangle �Ķ���
    p[3] = new triangle2(); // ָ������ĵ�����Ԫ��ָ�������� triangle �Ķ���
    printf("address of func is %p\n",&func);
    for (int i = 0; i < 4; i++){
        p[i]->draw(); // ����ָ�������и���Ԫ�ص� draw() ����
        printf("%p, %p",p[i],&(p[i]->draw));
        printf(", p[%d]->graphelem::draw��ַ:%p", i, &(p[i]->graphelem::draw));
        printf(", p[%d]->draw��ַ:%p\n", i, &(p[i]->draw));
    }
    // ((triangle*)p[3])->triangle::draw();
    return 0;
}


