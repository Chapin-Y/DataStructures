//
// Created by Oblivion on 2026/11/7.
//

#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>

//定义ElemType和Status
typedef int ElemType;
typedef bool Status;
#define OK true
#define ERROR false

//定义栈的节点
typedef struct SNode {
    ElemType data;
    struct SNode *next;
}SNode, *LinkStack;

//用随机函数生成 10 个 3 位整数(100~999)，把这些整数应用入栈操作存于堆栈中
SNode *Create_LinkStack(LinkStack &S) {
    int data; SNode *p, *q;
    int i = 0;
    while (i < 10) {
        p = new SNode;
        p->data = rand() % 900 + 100;
        p->next = S;
        S = p;
        i++;
    }
    return S;
}


//应用出栈操作输出堆栈的内容
Status Print_LinkStack(LinkStack &S) {
    SNode *p = NULL;
    int i = 0;
    printf("top");
    while (S != NULL) {
        int e = S->data;
        p = S;
        printf("-> %d", e);
        S = S->next;
        delete p;
    }
    printf("-> NULL");
    return OK;
}

//main函数
int main() {
    SetConsoleOutputCP(65001);   // 65001 = UTF-8
    srand((unsigned)time(NULL)); //播种一次，暂不知原理

    //用随机函数生成 10 个 3 位整数(100~999)，把这些整数应用入栈操作存于堆栈中
    LinkStack S = NULL;
    Create_LinkStack(S);

    //应用出栈操作输出堆栈的内容
    Print_LinkStack(S);

    return 0;
}