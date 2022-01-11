#include <stdio.h>
#include <string.h>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 100;
struct node
{
    int v, w;
};

stack<int> toporder;
vector<node> G[maxn];
int n, m, ve[maxn], vl[maxn], indegree[maxn];

bool topologicalsort()
{
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        printf("%d ", u);
        q.pop();
        toporder.push(u);
        for (int i = 0; i < G[u].size(); i++)
        {
            int v = G[u][i].v;
            indegree[v]--;
            if (indegree[v] == 0)
            {
                q.push(v);
            }
            if (ve[u] + G[u][i].w > ve[v])
            {
                ve[v] = ve[u] + G[u][i].w;
            }
        }
    }
    // printf("%d ",toporder.size());
    if (toporder.size() == n)
        return true;
    else
        return false;
}

int criticalpath()
{
    memset(ve, 0, sizeof(ve));
    if (topologicalsort() == false)
    {
        return -1;
    }
    printf("\n");
    fill(vl, vl + n, ve[n - 1]);
    while (!toporder.empty())
    {
        int u = toporder.top();
        toporder.pop();
        for (int i = 0; i < G[u].size(); i++)
        {
            int v = G[u][i].v;
            if (vl[v] - G[u][i].w < vl[u])
            {
                vl[u] = vl[v] - G[u][i].w;
            }
        }
    }

    for (int u = 0; u < n; u++)
    {
        for (int i = 0; i < G[u].size(); i++)
        {
            int v = G[u][i].v, w = G[u][i].w;
            int e = ve[u], l = vl[v] - w;
            if (e == l)
            {
                printf("%d->%d\n", u, v);
            }
        }
    }
    return ve[n - 1]; //返回关键路径长度
}

int main()
{
    scanf("%d %d", &n, &m);
    int s, t, weight, i;
    for (i = 0; i < m; i++)
    {
        scanf("%d %d %d", &s, &t, &weight);
        node pt; //用一个临时节点先存数据
        pt.v = t;
        pt.w = weight;
        G[s].push_back(pt); //邻接表的存法注意下
    }
    for (i = 0; i < n; i++)
    {
        scanf("%d", &indegree[i]); //记录入度
    }
    // topologicalsort();
    printf("拓扑排序序列为:\n");
    int ans = criticalpath();
    printf("%d\n", ans);
    return 0;
}
