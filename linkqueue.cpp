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

//定义一个栈，用于翻转队列时临时存储节点
typedef struct SNode {
    ElemType data;
    struct SNode *next;
}SNode, *LinkStack;

//链队的初始化
Status InitQueue(LinkQueue &Q) {
    Q.front = Q.rear = new QNode;
    Q.front->next = NULL;
    return OK;
}

//入队
Status EnQueue(LinkQueue &Q, ElemType e) {
    if (e == -1) return ERROR;
    auto *p = new QNode;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;//Q.rear->next表示队尾指针指向节点的指针
    Q.rear = p;
    return OK;
}

//出队，修改：返回为删除节点的data
ElemType DeQueue(LinkQueue &Q) {
    ElemType e;
    if (Q.rear == Q.front) return -1;
    auto *p = new QNode;
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p) Q.rear = Q.front;//删到最后一个节点
    delete p;
    return e;
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

//创建栈用于临时存储队列内容
Status Init_LinkStack(LinkStack &S) {
    S = NULL;
    return OK;
}

//入栈
Status Push_LinkStack(LinkStack &S, ElemType e) {
    if (e == -1) return ERROR;
    auto *p = new SNode;
    p->data = e;
    p->next = S;
    S = p;
    return OK;
}

//出栈，输出删除节点data
ElemType Pop_LinkStack(LinkStack &S) {
    auto *p = new SNode;
    if (S == NULL) return -1;
    ElemType e = S->data;
    p = S;
    S = p->next;
    delete p;
    return e;
}

//把队列的内容翻转
void Reverse_LinkQueue(LinkQueue &Q, LinkStack &S) {
    //定义节点用于临时存储数据
    auto *p = new QNode;
    auto *q = new SNode;

    bool Push_is_OK;
    bool En_is_OK;

    //逐一出队并入栈
    ElemType e;
    while (e != -1) {
        e = DeQueue(Q);
        Push_is_OK = Push_LinkStack(S, e);
        if (Push_is_OK != OK) printf("[Push]ERROR\n");
    }

    e = 0;//重置取值

    //逐一出栈并入队
    while (e != -1) {
        e = Pop_LinkStack(S);
        En_is_OK = EnQueue(Q, e);
    }


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

    //把队列的内容翻转，应用出队操作输出队列的内容

    //创建一个栈
    LinkStack S = NULL;
    bool Init_is_OK;
    Init_is_OK = Init_LinkStack(S);
    if (Init_is_OK != OK) {
        printf("[InitStack]ERROR");
    }

    //翻转并入栈
    Reverse_LinkQueue(Q,S);
    Print_LinkQueue(Q);


    return  0;
}