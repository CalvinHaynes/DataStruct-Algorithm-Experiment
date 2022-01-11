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
    int vname[MAX_NUM];           //顶点名称
    int weight[MAX_NUM][MAX_NUM]; //权值
} Tnode, *tnode;

void createGraph(tnode t)
{
    cout << "输入顶点和边数:" << endl;
    cin >> t->v >> t->e;
    cout << "输入所有顶点名称:" << endl;
    int i;
    for (i = 1; i <= t->v; i++)
    {
        cin >> t->vname[i];
    }
    for (i = 1; i <= t->v; i++)
    {
        for (int j = 1; j <= t->v; j++)
        {
            t->weight[i][j] = LIMITLESS;
        }
    }
    cout << "输入图的信息:" << endl;
    int k1, k2, weight;
    for (i = 1; i <= t->e; i++)
    {
        cin >> k1 >> k2 >> weight;
        t->weight[k1][k2] = weight;
    }
}

void printGraph(tnode t)
{
    for (int i = 1; i <= t->v; i++)
    {
        for (int j = 1; j <= t->v; j++)
        {
            if (t->weight[i][j] != LIMITLESS)
            {
                cout << t->weight[i][j] << " ";
            }
            else
            {
                cout << "∞"
                     << " ";
            }
        }
        cout << endl;
    }
}

void dijkstra(tnode t, int source)
{
    bool s[MAX_NUM];         //判断节点是否被访问的标志数组
    int dist[MAX_NUM];       //源点到终点最短距离数组
    int prev[MAX_NUM] = {0}; //源点到终点最短路径的路径数组（存储各节点的前驱结点）

    int i;
    for (i = 1; i <= t->v; i++)
    {
        dist[i] = t->weight[source][i]; //记录从源点到各终点的直接长度
        s[i] = false;
        if (dist[i] != LIMITLESS)
        {
            prev[i] = source; //若源点到顶点的距离不为空,则将源点置为顶点的前置点
        }
        else
        {
            prev[i] = 0; // 0表示前置节点不存在
        }
    }

    dist[source] = 0;
    s[source] = true;

    for (i = 1; i < t->v; i++)
    {
        int min = LIMITLESS;
        int flag = source;

        for (int j = 1; j <= t->v; j++)
        { 
            //找到距源点距离最小且未被访问的节点
            if (!s[j] && dist[j] < min)
            {
                flag = j;
                min = dist[j];
            }
        }

        s[flag] = true; //标记节点已被访问

        for (int i = 1; i <= t->v; i++)
        { 
            //从上面找到的顶点向其它顶点探索,优化源点到其他顶点的距离
            if (!s[i] && t->weight[flag][i] < LIMITLESS)
            {
                int newdist = dist[flag] + t->weight[flag][i];
                if (newdist < dist[i])
                { 
                    //其它顶点距离更新
                    dist[i] = newdist;
                    prev[i] = flag;
                }
            }
        }
    }

    stack<int> ss[MAX_NUM]; 

    for (i = 1; i <= t->v; i++)
    {
        cout << "\n源点到终点" << i << "的最短距离为:" << dist[i];
        cout << ",最短路径为:" << endl;
        int p = prev[i];
        if (!p)
        {
            cout << "源点到自身路径为空!" << endl;
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
            if (i != source)
                cout << "->" << i;  
        }
    }
}

int main()
{
    Tnode t;
    createGraph(&t);
    cout << "构建的图为:" << endl;
    printGraph(&t);
    cout << "dijkstra算法结果如下:" << endl;
    dijkstra(&t, 1);
    return 0;
}

/*
测试集

输入顶点和边数:
5 7
输入顶点信息:
1 2 3 4 5
输入两连接点下标和权值:
1 2 10
1 3 3
1 4 20
2 4 5
4 5 9
3 2 2
3 5 15

*/