#include<iostream>
using namespace std;

//定义二叉树结构
typedef struct Node
{
    char data;
    struct Node* lchild, * rchild;
}*BiTree, BiTNode;

/*****************API清单******************/
void CreateBiTree(BiTree& T);//先序创建二叉树
void PrintBiTree(BiTree T, int nLayer);//二叉树输出（树形结构）
void PreOrderTraverse(BiTree T);//先序遍历
void InOrderTraverse(BiTree T);//中序遍历
void PostOrderTraverse(BiTree T);//后序遍历
int GetDepth(BiTree T);//统计树的深度
int GetMax(BiTree T);//统计最大元
int GetMin(BiTree T);//统计最小元



int main() {
    BiTree T;
    printf("先序创建二叉树，请输入：（空树枝用#代替）\n");
    CreateBiTree(T);
    int depth = GetDepth(T);
    printf("二叉树输出（树形结构）\n");
    PrintBiTree(T, depth);
    printf("前序遍历:\n");
    PreOrderTraverse(T);
    printf("\n");
    printf("中序遍历:\n");
    InOrderTraverse(T);
    printf("\n");
    printf("后序遍历:\n");
    PostOrderTraverse(T);
    printf("\n");
    printf("该树的深度=%d\n", depth);
    printf("最大元=%d\n", GetMax(T));
    printf("最小元=%d\n", GetMin(T));
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
