#include<iostream>
#include<stdlib.h>
#include"ListStruct.h"
using namespace std;

extern char finalSymbol;//最后的符号

int main() {
	int n1 = 0, n2 = 0;

	List A, B, C; //定义链表A,B,C,C中存储A,B相加的结果

	InitList(A);
	InitList(B);
	InitList(C);

	cout << "********************************************************************" << endl;
	cout << "*                      100位以内的长整数加减法运算                      *" << endl;
	cout << "********************************************************************" << endl;
	cout << endl;

	cout << "实验要求：" << endl;
	cout << "1、输入输出要求：每四位一组，组间用逗号分隔。" << endl;
	cout << "2、加和减分别用不同的程序实现。" << endl;
	cout << "3、程序应考虑输入数据的符号。" << endl;
	cout << endl;

	cout << "请输入第一个带符号位的整数(如-1234,5678或+1234,5678)：" << endl;
	//输入第一个长整数（不超过100位）
	char symbol_1;
	while (1) {
		cin >> symbol_1;
		if (symbol_1 == '+' || symbol_1 == '-')
			break;
		cout << "符号输入错误或未输入符号,请重输第一个整数!" << endl;
		fflush(stdin);//清空输入缓存
	}
	CreateList(A, n1);


	cout << "请输入第二个带符号位的整数(如-1234,5678或+1234,5678)：" << endl;
	//输入第二个长整数（不超过100位）
	char symbol_2;
	while (1) {
		cin >> symbol_2;
		if (symbol_2 == '+' || symbol_2 == '-')
			break;
		cout << "符号输入错误或未输入符号,请重输第一个整数!" << endl;
		fflush(stdin);//清空输入缓存
	}
	CreateList(B, n2);

	cout << "选择加法请输入+，选择减法请输入-（如+）：" << endl;
	SelectMethod(A, B, C, n1, n2, symbol_1, symbol_2);

	//计算结果
	cout << "结果为：" << endl;
	if (finalSymbol == '-') cout << finalSymbol;
	ShowList(C);

}