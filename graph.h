#pragma once
#include<iostream>
#include<queue>
#include<malloc.h>
using namespace std;
#define MAX_VEX 100
template <class T>
struct node {							//��ڵ� 
	T adjvex;                           //�ڽӶ����� 
	node<T>*nextarc;					//ָ����һ���ڽӶ����ָ���� 
};
template <class T>
struct vexnode {						//ͷ�ڵ� 
	T vertex;                           //������ 
	node<T>*firstarc;					//�߱�ͷָ�� ���ڽӱ�ʽ�洢��ͼ����
};
template <class T>
class graph {
public:
	graph() { creat_graph(); }
	~graph() { delete_graph(); }
	void SPTraverse();
	void DFSTraverse();							//�ݹ������������
	void BFS();									//�����������
	void delete_graph();
	void creat_graph();							//��������ͼ
	void print();								//��ӡ
private:
	int SP(int v1, int v2, int k);				//�ݹ���Ѱ���·��
	void DFS(int i);						
	vexnode<T>adjlist[MAX_VEX];                 //����ͷ�ڵ�����
	bool visited[MAX_VEX];						//�ڵ���ʱ�ʶ
	node<T>*ptr;								//����ͼ
	queue<T>q;
	int n;										//�ڵ�����
	int m;										//������		
};
template <class T>
int graph<T>::SP(int v1, int v2, int k)			//�ݹ���Ѱ��·��
{
	node<T>*p;
	if (v1 == v2 && k == 0)
	{
		return 1;
	}
	else if (k > 0)
	{
		visited[v1] = true;
		for (p = adjlist[v1].firstarc; p; p = p->nextarc)
		{	
			q.push(adjlist[p->adjvex].vertex);
			if (!visited[p->adjvex] && SP(p->adjvex, v2, k - 1))
				return 1;
			q.pop();
		}
		visited[v1] = false;					//��Ѱ���п��ܵ�·��
	}
	return 0;
}
template <class T>
void graph<T>::SPTraverse()
{
	int k, v1, v2;
	bool exist = false;
	for (int i = 0; i < n; i++)
		visited[i] = false;						//��ʼ���ýڵ�Ϊδ���� 
	cout << "�ֱ����� ��ʼ�ڵ� �յ� ·������k:"; cin >> v1 >> v2 >> k;
	int temp = v1 - 1;
	while (SP(v1 - 1, v2 - 1, k))
	{
		exist = true;
		cout << "����: ";
		cout << adjlist[temp].vertex << " ";
		while (!q.empty()) {
			cout << q.front() << " ";
			q.pop();
		}
		cout << endl;
	}
	if (!exist)
		cout << "������" << endl;
}
template <class T>
void graph<T>::DFS(int i)						//�ڽӱ��������ȵݹ�
{
	node<T>*p;
	visited[i] = true;         					//���ʹ��˸ö��㣬���Ϊtrue
	cout << adjlist[i].vertex<<" ";
	p = adjlist[i].firstarc;					//pָ��߱��һ����� 
	while (p)									
	{
		if (!visited[p->adjvex])				//��δ���ʵ��ڽӶ���ݹ���� 
			DFS(p->adjvex);
		p = p->nextarc;
	}
}
template <class T>
void graph<T>::DFSTraverse()
{
	for (int i = 0; i < n; i++)
		visited[i] = false;						//��ʼ���ýڵ�Ϊδ���� 
	for (int i = 0; i < n; i++)
		if (!visited[i])
			DFS(i);								//��δ���ʵĶ�����õݹ�		
}
template <class T>
void graph<T>::BFS() {
	for (int i = 0; i < n; i++)
		visited[i] = false;						//��ʼ���ýڵ�Ϊδ���� 
	for (int i = 0; i < n; i++) 
	{
		visited[i] = true;
		cout<<adjlist[i].vertex<<" ";
		q.push(i);
		while (!q.empty()) {
			q.pop();  
			node<T> *p = adjlist[i].firstarc;	//i������ڽ�����ĵ�һ�����
			while (p) {							//����p�������ڽӵ� 
				if (!visited[p->adjvex]) { 
					visited[p->adjvex] = true;
					cout<<adjlist[p->adjvex].vertex<<" ";
					q.push(p->adjvex);			//���ý�����  
				}
				i++;
				p = p->nextarc;					//����i����һ���ڽӵ� 	
			}
			
		}
	}
}
template <class T>
void graph<T>::creat_graph()						//��������ͼ
{
	int j = 0;
	cout << "������ڵ�ͱߵ�����:"; cin >> n >> m;
	cout << "����������ڵ���Ϣ:";
	for (int i = 0; i < n; i++)
		 cin >> adjlist[i].vertex;
	cout << "������ڵ���������:" << endl;
	for (int i = 0; i < m; i++)
	{
		T v1, v2;
		cout << "v1,v2="; cin >> v1 >> v2;
		v1 -= 1; v2 -= 1;
		ptr = (node<T> *)malloc(sizeof(node<T>));
		ptr->adjvex = v2;							//�������±�(v2)���뵽������
		ptr->nextarc = adjlist[v1].firstarc;
		adjlist[v1].firstarc = ptr;					//���ڽӵ��±�(v2)�����ͷ�ڵ�(v1)֮��

		ptr = (node<T> *)malloc(sizeof(node<T>));	//����ͼ
		ptr->adjvex = v1;
		ptr->nextarc = adjlist[v2].firstarc;
		adjlist[v2].firstarc = ptr;
	}
}
template <class T>
void graph<T>::print()							//��ӡ
{
	node<T>*p;
	printf("�ڽӱ�ṹ:\n");
	for (int i = 0; i < n; i++)
	{
		cout<<adjlist[i].vertex;
		p = adjlist[i].firstarc;
		while (p != NULL)
		{
			cout << "->" << adjlist[p->adjvex].vertex;
			p = p->nextarc;
		}
		cout << endl;
	}
}
template <class T>
void graph<T>::delete_graph()
{	delete ptr;	}
