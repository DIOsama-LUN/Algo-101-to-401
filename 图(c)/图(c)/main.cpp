#include<stdio.h>
#include"graph.h"
#pragma warning(disable:4996)
int main() {
	ALGraph G;
	CreateDG(&G);
	int vex1,vex2;
	int result;
	printf("输入需删除的有向弧：（格式：i,j)");
	scanf("%d,%d", &vex1,&vex2);
	result= DeleteArc(&G, vex1, vex2);
	if (result==1) {
		printf("删除成功");
	}
	else {
		printf("删除失败");
	}
	return 0;
}