#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
typedef int Status;     
typedef int QElemType;  


typedef struct QNode {
	char  data;
	struct QNode* next;

}QNode,*QueuePtr;
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
Status InitQueue(LinkQueue *Q);
Status DestroyQueue(LinkQueue* Q);
Status QueueEmpty(LinkQueue* Q);
Status enQueue(LinkQueue* Q, char e);
Status deQueue(LinkQueue* Q, char* e);

#endif