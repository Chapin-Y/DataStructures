//
// Created by Oblivion on 2026/11/9.
//

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <windows.h>

//定义ElemType和Status
typedef char ElemType;
typedef bool Status;
#define OK true

//定义单链表节点
typedef struct LNode {
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

//初始化单链表
Status Init_LinkList(LinkList &L) {
    L = new LNode;
    L->next = NULL;
    return OK;
}

//插入节点
Status ListInsert(LinkList &L, int idx, ElemType e) {
    auto *p = L;int i = 0;
    while (p && i < idx - 1) {
        p = p->next;
        idx++;
    }
    auto s = new LNode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

//用随机函数生成 10 个 3 位整数(100~999)，把这些整数存于单链表中
Status InsertLNodes(LinkList &L) {
    char e[6] = {'(', ')', '[', ']', '{', '}'};
    char s;
    int i = 0;
    int k;//0~5随机
    while (i < 10) {
        k = rand() %6;
        s = e[k];
        ListInsert(L, 1, s);
        i++;
    }
    return OK;
}

//打印单链表
void Print_LinkList(LinkList &L) {
    LNode *p = L->next;
    printf("[LinkList]");
    while (p) {
        printf("%c",p->data);
        if (p->next != NULL) {
            printf(" ");
        }
        p = p->next;
    }
    printf("\n");
}

//读入一个整数，以该值为基准把单链表分割为两部分，所有小于该值的结点排在大于或等于该值的结点之前
Status Partition_LinkList(LinkList &L) {
    int e = 0;
    printf("[Partition]请读入一个整数:");
    scanf("%d",&e);
    printf("\n");

    if (L->next == NULL) return OK;

    LNode *p = L;
    LNode *q;//双指针遍历
    while (p->next != NULL) {
        q = p->next;
        if (q->data < e && p != L) { // 小于基准且不在头部，才搬
            //头插法
            p->next = q->next;
            q->next = L->next;
            L->next = q;
        }
        else p = p->next;  // 不搬才前进，防止跳过节点
    }
    return OK;
}

int main() {
    SetConsoleOutputCP(65001);   // 65001 = UTF-8
    srand((unsigned)time(NULL)); //播种一次，暂不知原理

    //创建并初始化单链表
    LinkList L;
    if (Init_LinkList(L) == OK) printf("[Init_LinkList]Successed\n");

    //在单链表中插入包含六种字符的节点10个
    if (InsertLNodes(L) == OK) printf("[Insert10LNode]Successed\n");
    Print_LinkList(L);

    return 0;
}