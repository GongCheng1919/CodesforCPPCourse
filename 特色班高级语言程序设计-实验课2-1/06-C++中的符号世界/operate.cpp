#include<iostream>
#include<cmath>
#include<string>
using namespace std;
int judgeoperator(string op);
int judgeoperator(string op)
{
	if (op == "[]" || op == "()" || op == "->") return 1;
	if (op == "~" || op == "++" || op == "--" || op == "!" || op == "sizeof") return 2;
	if (op == "/" || op == "*" || op == "%") return 3;
	if (op == "+" || op == "-")return 4;
	if (op == "<<" || op == ">>") return 5;
	if (op == ">" || op == ">=" || op == "<" || op == "<=") return 6;
	if (op == "==" || op == "!=") return 7;
	if (op == "&") return 8;
	if (op == "^") return 9;
	if (op == "|") return 10;
	if (op == "&&") return 11;
	if (op == "||")return 12;
	if (op == "?:")return 13;
	if (op == "=" || op == "/=" || op == "*=" || op == "%=" || op == "+=" || op == "-=" || op == "<<=" || op == ">>=" || op == "&=" || op == "^=" || op == "|=") return 14;
}
int main()
{
	string op1, op2;
	cin >> op1 >> op2;
	if (judgeoperator(op1) <= judgeoperator(op2)) cout << op1 << " " << op2;
	else cout << op2 << " " << op1;
	
	return 0;
}
