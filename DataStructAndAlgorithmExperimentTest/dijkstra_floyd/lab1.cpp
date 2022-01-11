#include <iostream>
#include <iomanip>

using namespace std;

constexpr int MAX = 5;

class ArcN
{
public:
    int number;
    int weight;
    ArcN *nextArc;
};

class HeadN
{
public:
    ArcN *firstArc;
};

class graph
{
public:
    int m = 4;
    int n = 4;
    HeadN head[MAX];
};

//输出二阶矩阵:
void OutPut(int a[MAX][MAX])
{
    for (int i = 0; i < MAX; i++)
    {
        cout << endl;
        for (int j = 0; j < MAX; j++)
            cout << left << setw(6) << a[i][j] << ' ';
    }
    cout << endl;
}

//输出最短路径:
void OutPut(int R[MAX][MAX], int i, int j)
{
    if (R[i][j] == j)
        cout << "-->" << j;
    else
    {
        OutPut(R, i, R[i][j]);
        OutPut(R, R[i][j], j);
    }
}

//实验一 图论模型设计与存储
void Adjlist(graph *&g1, int mat[MAX][MAX])
{
    ArcN *p;
    g1 = (graph *)malloc(sizeof(graph));
    if (g1 == NULL)
        exit(0);
    int m;

    OutPut(mat);

    for (int i = 0; i < MAX; i++)
    {
        g1->head[i].firstArc = NULL;
        m = 0;
        for (int j = 0; j < MAX; j++)
            if ((mat[i][j] > 0) && (mat[i][j] < 65535))
            {
                p = (ArcN *)malloc(sizeof(ArcN));
                if (p == NULL)
                    exit(0);
                p->number = j;
                p->weight = mat[i][j];
                p->nextArc = NULL;
                if (m++ == 0)
                    g1->head[i].firstArc = p;
                else
                {
                    p->nextArc = g1->head[i].firstArc;
                    g1->head[i].firstArc = p;
                }
            }
    }

    for (int i = 0; i < MAX; ++i)
    {
        cout << '\n';
        ArcN *a = (*g1).head[i].firstArc;
        if (a != 0)
            cout << i;
        for (int j = 0; j < MAX; ++j)
            if (a != 0)
            {
                cout << "-->" << a->number << '(' << a->weight << ')';
                a = a->nextArc;
            }
            else
                break;
    }
}

//实验二 图的遍历输出
int visit[MAX] = {0};
int q = 0;
void DFS(graph *&g1, int v)
{
    visit[v] = 1;
    ArcN *p = g1->head[v].firstArc;
    if (q++ != 0)
        cout << "-->";
    cout << v;
    while (p != 0)
    {
        if (visit[p->number] == 0)
            DFS(g1, p->number);
        p = p->nextArc;
    }
}

int visit2[MAX] = {0};
int Se[MAX] = {0};
int t = 0;
int a = 0;
void BFS(graph *&g1, int v)
{
    ArcN *p = g1->head[v].firstArc;
    if (visit2[v] == 0)
    {
        visit2[v] = 1;
        Se[t++] = v;
    }
    while (p != NULL)
    {
        if (visit2[p->number] == 0)
        {
            printf("this is p-->number:%d\n", p->number);
            Se[t++] = p->number;
            visit2[p->number] = 1;
        }
        p = p->nextArc;
    }
    if (t < MAX)
        BFS(g1, Se[a++]);
}

//实验三 图的最小生成树设计
void Kruskal(int mat[MAX][MAX])
{
    int s[MAX] = {-1, -1, -1, -1, -1};
    // int w[2 * (MAX - 1)] = { 0 };
    // int k = 0;
    int t = 0;
    int a = 65535;
    int m, n = 0;
    int x, y = 0;
    int b = 0;
    while (b < MAX)
    {
        a = 65535;
        t = 0;
        x = y = 0;
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                if ((mat[i][j] > 0) && (a > mat[i][j]) && (i != j))
                {
                    a = mat[i][j];
                    m = i;
                    n = j;
                }
        mat[m][n] = 65535;

        for (int i = 0; i < MAX; i++)
        {
            if (m == s[i])
                x = 1;
            if (n == s[i])
                y = 1;
        }

        if (x == 0)
            s[b++] = m;
        if (y == 0)
            s[b++] = n;
        if (x + y < 2)
        {
            // w[k++] = m;
            // w[k++] = n;
            printf("route:%d-->%d weight:%d\n", m, n, a);
        }

        // cout << "b==" << b;
    }
    // for (int i = 0;i < 2*(MAX-1);++i)
    // cout << w[i] << "-->";
}
void Prim(int mat[MAX][MAX])
{
    int v[MAX] = {0};
    int t = 65535;
    int m1[MAX - 1] = {0};
    int m2[MAX - 1] = {0};
    int n = 0;
    for (int i = 0; i < MAX; i++)
        if ((mat[0][i] > 0) && (mat[0][i] < 65535) && (t > mat[0][i]))
        {
            t = mat[0][i];
            m2[n] = i;
        }
    v[n + 1] = m2[n];
    ++n;

    for (; n < MAX - 1;)
    {
        t = 65535;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                mat[v[i]][v[j]] = 65535;

        for (int j = 0; j <= n; j++)
            for (int i = 0; i < MAX; i++)
                if ((mat[v[j]][i] > 0) && (mat[v[j]][i] < 65535) && (t > mat[v[j]][i]))
                {
                    t = mat[v[j]][i];
                    m1[n] = v[j];
                    m2[n] = i;
                }

        v[n + 1] = m2[n];
        ++n;
    }

    for (int i = 0; i < MAX - 1; ++i)
        printf("(%d,%d)", m1[i], m2[i]);
}

