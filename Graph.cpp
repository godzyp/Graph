#include <iostream>
#include "graph.h"
using namespace std;

int main()
{
	graph<int>G;
	G.print();
	G.DFSTraverse();
	cout << endl;
	G.BFS();
	cout << endl;
	G.SPTraverse();
	return 0;
}

