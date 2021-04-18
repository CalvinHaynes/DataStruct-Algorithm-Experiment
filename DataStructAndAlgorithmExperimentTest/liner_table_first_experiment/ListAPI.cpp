#include "ListStruct.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

char finalSymbol;//运算后最终决定的数字正负符号

/*
* Comments:初始化List
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
* Comments:创建双向循环链表
* Param L :链表结构体指针引用
* Param int n :结点数
* @Return void
*/
void CreateList(List& L, int& n) {
	int x;
	char d;
	List p = L;

	cin >> x;

	//循环输入数值（x），直到缓冲区中检测到回车换行符\n，结束循环
	while ((d = getchar()) != '\n') {
		List q = new Node;
		n++;
		
		//双向循环链表信息存入
		q->data = x;
		q->pre = p;
		q->next = L;
		p->next = q;
		L->pre = q;
		p = q;
		//cin >> d;
		cin >> x;
	}
	//将回车前最后一次输入的x值存入链表结点中
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
* Comments:链表头部插入数值e
* Param L :链表结构体指针引用
* Param int e:头部插入的数值
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
* Comments:链表尾部插入数值e
* Param L :链表结构体指针引用
* Param int e:尾部插入的数值
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
* Comments:绝对值比较L1和L2链表中存储的数的大小
* Param L1,L2:链表结构体指针引用
* Param n1,n2:两链表中结点个数引用
* @Return int 
*		- 返回1：L1 > L2
*		- 返回0：L1 = L2
*		- 返回-1：L1 < L2
*/
int CompareList(List& L1, List& L2, int& n1, int& n2) {
	
	//先比较结点个数，避免不必要的比较计算
	if (n1 > n2)
		return 1;
	else if (n1 < n2)
		return -1;
	else {
		List p, q;

		p = L1->next;
		q = L2->next;
		
		//只要数据域相等，就一直自增遍历链表，直到遍历完毕(p != L1 && q != L2)
		while (p != L1 && q != L2 && p->data == q->data) {
			p = p->next;
			q = q->next;
		}
		
		//数据域比较
		if (p->data > q->data)
			return 1;
		else if (p == L1)
			return 0;
		else
			return -1;
	}
}

/*
* Comments:两链表中存储数值减法算法实现
* Param L1,L2,L3:链表结构体指针引用
* @Return void
*/
void SubList(List& L1, List& L2, List& L3) {
	List p = new Node;
	List q = new Node;
	int e;
	int borrow = 0;//借位

	p = L1->pre;
	q = L2->pre;

	//L1，L2长度相等 
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

	//L1比L2长 
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

	//L2比L1长
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
* Comments:两链表中存储数值加法算法实现，L3 = L1 + L2
* Param L1,L2,L3:链表结构体指针引用
* @Return void
*/
void AddList(List& L1, List& L2, List& L3) {
	List p = new Node;
	List q = new Node;
	
	int e;
	int carry = 0;//进位

	p = L1->pre;
	q = L2->pre;

	//L1，L2长度相等 
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

	//L1比L2长 
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

	//L2比L1长 
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
* Comments:运算方法判断选择 
* Param A,B,C:三个循环链表引用
* Param n1,n2:A,B循环链表的结点数
* Param sym1,sym2:A,B中存储数字的正负号
* Tips：用户键盘输入的第一个字符+或-被条件判断吞掉，实际上计算时是利用其绝对值计算，再利用finalSymbol存储最终结果数字的正负号
* @Return void
*/
void SelectMethod(List& A, List& B, List& C, int& n1, int& n2, char& sym1, char& sym2) {  
	char symbol;
	cin >> symbol;//从缓冲区中提取用户输入的加或减运算符
	
	//先比较下A，B链表中存储数字的绝对值大小
	int num = CompareList(A, B, n1, n2);

	if (symbol == '+') {//加法
		if (sym1 == '+' && sym2 == '+') {
			//两个正数相加
			finalSymbol = '+';
			AddList(A, B, C);
		}
		else if (sym1 == '+' && sym2 == '-') {
			if (num == 1) {//A>B
			//绝对值大的正数加上绝对值小的负数
				finalSymbol = '+';
				SubList(A, B, C);//C = A - B
			}
			else if (num == -1) {//B>A
		   //绝对值小的正数加上绝对值大的负数
				finalSymbol = '-';
				SubList(B, A, C);//C = B - A
			}
			else SubList(A, B, C);//C = A - B
		}
		else if (sym1 == '-' && sym2 == '+') {
			if (num == 1) { //A>B
			//绝对值大的负数加上绝对值小的正数
				finalSymbol = '-';
				SubList(A, B, C);
			}
			else if (num == -1) {//B>A
			//绝对值小的负数加上绝对值大的正数
				finalSymbol = '+';
				SubList(B, A, C);
			}
			else SubList(A, B, C);
		}
		else if (sym1 == '-' && sym2 == '-') {//两负数相加
			
			finalSymbol = '-';
			AddList(A, B, C);
		}
	}
	else if (symbol == '-') {//减法
		if (sym1 == '+' && sym2 == '+') {
			if (num == 1) {         //A>B
			//绝对值大的正数减去绝对值小的正数
				finalSymbol = '+';
				SubList(A, B, C);
			}
			else if (num == -1) {    //B>A
			//绝对值小的正数减去绝对值大的正数
				finalSymbol = '-';
				SubList(B, A, C);
			}
			else SubList(A, B, C);
		}
		else if (sym1 == '+' && sym2 == '-') {
			//正数减去负数
			finalSymbol = '+';
			AddList(A, B, C);
		}
		else if (sym1 == '-' && sym2 == '+') {
			//负数减去正数
			finalSymbol = '-';
			AddList(A, B, C);
		}
		else if (sym1 == '-' && sym2 == '-') {
			if (num == 1) {      //A>B
			//绝对值大的负数减去绝对值小的负数
				finalSymbol = '-';
				SubList(A, B, C);
			}
			else if (num == -1) {    //B>A
			//绝对值小的负数减去绝对值大的负数
				finalSymbol = '+';
				SubList(B, A, C);
			}
			else SubList(A, B, C);
		}
	}
	else {
		cout << "输入错误，请重新输入:" << endl;
		SelectMethod(A, B, C, n1, n2, sym1, sym2);
	}
}

/*
* Comments:输出链表中存储的数值
* Param L :链表结构体指针引用
* @Return void
*/
void ShowList(List& L) {
	List p;
	if (L == NULL) 
		return;

	p = L->next;

	while (p->data == 0 && p->next != L) {  //结果中遇到数据为0的结点直接略过不输出，直到有数值的结点或尾节点 
		p = p->next;
	}

	if (p->data == 0 && p->next == L) {  //如果结果链表中数据全为0 
		cout << "0";
		return;
	}

	cout << p->data;  //第一个数作直接输出，无需在前添0； 
	p = p->next;
	
	if (p == L) 
		return;  //如果p此时指向最后一个数 ，p->next为null，结束输出。 
	else
		cout << ",";

	while (1) {       //循环输出剩余结点内容。 
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