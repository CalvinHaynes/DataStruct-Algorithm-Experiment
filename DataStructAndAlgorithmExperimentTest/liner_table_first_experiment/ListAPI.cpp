#include "ListStruct.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

char finalSymbol;//��������վ�����������������

/*
* Comments:��ʼ��List
* @Return void
*/
void InitList(List& L) {

	L = new Node;
	if (L) {
		L->pre  = L;
		L->next = L;
	}
	else {
		exit(0);
	}
}

/*
* Comments:����˫��ѭ������
* Param L :����ṹ��ָ������
* Param int n :�����
* @Return void
*/
void CreateList(List& L, int& n) {
	int x;
	char d;
	List p = L;

	cin >> x;

	//ѭ��������ֵ��x����ֱ���������м�⵽�س����з�\n������ѭ��
	while ((d = getchar()) != '\n') {
		List q = new Node;
		n++;
		
		//˫��ѭ��������Ϣ����
		q->data = x;
		q->pre = p;
		q->next = L;
		p->next = q;
		L->pre = q;
		p = q;
		//cin >> d;
		cin >> x;
	}
	//���س�ǰ���һ�������xֵ������������
	List q = new Node;
	n++;
	q->data = x;
	q->pre = p;
	q->next = L;
	p->next = q;
	L->pre = q;
	p = q;
}

/*
* Comments:����ͷ��������ֵe
* Param L :����ṹ��ָ������
* Param int e:ͷ���������ֵ
* @Return void
*/
void ListInsertTop(List& L, int e) {
	List s = new Node;
	s->data = e;
	s->next = L->next;
	s->pre = L;
	L->next->pre = s;
	L->next = s;
}

/*
* Comments:����β��������ֵe
* Param L :����ṹ��ָ������
* Param int e:β���������ֵ
* @Return void
*/
void ListInsertBelow(List& L, int e) {
	List s = new Node;
	s->data = e;
	s->next = L;
	s->pre = L->pre;
	L->pre->next = s;
	L->pre = s;
}

/*
* Comments:����ֵ�Ƚ�L1��L2�����д洢�����Ĵ�С
* Param L1,L2:����ṹ��ָ������
* Param n1,n2:�������н���������
* @Return int 
*		- ����1��L1 > L2
*		- ����0��L1 = L2
*		- ����-1��L1 < L2
*/
int CompareList(List& L1, List& L2, int& n1, int& n2) {
	
	//�ȱȽϽ����������ⲻ��Ҫ�ıȽϼ���
	if (n1 > n2)
		return 1;
	else if (n1 < n2)
		return -1;
	else {
		List p, q;

		p = L1->next;
		q = L2->next;
		
		//ֻҪ��������ȣ���һֱ������������ֱ���������(p != L1 && q != L2)
		while (p != L1 && q != L2 && p->data == q->data) {
			p = p->next;
			q = q->next;
		}
		
		//������Ƚ�
		if (p->data > q->data)
			return 1;
		else if (p == L1)
			return 0;
		else
			return -1;
	}
}

/*
* Comments:�������д洢��ֵ�����㷨ʵ��
* Param L1,L2,L3:����ṹ��ָ������
* @Return void
*/
void SubList(List& L1, List& L2, List& L3) {
	List p = new Node;
	List q = new Node;
	int e;
	int borrow = 0;//��λ

	p = L1->pre;
	q = L2->pre;

	//L1��L2������� 
	while (p != L1 && q != L2) { 
		e = p->data - q->data - borrow;
		if (p->data < q->data) {
			e = e + 10000;
			borrow = 1;
		}
		else {
			borrow = 0;
		}
		ListInsertTop(L3, e);
		p = p->pre;
		q = q->pre;
	}

	//L1��L2�� 
	while (p != L1) { 
		e = p->data - borrow;
		if (e < 0) {
			e = e + 10000;
			borrow = 1;
		}
		else borrow = 0;
		ListInsertTop(L3, e);
		p = p->pre;
	}

	//L2��L1��
	while (q != L2) {
		e = q->data - borrow;
		if (e < 0) {
			e = e + 10000;
			borrow = 1;
		}
		else borrow = 0;
		ListInsertTop(L3, e);
		q = q->pre;
	}

}

/*
* Comments:�������д洢��ֵ�ӷ��㷨ʵ�֣�L3 = L1 + L2
* Param L1,L2,L3:����ṹ��ָ������
* @Return void
*/
void AddList(List& L1, List& L2, List& L3) {
	List p = new Node;
	List q = new Node;
	
	int e;
	int carry = 0;//��λ

	p = L1->pre;
	q = L2->pre;

	//L1��L2������� 
	while (p != L1 && q != L2) { 
		e = p->data + q->data + carry;
		if (e >= 10000) {
			carry = 1;
			e = e - 10000;
		}
		else 
			carry = 0;

		ListInsertTop(L3, e);
		p = p->pre;
		q = q->pre;
	}

	//L1��L2�� 
	while (p != L1) { 
		e = p->data + carry;
		if (e >= 10000) {
			carry = 1;
			e = e - 10000;
		}
		else carry = 0;
		ListInsertTop(L3, e);
		p = p->pre;
	}

	//L2��L1�� 
	while (q != L2) { 
		e = q->data + carry;
		if (e >= 10000) {
			carry = 1;
			e = e - 10000;
		}
		else carry = 0;
		ListInsertTop(L3, e);
		q = q->pre;
	}
	if (carry == 1) ListInsertTop(L3, 1);
}

