#pragma once
#include<iostream>
#include<queue>
#include<malloc.h>
using namespace std;
#define MAX_VEX 100
template <class T>
struct node {							//表节点 
	T adjvex;                           //邻接顶点域 
	node<T>*nextarc;					//指向下一个邻接顶点的指针域 
};
template <class T>
struct vexnode {						//头节点 
	T vertex;                           //顶点域 
	node<T>*firstarc;					//边表头指针 以邻接表方式存储的图类型
};
template <class T>
class graph {
public:
	graph() { creat_graph(); }
	~graph() { delete_graph(); }
	void SPTraverse();
	void DFSTraverse();							//递归深度优先搜索
	void BFS();									//广度优先搜索
	void delete_graph();
	void creat_graph();							//生成无向图
	void print();								//打印
private:
	int SP(int v1, int v2, int k);				//递归搜寻最短路径
	void DFS(int i);						
	vexnode<T>adjlist[MAX_VEX];                 //定义头节点数组
	bool visited[MAX_VEX];						//节点访问标识
	node<T>*ptr;								//无向图
	queue<T>q;
	int n;										//节点数量
	int m;										//边数量		
};
template <class T>
int graph<T>::SP(int v1, int v2, int k)			//递归搜寻简单路径
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
		visited[v1] = false;					//搜寻所有可能的路径
	}
	return 0;
}
template <class T>
void graph<T>::SPTraverse()
{
	int k, v1, v2;
	bool exist = false;
	for (int i = 0; i < n; i++)
		visited[i] = false;						//初始设置节点为未访问 
	cout << "分别输入 起始节点 终点 路径长度k:"; cin >> v1 >> v2 >> k;
	int temp = v1 - 1;
	while (SP(v1 - 1, v2 - 1, k))
	{
		exist = true;
		cout << "存在: ";
		cout << adjlist[temp].vertex << " ";
		while (!q.empty()) {
			cout << q.front() << " ";
			q.pop();
		}
		cout << endl;
	}
	if (!exist)
		cout << "不存在" << endl;
}
template <class T>
void graph<T>::DFS(int i)						//邻接表的深度优先递归
{
	node<T>*p;
	visited[i] = true;         					//访问过了该顶点，标记为true
	cout << adjlist[i].vertex<<" ";
	p = adjlist[i].firstarc;					//p指向边表第一个结点 
	while (p)									
	{
		if (!visited[p->adjvex])				//对未访问的邻接顶点递归调用 
			DFS(p->adjvex);
		p = p->nextarc;
	}
}
template <class T>
void graph<T>::DFSTraverse()
{
	for (int i = 0; i < n; i++)
		visited[i] = false;						//初始设置节点为未访问 
	for (int i = 0; i < n; i++)
		if (!visited[i])
			DFS(i);								//对未访问的顶点调用递归		
}
template <class T>
void graph<T>::BFS() {
	for (int i = 0; i < n; i++)
		visited[i] = false;						//初始设置节点为未访问 
	for (int i = 0; i < n; i++) 
	{
		visited[i] = true;
		cout<<adjlist[i].vertex<<" ";
		q.push(i);
		while (!q.empty()) {
			q.pop();  
			node<T> *p = adjlist[i].firstarc;	//i顶点的邻接链表的第一个结点
			while (p) {							//遍历p的所有邻接点 
				if (!visited[p->adjvex]) { 
					visited[p->adjvex] = true;
					cout<<adjlist[p->adjvex].vertex<<" ";
					q.push(p->adjvex);			//将该结点入队  
				}
				i++;
				p = p->nextarc;					//遍历i的下一个邻接点 	
			}
			
		}
	}
}
template <class T>
void graph<T>::creat_graph()						//生成无向图
{
	int j = 0;
	cout << "请输入节点和边的数量:"; cin >> n >> m;
	cout << "请依次输入节点信息:";
	for (int i = 0; i < n; i++)
		 cin >> adjlist[i].vertex;
	cout << "请输入节点的链接情况:" << endl;
	for (int i = 0; i < m; i++)
	{
		T v1, v2;
		cout << "v1,v2="; cin >> v1 >> v2;
		v1 -= 1; v2 -= 1;
		ptr = (node<T> *)malloc(sizeof(node<T>));
		ptr->adjvex = v2;							//将顶点下标(v2)插入到链表中
		ptr->nextarc = adjlist[v1].firstarc;
		adjlist[v1].firstarc = ptr;					//将邻接点下标(v2)插入表头节点(v1)之后

		ptr = (node<T> *)malloc(sizeof(node<T>));	//无向图
		ptr->adjvex = v1;
		ptr->nextarc = adjlist[v2].firstarc;
		adjlist[v2].firstarc = ptr;
	}
}
template <class T>
void graph<T>::print()							//打印
{
	node<T>*p;
	printf("邻接表结构:\n");
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
