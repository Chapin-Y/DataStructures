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
        i++;
    }
    if (!p) return false;//位置越界
    auto s = new LNode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

//用随机函数生成 10 个 3 位整数(100~999)，把这些整数存于单链表中
Status InsertLNodes(LinkList &L) {
    char e[6] = {'(', ')', '[', ']', '{', '}'};
    int i = 0;
    int k;//0~5随机
    while (i < 10) {
        k = rand() %6;
        ListInsert(L, 1, e[k]);
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

//编写判别给定表达式中所含括号是否正确配对出现的算法，如果是合法嵌套则返回为 true，如果是不符合法嵌套则返回为 false。
//增加对非括号字符的判断.
Status Check_LinkList(LinkList &L) {
    LNode *p = L->next;
    char stack[256]; int top = -1;//顺序栈，存已读入的左括号
    while (p) {
        char c = p->data;
        if (c == '(' || c == '[' || c == '{') {
            stack[++top] = c;//左括号：入栈等待配对
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (top == -1) return false;//栈空，右括号无左括号可配
            char e = stack[top--];//弹出栈顶左括号
            if ((c == ')' && e != '(') ||
                (c == ']' && e != '[') ||
                (c == '}' && e != '{')) {
                return false;//左右括号类型不匹配
            }
        }
        //非括号字符：跳过，不做处理
        p = p->next;
    }
    return top == -1;//栈空说明左括号全部配对，否则有剩余左括号
}

//读入一个表达式字符串（可含非括号字符），存于单链表中
Status Read_Expression(LinkList &L) {
    char str[256];
    printf("[Expression]请输入表达式:");
    scanf("%255s", str);
    printf("\n");
    //清空原链表
    LNode *p = L->next;
    while (p) {
        LNode *q = p;
        p = p->next;
        delete q;
    }
    L->next = NULL;
    //逐字符尾插入表
    int i = 0;
    while (str[i] != '\0') {
        ListInsert(L, i + 1, str[i]);
        i++;
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
    if (Check_LinkList(L)) printf("[Check_LinkList]true\n");
    else printf("[Check_LinkList]false\n");

    //读入给定表达式（可含非括号字符），判别括号是否正确配对
    if (Read_Expression(L) == OK) printf("[Read_Expression]Successed\n");
    Print_LinkList(L);
    if (Check_LinkList(L)) printf("[Check_LinkList]true\n");
    else printf("[Check_LinkList]false\n");

    return 0;
}