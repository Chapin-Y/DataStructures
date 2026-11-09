//
// Created by Oblivion on 2026/11/9.
//

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <windows.h>

//定义ElemType和Status
typedef int ElemType;
typedef bool Status;
#define OK true

//定义节点
typedef struct QNode {
    ElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

//定义队头指针与队尾指针
typedef struct {
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

//链队的初始化
Status InitQueue(LinkQueue &Q) {
    Q.front = Q.rear = new QNode;
    Q.front->next = NULL;
    return OK;
}

//入队
Status EnQueue(LinkQueue &Q, ElemType e) {
    auto *p = new QNode;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;//Q.rear->next表示队尾指针指向节点的指针
    Q.rear = p;
    return OK;
}

//应用遍历操作输出队列的内容
void Print_LinkQueue(LinkQueue &Q) {
    auto *p = new QNode;
    p = Q.front->next;
    printf("Front");
    while (p) {
        printf("->%d", p->data);
        p = p->next;
    }
    printf("->NULL\n");
}

//main函数
int main() {
    SetConsoleOutputCP(65001);   // 65001 = UTF-8
    srand((unsigned)time(NULL)); //播种一次，暂不知原理

    //初始化，创建一个新的链队
    LinkQueue Q;
    InitQueue(Q);

    //用随机函数生成 10 个 3 位整数(100~999)，把这些整数应用入栈操作存于堆栈中
    int i = 0;
    while (i < 10) {
        int e = rand() % 900 + 100;
        bool EnQueue_is_OK = EnQueue(Q, e);
        if (EnQueue_is_OK != TRUE) {
            printf("[EnQueue]ERROR\n");
        }
        i++;
    }

    //应用遍历操作输出队列的内容
    Print_LinkQueue(Q);

    return  0;
}