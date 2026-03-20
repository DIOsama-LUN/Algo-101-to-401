#include"LinkQueue.h"
int InitQueue(LinkQueue* Q) {

	//构造链队列
	if (Q == NULL) return ERROR;
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (Q->front == NULL) {
		printf("头节点内存分配失败");
		return ERROR;
	}
	Q->front->next = NULL;
	Q->front->data = 0;
	printf("带头节点的链队列初始化成功！\n");
	return OK;
}
int DestroyQueue(LinkQueue* Q) {
	if (Q == NULL) {
		printf("入参Q为NULL，销毁失败！\n");
		return ERROR;
	}
	while (Q->front != NULL) {
		QueuePtr temp;
		temp = Q->front->next;
		Q->front = Q->front->next;
		if (temp == Q->rear) {
			Q->rear = NULL;
		}

		free(temp);
	}
	Q->front = Q->rear = NULL;

	printf("销毁成功！\n");

	
	return OK;
}
int enQueue(LinkQueue* Q, char e) {
	QueuePtr newNode = (QueuePtr)malloc(sizeof(QNode));
	if (newNode == NULL) return ERROR;
	newNode->data = e;
	newNode->next = NULL;
	Q->rear->next = newNode;
	Q->rear = newNode;
	return OK;

}
 

int deQueue(LinkQueue *Q,char *e){
	if (Q == NULL || e == NULL) {
		printf("入参Q或e为NULL，出队失败！\n");
		return ERROR;
	}
	if (QueueEmpty(Q)) {
		printf("队列为空，出队失败！\n");
		return ERROR;
	}
	QueuePtr temp = Q->front->next;
	*e = temp->data;
	Q->front->next = temp->next;
	if (Q->rear == temp) {  
		Q->rear = Q->front;
	}
	free(temp);
	return OK;
}
int QueueEmpty(LinkQueue* Q) {
	if (Q == NULL) {
		printf("入参Q为NULL \n");
		return FALSE; 
	}
	if (Q->front->next == NULL) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

