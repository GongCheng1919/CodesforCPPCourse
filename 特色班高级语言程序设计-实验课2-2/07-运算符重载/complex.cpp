#include<iostream>
#include<cmath>
using namespace std;
class Complex;
Complex operator + (const Complex & c1, const Complex & c2);
Complex operator - (const Complex& c1, const Complex& c2);
class Complex
{
	friend Complex operator + (const Complex & c1, const Complex & c2);
	friend Complex operator - (const Complex& c1, const Complex& c2);
	int shibu;
	int xubu;
public:
	Complex(int a, int b)
	{
		shibu = a;
		xubu = b;
	}
	Complex()
	{};
	Complex& operator=(const Complex& c1)
	{
		this->shibu = c1.shibu;
		this->xubu = c1.xubu;
		return *this;
	}
	void display(){
		if(xubu>=0)
		cout << shibu << " + " << xubu << "i";
		else if(xubu<0)
			cout << shibu << " - " << fabs(xubu) << "i";
	}
};
int main()
{
	int x,y,c,d;
	cin >> x >> y;
	cin >> c >> d;
	Complex a1(x,y);
	Complex a2(c,d);
	Complex a3,a4;
	a3 = a1 + a2;
	a4 = a1 - a2;
	a3.display();
	cout << endl;
	a4.display();
	return 0;
}
Complex operator + (const Complex& c1, const Complex& c2)
{
	Complex c3;
	c3.shibu = c1.shibu + c2.shibu;
	c3.xubu = c1.xubu + c2.xubu;
	return c3;
}
Complex operator - (const Complex& c1, const Complex& c2)
{
	Complex c3;
	c3.shibu = c1.shibu - c2.shibu;
	c3.xubu = c1.xubu - c2.xubu;
	return c3;
}
