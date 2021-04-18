#include <iostream>
using namespace std;

const int MaxSize = 100;//�㹻����С����·�ĸ�������������׿ɵ����׸��㷨ԭ���ٻ�ͷ������
const int M = 8;//�Թ���С�����ҳ���
const int N = 8;//�Թ���С�����³���

typedef struct
{
	int i, j;//�����λ��
	int pre;//��·������һ�������ڶ����е��±�
}Box;//������������

typedef struct
{
	Box data[MaxSize];//�������͵�����
	int front, rear;//��ͷָ��Ͷ�βָ��
}QuType;//˳�������

void InitQueue(QuType*& q);//��ʼ������

bool QueueEmpty(QuType* q);//�ж϶����Ƿ�Ϊ��

bool enQueue(QuType*& q, Box e);//�������

bool deQueue(QuType*& q, Box& e);//�뿪����

void DestroyQueue(QuType*& q);//���ٶ���

void print(QuType* qu, int front);//��ӡ����

int mg[M + 2][N + 2] = {//�Թ� 1��ǽ�� 0��·  +2����Ϊ��һȦǽ��
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

bool mgpath1(int xi, int yi, int xe, int ye)//xiyiΪ�������xy��xeyeΪ�յ��xy
{
	Box e;//Box���͵�e
	int i, j, di, i1, j1;
	QuType* qu;//����ָ��
	InitQueue(qu);//��ʼ��
	e.i = xi; e.j = yi; e.pre = -1;//��ֵ������
	enQueue(qu, e);//���ӽ���
	mg[xi][yi] = -1;//�����㸳ֵ-1
	while (!QueueEmpty(qu))//�����в���ʱѭ��
	{
		deQueue(qu, e);//����e����Ϊ���ǻ��ζ��У����Ӻ�e���ڶ����С�
		i = e.i; j = e.j;//��ֵe��λ��
		if (i == xe && j == ye)//���e��λ�����յ�
		{
			print(qu, qu->front);//����print�����������Լ���д�ĺ�����
			DestroyQueue(qu);//���ٶ���
			return true;//������
		}
		for (di = 0; di < 4; di++)//�ĸ���λѭ��ɨ��
		{
			switch (di)//di��ֵ������ѡ��
			{
			case 0:i1 = i - 1; j1 = j; break;//������ͼ�εĽǶ�������
			case 1:i1 = i; j1 = j + 1; break;//���£�������Ϊ���Ͻǣ�
			case 2:i1 = i + 1; j1 = j; break;//����
			case 3:i1 = i; j1 = j - 1; break;//����
			}
			if (mg[i1][j1] == 0)//��������Ϊ0��·��
			{
				e.i = i1; e.j = j1;//���ߵĻ��������ӵ�e��
				e.pre = qu->front; //e��preָ����һ��������±�
				enQueue(qu, e);//����
				mg[i1][j1] = -1;//��ֵ�÷���Ϊ-1��ʾ��������
			}
		}
	}
	DestroyQueue(qu);//���ٶ���
	return false;//���ؼ٣���ʾû���ҵ�·��
}

void print(QuType* qu, int front)//�����Լ���д��print����
{                                //���������qu���·��
	int k = front, j, ns = 0;
	cout << endl;//����
	do//do-while
	{
		j = k;//do-while�ȸ�ֵһ����ѭ��
		k = qu->data[k].pre;//��ֵ��k��ǰ�����ǰһ��������±�
		qu->data[j].pre = -1;//����ǰ�����pre��Ϊ-1
	} while (k != 0);//pre�������ʱ�����Ϊ��ǣ���Ѱ·��ʱ���ǵ�ǰ�������һ��������±�
	cout << "һ���Թ�·�����£�" << endl;
	k = 0;
	while (k <= front)//��kС��frontʱ�����Կ�����Ϊʲô��
	{
		if (qu->data[k].pre == -1)//�������pre=-1�ķ�������
		{
			ns++;//Ϊ�Ű�����ڵı���
			cout << "(";
			cout << qu->data[k].i;
			cout << ",";
			cout << qu->data[k].j;
			cout << ")";//�������
			if (ns % 5 == 0)//���һ��
				cout << endl;
		}
		k++;
	}
	cout << endl;//����
}

int main() {
	if (!mgpath1(1, 1, M, N))//����mgpath1������Ϊ�����޽�
		cout << "���Թ�����û�н⣡" << endl;
	return 1;
}


void InitQueue(QuType*& q)//��ʼ������
{
	q = (QuType*)malloc(sizeof(QuType));
	q->front = q->rear = -1;
}

bool QueueEmpty(QuType* q)//�����Ƿ�Ϊ��
{
	return(q->front == q->rear);
}

bool enQueue(QuType*& q, Box e)//����
{
	if (q->rear == MaxSize - 1)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

bool deQueue(QuType*& q, Box& e)//����
{
	if (q->front == q->rear)
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}

void DestroyQueue(QuType*& q)//���ٶ���
{
	free(q);
}
