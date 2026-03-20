#include"graph.h"
#pragma warning(disable:4996)
#include<stdio.h>
void CreateDG(ALGraph* G) {
	int i, j, k;
	ArcNode* S;
	G->kind = DG;
	printf("请输入顶点数和边数 (格式: 顶点数 边数): ");
	scanf("%d %d", &G->vexnum, &G->arcnum);
	//初始化顶点信息；
	printf("请输入 %d 个顶点的数据 (编号从 0 开始):\n", G->vexnum);
	for (i = 0; i < G->vexnum; i++) {
		scanf("%d", &G->vertices[i].data);
		G->vertices[i].firstarc = NULL;

	}
	printf("请输入%d条弧的信息 (格式: 起点,终点):\n", G->arcnum);
	for (k = 0; k < G->arcnum; k++) {
		printf("输入第%d条弧的信息:", k + 1);
		if (scanf("%d,%d", &i, &j) != 2) {
			printf("输入格式错误，请重新输入！\n");
			// 清除输入缓冲区的无效内容
			while (getchar() != '\n');
			k--; // 重新输入当前边
			continue;
		}
		S = (ArcNode*)malloc(sizeof(ArcNode));
		if (S == NULL) {
			printf("内存分配失败\n");
			exit(1);
		}
		S->adjvex = j;
		S->nextarc = G->vertices[i].firstarc;
		G->vertices[i].firstarc = S;
	}
}
void DFS(ALGraph G,int v,int visited[]) {
	ArcNode* w;
	visited[v] = 1;//标记当前顶点已被访问
	printf("%3d", G.vertices[v].data);
	//递归遍历未访问的邻接点
	for (w = G.vertices[v].firstarc; w != NULL; w = w->nextarc) {
		if (w->adjvex >= 0 && w->adjvex < G.vexnum && !visited[w->adjvex]) {
			DFS(G, w->adjvex, visited);//递归
		}
	}
}
void DFSGraph(ALGraph G) {
	int i;
	int visited[N] = { 0 };// 访问标记数组，初始化为 0（未访问）
	printf("\n深度优先遍历结果：\n");
	for (i = 0; i < G.vexnum; i++) {
		if (!visited[i]) {
			printf("从顶点 %d 出发的遍历路径: ", G.vertices[i].data);
			DFS(G, i, visited);
			printf("\n");
		}
	}
}
int OutputDegree(ALGraph G, int i) {
	ArcNode* p;
	int count = 0;
	if (i < G.vexnum && i >= 0) {
		for (p = G.vertices[i].firstarc; p != NULL; p = p->nextarc) {
			count++;
		}
	}
	else {
		printf("该顶点无效");
		return -1;
	}
	return count;
	
}
int InDegree(ALGraph G, int j) {
	ArcNode *v;
	int count2 = 0;
	int i = 0;
	if (j < G.vexnum && j >= 0) {
		for (i; i < G.vexnum; i++) {
			for (v = G.vertices[i].firstarc; v != NULL; v = v->nextarc) {
				if (v->adjvex==j) {
					count2++;
				}

			}

		}
	}
	else {
		printf("该顶点无效");
		return -1;
	}
	return count2;
}
int DeleteArc(ALGraph* G, int i, int j) {
	ArcNode* p = G->vertices[i].firstarc;
	ArcNode* q = NULL;//前驱
	while (p != NULL) {
		if (p->adjvex == j) {
			if (q != NULL) {
				q->nextarc = p->nextarc;
			}
			else {//当j为第一个邻接点时
				G->vertices[i].firstarc = p->nextarc;
			}
			free(p);
			printf("%d->%d的有向弧删除成功\n", i, j);
			return 1;
		}
		q = p, p = p->nextarc;
	}
	printf("不存在该弧");
	return 0;
}


