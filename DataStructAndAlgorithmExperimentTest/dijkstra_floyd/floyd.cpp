#include <iostream>
using namespace std;

const int INF = 99999999;

// n：顶点数，m：边数
int n, m;

struct node
{
    int space;  //点i到点j的最短距离
    int pre;    //点j的前驱点
} map[110][110]; 

void input()
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            if (i == j)
                map[i][j].space = 0;
            else
                map[i][j].space = INF;
            map[i][j].pre = i;
        }
    int a, b, x;
    for (i = 0; i < m; i++)
    {
        cin >> a >> b >> x;
        map[a][b].space = x;
    }
}

void floyd() 
{
    int k, i, j;
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
            {
                if (map[i][k].space != INF && map[k][j].space != INF && map[i][k].space + map[k][j].space < map[i][j].space)
                {
                    map[i][j].space = map[i][k].space + map[k][j].space;
                    map[i][j].pre = k;
                }
            }
}

void output()
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if(map[i][j].space != INF){
                cout << i << "~" << j << "的最短距离:" << map[i][j].space << endl;
                int k = j;
                cout << "路径:" << i << " ";
                while (map[i][k].pre != i)
                {
                    cout << map[i][k].pre << " ";
                    k = map[i][k].pre;
                }
                cout << j << " \n";
            }
        }
    }
}

int main()
{
    cout << "请输入图的信息（第一行第一个数值为节点数，第二个为边数，后面每一行为图的各边信息）" << endl;

    cin >> n >> m;
    input();

    floyd();

    output();

    return 0;
}
