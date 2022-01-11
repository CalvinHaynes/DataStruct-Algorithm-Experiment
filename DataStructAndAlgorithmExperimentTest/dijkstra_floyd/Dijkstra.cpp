#include <iostream>
#include <algorithm>
#include <cstdio>
#include <stack>
#define MAX_NUM 50
#define LIMITLESS 65535
using namespace std;
typedef struct Tnode
{
    int v, e;
    int vex[MAX_NUM];
    int wei[MAX_NUM][MAX_NUM];
} Tnode, *tnode;
void createGraph(tnode t)
{
    cout << "输入顶点和边数:" << endl;
    cin >> t->v >> t->e;
    cout << "输入顶点信息:" << endl;
    int i;
    for (i = 1; i <= t->v; i++)
    {
        cin >> t->vex[i];
    }
    for (i = 1; i <= t->v; i++)
    {
        for (int j = 1; j <= t->v; j++)
        {
            t->wei[i][j] = LIMITLESS;
        }
    }
    cout << "输入两连接点下标和权值:" << endl;
    int k1, k2, weight;
    for (i = 1; i <= t->e; i++)
    {
        cin >> k1 >> k2 >> weight;
        t->wei[k1][k2] = weight;
    }
}
void printGraph(tnode t)
{
    for (int i = 1; i <= t->v; i++)
    {
        for (int j = 1; j <= t->v; j++)
        {
            if (t->wei[i][j] != LIMITLESS)
            {
                cout << t->wei[i][j] << "  ";
            }
            else
            {
                cout << "oo"
                     << "  ";
            }
        }
        cout << endl;
    }
}
void dijkstra(tnode t, int sour)
{
    bool s[MAX_NUM];         //标识节点是否被访问
    int dist[MAX_NUM];       //源点到顶点距离，存储最短路径长度的数组
    int prev[MAX_NUM] = {0}; //顶点的前置顶点，最后迭代输出最短路径
    int i;
    for (i = 1; i <= t->v; i++)
    {
        dist[i] = t->wei[sour][i]; //记录从源点到各顶点的路径长
        s[i] = false;              //初始化标识数组
        if (dist[i] != LIMITLESS)
        { //若源点到顶点的距离不为空,则将源点置为顶点的前置点
            prev[i] = sour;
        }
        else
        {
            prev[i] = 0;
        }
    }
    dist[sour] = 0, s[sour] = true;
    for (i = 1; i < t->v; i++)
    {
        int item = LIMITLESS;
        int flag = sour;
        for (int j = 1; j <= t->v; j++)
        {
            if (!s[j] && dist[j] < item)
            {
                flag = j;
                item = dist[j];
            }
        }
        s[flag] = true;
        for (int i = 1; i <= t->v; i++)
        {
            if (!s[i] && t->wei[flag][i] < LIMITLESS)
            {
                int newdist = dist[flag] + t->wei[flag][i];
                if (newdist < dist[i])
                {
                    dist[i] = newdist;
                    prev[i] = flag;
                }
            }
        }
    }
    stack<int> ss[MAX_NUM]; //栈实现打印路径构建
    for (i = 1; i <= t->v; i++)
    {
        cout << "\n源点到顶点" << i << "的最短距离为:" << dist[i];
        cout << ",最短路径构建为:" << endl;
        int p = prev[i];
        if (!p)
        {
            cout << "源点到自身路径构建为空!" << endl;
        }
        else
        {
            while (p)
            {
                ss[i].push(p);
                p = prev[p];
            }
            while (!ss[i].empty())
            {
                int k = ss[i].top();
                cout << k;
                ss[i].pop();
                if (!ss[i].empty())
                {
                    cout << "->";
                }
            }
            if (i != sour)
                cout << "->" << i; //顶点自身值打印
        }
    }
}
int main()
{
    Tnode t;
    createGraph(&t);
    cout << "构建的图为:" << endl;
    printGraph(&t);
    cout << "dijkstra算法构建的顶点最短路径为:" << endl;
    dijkstra(&t, 1);
    return 0;
}
