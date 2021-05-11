#include<iostream>
using namespace std;

//����������ṹ
typedef struct Node
{
    char data;
    struct Node* lchild, * rchild;
}*BiTree, BiTNode;

/*****************API�嵥******************/
void CreateBiTree(BiTree& T);//���򴴽�������
void PrintBiTree(BiTree T, int nLayer);//��������������νṹ��
void PreOrderTraverse(BiTree T);//�������
void InOrderTraverse(BiTree T);//�������
void PostOrderTraverse(BiTree T);//�������
int GetDepth(BiTree T);//ͳ���������
int GetMax(BiTree T);//ͳ�����Ԫ
int GetMin(BiTree T);//ͳ����СԪ



int main() {
    BiTree T;
    printf("���򴴽��������������룺������֦��#���棩\n");
    CreateBiTree(T);
    int depth = GetDepth(T);
    printf("��������������νṹ��\n");
    PrintBiTree(T, depth);
    printf("ǰ�����:\n");
    PreOrderTraverse(T);
    printf("\n");
    printf("�������:\n");
    InOrderTraverse(T);
    printf("\n");
    printf("�������:\n");
    PostOrderTraverse(T);
    printf("\n");
    printf("���������=%d\n", depth);
    printf("���Ԫ=%d\n", GetMax(T));
    printf("��СԪ=%d\n", GetMin(T));
}


void CreateBiTree(BiTree& T)
{
    char ch;
    cin >> ch;
    if (ch == '#') 
        T = NULL;
    else {
        T = new BiTNode;
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}


void PrintBiTree(BiTree T,int nLayer)
{
    int i;
    if (T == NULL)
        return;
    PrintBiTree(T->rchild, nLayer + 1);
    for (i = 0; i < nLayer; i++)
        printf("    ");
    printf("%c\n",T->data);
    PrintBiTree(T->lchild, nLayer + 1);
}


void PreOrderTraverse(BiTree T)
{
    if (T)
    {
        cout << T->data;
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}


void InOrderTraverse(BiTree T)
{
    if (T)
    {
        InOrderTraverse(T->lchild);
        cout << T->data;
        InOrderTraverse(T->rchild);
    }
}


void PostOrderTraverse(BiTree T)
{
    if (T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout << T->data;
    }
}


int GetDepth(BiTree T)
{
    if (T == NULL)
        return 0;
    else
    {
        int m = GetDepth(T->lchild);
        int n = GetDepth(T->rchild);
        if (m > n) return (m + 1);
        else return (n + 1);
    }
}


int GetMax(BiTree T)
{
    static int max = 0;
    if (T != NULL) {
        if (max < T->data) max = T->data;
        GetMax(T->lchild);
        GetMax(T->rchild);
    }
    return max;
}


int GetMin(BiTree T)
{
    static int min = 99999999;
    if (T != NULL) {
        if (T->data < min) min = T->data;
        GetMin(T->lchild);
        GetMin(T->rchild);
    }
    return min;
}
