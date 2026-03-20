#ifndef _GRAPH_H_
#define _GRAPH_H_
#include<stdio.h>
#include<stdlib.h>
#define N 20
typedef enum{DG,DN,UG,UDN}GraphKind;
typedef struct ArcNode {
	int adjvex;//顶点数组索引
	struct ArcNode *nextarc;//指向下一个边结点的指针
}ArcNode;
typedef struct VNode{
	int data;
	ArcNode *firstarc;//顶点指向边的入口指针
} VNode;
typedef VNode AdjList[N];//存储顶点
typedef struct {
	AdjList vertices;
	int vexnum;//顶点数
	int arcnum;//边数
	GraphKind kind;
}ALGraph;

void CreateDG(ALGraph* G);//创建有向图
void DFS(ALGraph G, int v, int visited[]);//DFS搜索
void DFSGraph(ALGraph G);
int OutputDegree(ALGraph G, int i);
int InDegree(ALGraph G, int j);
int DeleteArc(ALGraph* G, int i, int j);
#endif
