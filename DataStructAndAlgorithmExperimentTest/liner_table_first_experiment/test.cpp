#include<iostream>
#include<stdlib.h>
#include"ListStruct.h"
using namespace std;

extern char finalSymbol;//���ķ���

int main() {
	int n1 = 0, n2 = 0;

	List A, B, C; //��������A,B,C,C�д洢A,B��ӵĽ��

	InitList(A);
	InitList(B);
	InitList(C);

	cout << "********************************************************************" << endl;
	cout << "*                      100λ���ڵĳ������Ӽ�������                      *" << endl;
	cout << "********************************************************************" << endl;
	cout << endl;

	cout << "ʵ��Ҫ��" << endl;
	cout << "1���������Ҫ��ÿ��λһ�飬����ö��ŷָ���" << endl;
	cout << "2���Ӻͼ��ֱ��ò�ͬ�ĳ���ʵ�֡�" << endl;
	cout << "3������Ӧ�����������ݵķ��š�" << endl;
	cout << endl;

	cout << "�������һ��������λ������(��-1234,5678��+1234,5678)��" << endl;
	//�����һ����������������100λ��
	char symbol_1;
	while (1) {
		cin >> symbol_1;
		if (symbol_1 == '+' || symbol_1 == '-')
			break;
		cout << "������������δ�������,�������һ������!" << endl;
		fflush(stdin);//������뻺��
	}
	CreateList(A, n1);


	cout << "������ڶ���������λ������(��-1234,5678��+1234,5678)��" << endl;
	//����ڶ�����������������100λ��
	char symbol_2;
	while (1) {
		cin >> symbol_2;
		if (symbol_2 == '+' || symbol_2 == '-')
			break;
		cout << "������������δ�������,�������һ������!" << endl;
		fflush(stdin);//������뻺��
	}
	CreateList(B, n2);

	cout << "ѡ��ӷ�������+��ѡ�����������-����+����" << endl;
	SelectMethod(A, B, C, n1, n2, symbol_1, symbol_2);

	//������
	cout << "���Ϊ��" << endl;
	if (finalSymbol == '-') cout << finalSymbol;
	ShowList(C);

}