/*
* Comments:���㷽���ж�ѡ�� 
* Param A,B,C:����ѭ����������
* Param n1,n2:A,Bѭ������Ľ����
* Param sym1,sym2:A,B�д洢���ֵ�������
* Tips���û���������ĵ�һ���ַ�+��-�������ж��̵���ʵ���ϼ���ʱ�����������ֵ���㣬������finalSymbol�洢���ս�����ֵ�������
* @Return void
*/
void SelectMethod(List& A, List& B, List& C, int& n1, int& n2, char& sym1, char& sym2) {  
	char symbol;
	cin >> symbol;//�ӻ���������ȡ�û�����ļӻ�������
	
	//�ȱȽ���A��B�����д洢���ֵľ���ֵ��С
	int num = CompareList(A, B, n1, n2);

	if (symbol == '+') {//�ӷ�
		if (sym1 == '+' && sym2 == '+') {
			//�����������
			finalSymbol = '+';
			AddList(A, B, C);
		}
		else if (sym1 == '+' && sym2 == '-') {
			if (num == 1) {//A>B
			//����ֵ����������Ͼ���ֵС�ĸ���
				finalSymbol = '+';
				SubList(A, B, C);//C = A - B
			}
			else if (num == -1) {//B>A
		   //����ֵС���������Ͼ���ֵ��ĸ���
				finalSymbol = '-';
				SubList(B, A, C);//C = B - A
			}
			else SubList(A, B, C);//C = A - B
		}
		else if (sym1 == '-' && sym2 == '+') {
			if (num == 1) { //A>B
			//����ֵ��ĸ������Ͼ���ֵС������
				finalSymbol = '-';
				SubList(A, B, C);
			}
			else if (num == -1) {//B>A
			//����ֵС�ĸ������Ͼ���ֵ�������
				finalSymbol = '+';
				SubList(B, A, C);
			}
			else SubList(A, B, C);
		}
		else if (sym1 == '-' && sym2 == '-') {//���������
			
			finalSymbol = '-';
			AddList(A, B, C);
		}
	}
	else if (symbol == '-') {//����
		if (sym1 == '+' && sym2 == '+') {
			if (num == 1) {         //A>B
			//����ֵ���������ȥ����ֵС������
				finalSymbol = '+';
				SubList(A, B, C);
			}
			else if (num == -1) {    //B>A
			//����ֵС��������ȥ����ֵ�������
				finalSymbol = '-';
				SubList(B, A, C);
			}
			else SubList(A, B, C);
		}
		else if (sym1 == '+' && sym2 == '-') {
			//������ȥ����
			finalSymbol = '+';
			AddList(A, B, C);
		}
		else if (sym1 == '-' && sym2 == '+') {
			//������ȥ����
			finalSymbol = '-';
			AddList(A, B, C);
		}
		else if (sym1 == '-' && sym2 == '-') {
			if (num == 1) {      //A>B
			//����ֵ��ĸ�����ȥ����ֵС�ĸ���
				finalSymbol = '-';
				SubList(A, B, C);
			}
			else if (num == -1) {    //B>A
			//����ֵС�ĸ�����ȥ����ֵ��ĸ���
				finalSymbol = '+';
				SubList(B, A, C);
			}
			else SubList(A, B, C);
		}
	}
	else {
		cout << "�����������������:" << endl;
		SelectMethod(A, B, C, n1, n2, sym1, sym2);
	}
}

/*
* Comments:��������д洢����ֵ
* Param L :����ṹ��ָ������
* @Return void
*/
void ShowList(List& L) {
	List p;
	if (L == NULL) 
		return;

	p = L->next;

	while (p->data == 0 && p->next != L) {  //�������������Ϊ0�Ľ��ֱ���Թ��������ֱ������ֵ�Ľ���β�ڵ� 
		p = p->next;
	}

	if (p->data == 0 && p->next == L) {  //����������������ȫΪ0 
		cout << "0";
		return;
	}

	cout << p->data;  //��һ������ֱ�������������ǰ��0�� 
	p = p->next;
	
	if (p == L) 
		return;  //���p��ʱָ�����һ���� ��p->nextΪnull����������� 
	else
		cout << ",";

	while (1) {       //ѭ�����ʣ�������ݡ� 
		if (p->data == 0)
			cout << "0000";
		else if (p->data < 10)
			cout << "000" << p->data;
		else if (p->data < 100)
			cout << "00" << p->data;
		else if (p->data < 1000)
			cout << "0" << p->data;
		else cout << p->data;
		
		p = p->next;

		if (p == L) 
			break;
		cout << ",";
	}
	cout << endl;
}