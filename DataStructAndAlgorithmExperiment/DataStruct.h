#ifndef _DATA_STRUCT__
#define _DATA_STRUCT__

/*
* ����˫��ѭ����������ݽṹ�洢���ṩ���������API
*/

//˫��ѭ������ṹ��
typedef struct ListNode {		
	int data;
	struct ListNode* pre;
	struct ListNode* next;
}Node, * List;



/***************API�б�******************/
void InitList(List& L);
void CreateList(List& L, int& n);
void ListInsertTop(List& L, int e);
void ListInsertBelow(List& L, int e);
int CompareList(List& L1, List& L2, int& n1, int& n2);
void SubList(List& L1, List& L2, List& L3);
void AddList(List& L1, List& L2, List& L3);
void SelectMethod(List& A, List& B, List& C, int& n1, int& n2, char& sym1, char& sym2);
void ShowList(List& L);


#endif