//实验四 图的单源最短路径求解
void Dijkstra(int mat[MAX][MAX], int v, int m)
{
    int R[MAX][MAX];
    int W[MAX] = {0};
    int W1[MAX] = {0};
    int t = 65535;
    int n = -1;
    for (int i = 0; i < MAX; ++i)
        W[i] = mat[v][i];

    int G[MAX] = {0};

    for (int i = 0; i < MAX; i++)
    {
        t = 65535;
        for (int j = 0; j < MAX; j++)
        {
            R[i][j] = -1;
            if ((W[j] < 65535) && (W[j] != -1) && (t > W[j]))
            {
                t = W[j];
                n = j;
            }
        }
        W[n] = -1;
        G[i] = n;
        W1[i] = t;

        for (int j = 0; j < MAX; j++)
            if ((W[j] != -1) && (mat[v][i] != 65535) && (mat[i][j] != 65535))
                if (W[j] > mat[v][i] + mat[i][j])
                {
                    W[j] = mat[v][i] + mat[i][j];
                    R[i][j] = i;
                }
    }

    for (int i = 0; i < MAX; i++)
        cout << G[i];
    cout << endl;
    for (int i = 0; i < MAX; i++)
        cout << W1[i];
    cout << endl
         << endl;

    //输出最短路径
    for (int i = 0; i < MAX; i++)
    {
        /*cout << v << "-->" << i << ':' << v << "-->";
        for (int j = 0;j < MAX;++j)
            //固定列输出行
            if (R[j][i] != -1)
                cout << R[j][i] << "-->";
        cout << i;
        for (int k = 0;k < MAX;k++)
            if (G[k] == i)
                cout << '(' << W1[k] << ')' << endl;*/

        if (i == m)
        {
            cout << v << "-->" << i << ':' << v << "-->";
            for (int j = 0; j < MAX; ++j)
                //固定列输出行
                if (R[j][i] != -1)
                    cout << R[j][i] << "-->";
            cout << i;
            for (int k = 0; k < MAX; k++)
                if (G[k] == i)
                    cout << '(' << W1[k] << ')' << endl;
        }
    }
}

//实验五 图的任意两点间最短路径求解
void Floyd(int mat[MAX][MAX], int v1, int v2)
{
    //计算路由矩阵:
    int R[MAX][MAX] = {0};
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
        {
            R[i][j] = -1;
            if ((mat[i][j] > 0) && (mat[i][j] < 65535))
                R[i][j] = j;
        }

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            for (int k = 0; k < MAX; k++)
                if ((mat[j][i] != 65535) && (mat[i][k] != 65535) && (mat[j][k] > mat[j][i] + mat[i][k]))
                {
                    mat[j][k] = mat[j][i] + mat[i][k];
                    R[j][k] = i;
                }

    OutPut(mat);
    OutPut(R);

    cout << endl
         << endl
         << endl;

    //输出最短路径及权值:
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            if (R[i][j] != -1)
            {
                // printf("\n%d-->%d: weight:%d route:%d", i, j, mat[i][j], i);
                OutPut(R, i, j);
            }
            else
                // printf("\n节点(%d,%d)间无路径", i, j);
    cout << "\n\n\n";
    printf("\n%d-->%d: weight:%d route:%d", v1, v2, mat[v1][v2], v1);
    OutPut(R, v1, v2);
}

int main()
{
    graph *g1;
    char c;
    int mat[MAX][MAX] = {0};
    int replica[MAX][MAX] = {0};

    cout << "请输入图的信息:" << endl;

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
        {
            cin >> c >> mat[i][j];
            replica[i][j] = mat[i][j];
        }

    cin >> c;

    //实验一 图论模型设计与存储
    // Adjlist(g1, mat);

    //实验二 图的遍历输出
    int v;
    // cout << '\n'
    //      << '\n';
    // cin >> v;
    // cout << '\n'
    //      << '\n'
    //      << "DFS:" << endl;
    // DFS(g1, v);
    // cout << '\n'
    //      << '\n'
    //      << "BFS:" << endl;
    // BFS(g1, v);
    // for (int i = 0; i < MAX; ++i)
    //     cout << Se[i];
    // cout << endl
    //      << endl;

    //实验三 图的最小生成树设计
    cout << "最小生成树(Kruskal):" << endl;
    Kruskal(mat);

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            mat[i][j] = replica[i][j];

    // cout << endl << "最小生成树(Prim):" << endl;

    int min = 65535;
    int qq1, qq2 = -1;
    for (int k = 0; k < MAX * MAX; k++)
    {
        min = 65535;
        qq1 = -1;
        qq2 = -1;
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                if ((min > mat[i][j]) && (mat[i][j] != 65535) && (mat[i][j] > 0))
                {
                    qq1 = i;
                    qq2 = j;
                    min = mat[i][j];
                }
        mat[qq1][qq2] = 65535;
        if (min != 65535)
            printf("%d->%d:weight=%d\n", qq1, qq2, min);
    }

    // Prim(mat);

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            mat[i][j] = replica[i][j];

    //实验四 图的单源最短路径求解

    cout << endl
         << endl
         << "请输入两个节点:" << endl;
    int m = 0;
    cin >> v >> m;
    // Dijkstra(mat, v, m);

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            mat[i][j] = replica[i][j];

    //实验五 图的任意两点间最短路径求解
    // cout << endl
    //      << endl
    //      << "图的任意两点间最短路径:" << endl;
    Floyd(mat, v, m);

    return 0;
}