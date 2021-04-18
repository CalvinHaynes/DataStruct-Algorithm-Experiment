#include <iostream>
using namespace std;

const int MaxSize = 100;//足够大，最小等于路的个数（如果不明白可等明白该算法原理再回头看看）
const int M = 8;//迷宫大小（左右长）
const int N = 8;//迷宫大小（上下长）

typedef struct
{
	int i, j;//方块的位置
	int pre;//本路径中上一个方块在队列中的下标
}Box;//方块数据类型

typedef struct
{
	Box data[MaxSize];//方块类型的数组
	int front, rear;//队头指针和队尾指针
}QuType;//顺序队类型

void InitQueue(QuType*& q);//初始化队列

bool QueueEmpty(QuType* q);//判断队列是否为空

bool enQueue(QuType*& q, Box e);//加入队列

bool deQueue(QuType*& q, Box& e);//离开队列

void DestroyQueue(QuType*& q);//销毁队列

void print(QuType* qu, int front);//打印队列

int mg[M + 2][N + 2] = {//迷宫 1是墙壁 0是路  +2是因为有一圈墙壁
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,0,0,1,1,0,0,1},
	{1,0,1,1,1,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,1},
	{1,0,1,1,1,0,1,1,0,1},
	{1,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

bool mgpath1(int xi, int yi, int xe, int ye)//xiyi为出发点的xy，xeye为终点的xy
{
	Box e;//Box类型的e
	int i, j, di, i1, j1;
	QuType* qu;//队列指针
	InitQueue(qu);//初始化
	e.i = xi; e.j = yi; e.pre = -1;//赋值出发点
	enQueue(qu, e);//盒子进队
	mg[xi][yi] = -1;//出发点赋值-1
	while (!QueueEmpty(qu))//当队列不空时循环
	{
		deQueue(qu, e);//出队e，因为不是环形队列，出队后e仍在队列中。
		i = e.i; j = e.j;//赋值e的位置
		if (i == xe && j == ye)//如果e的位置是终点
		{
			print(qu, qu->front);//调用print函数（我们自己重写的函数）
			DestroyQueue(qu);//销毁队列
			return true;//返回真
		}
		for (di = 0; di < 4; di++)//四个方位循环扫描
		{
			switch (di)//di的值决定了选项
			{
			case 0:i1 = i - 1; j1 = j; break;//向左（以图形的角度描述）
			case 1:i1 = i; j1 = j + 1; break;//向下（出发点为左上角）
			case 2:i1 = i + 1; j1 = j; break;//向右
			case 3:i1 = i; j1 = j - 1; break;//向上
			}
			if (mg[i1][j1] == 0)//如果这个点为0（路）
			{
				e.i = i1; e.j = j1;//可走的话将这个添加到e中
				e.pre = qu->front; //e的pre指向上一个方块的下标
				enQueue(qu, e);//进队
				mg[i1][j1] = -1;//赋值该方块为-1表示不可再走
			}
		}
	}
	DestroyQueue(qu);//销毁队列
	return false;//返回假，表示没有找到路径
}

void print(QuType* qu, int front)//我们自己重写的print函数
{                                //作用是输出qu里的路径
	int k = front, j, ns = 0;
	cout << endl;//换行
	do//do-while
	{
		j = k;//do-while先赋值一次再循环
		k = qu->data[k].pre;//赋值给k当前方块的前一个方块的下标
		qu->data[j].pre = -1;//将当前方块的pre设为-1
	} while (k != 0);//pre在输出的时候可作为标记，在寻路的时候是当前方块的上一个方块的下标
	cout << "一条迷宫路径如下：" << endl;
	k = 0;
	while (k <= front)//当k小于front时（可以考虑下为什么）
	{
		if (qu->data[k].pre == -1)//输出所有pre=-1的方块坐标
		{
			ns++;//为排版而存在的变量
			cout << "(";
			cout << qu->data[k].i;
			cout << ",";
			cout << qu->data[k].j;
			cout << ")";//输出坐标
			if (ns % 5 == 0)//五个一行
				cout << endl;
		}
		k++;
	}
	cout << endl;//换行
}

int main() {
	if (!mgpath1(1, 1, M, N))//调用mgpath1函数，为真则无解
		cout << "该迷宫问题没有解！" << endl;
	return 1;
}


void InitQueue(QuType*& q)//初始化队列
{
	q = (QuType*)malloc(sizeof(QuType));
	q->front = q->rear = -1;
}

bool QueueEmpty(QuType* q)//队列是否为空
{
	return(q->front == q->rear);
}

bool enQueue(QuType*& q, Box e)//进队
{
	if (q->rear == MaxSize - 1)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

bool deQueue(QuType*& q, Box& e)//出队
{
	if (q->front == q->rear)
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}

void DestroyQueue(QuType*& q)//销毁队列
{
	free(q);
}
