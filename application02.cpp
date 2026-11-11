//
// Created by Oblivion on 2026/11/11.
//

#include <cstdio>
#include <numbers>
#include <windows.h>
//定义ElemType和Status
typedef char ElemType;
typedef bool Status;
#define OK true

//定义栈的节点
typedef struct SNode {
    ElemType data;
    struct SNode *next;
}SNode, *LinkStack;

//初始化
Status InitStack(LinkStack &S) {
    S = NULL;
    return OK;
}

//入栈
Status EnStack (LinkStack &S, ElemType &c) {
    char st[] = "[]{}()";
    if (strchr(st, c) == NULL) return ERROR;
    auto *p = new SNode;
    p->data = c;
    p->next = S;
    S = p;
    return OK;
}

//字符匹配
char Change_Char(LinkStack &S, ElemType &c) {
    char st[] = "[]{}()";
    if (strchr(st, c) == NULL) return ERROR;
    if (c == ')')  return '(';
    if (c == ']')  return '[';
    if (c == '}')  return '{';
    return ERROR;
}

//出栈
char DeStack (LinkStack &S) {
    SNode *p = S;
    char e = p->data;
    S = p->next;
    delete p;
    return e;
}

int main() {
    SetConsoleOutputCP(65001);

    //读入字符串
    char e[100] = "";
    printf("请读入一个字符串: ");
    scanf("%99s", e);
    printf("%s\n", e);

    //创建并初始化栈
    LinkStack S1;//用于存放原字符串
    if (InitStack(S1) != OK) printf("[InitStack]:ERROR");

    LinkStack S2;//用于消除和存放匹配字符
    if (InitStack(S2) != OK) printf("[InitStack]:ERROR");

    //将e中的字符插入到栈中
    int i = 0;
    while (i < strlen(e)) {
        if (EnStack(S1, e[i]) != OK) printf("[EnStack]ERROR key:%c\n", e[i]);
        i++;
    };

    i = 0;

    //出栈及匹配
    while (S1 != NULL) {
        //出栈
        char c = DeStack(S1);
        printf("%c S1出栈成功\n", c);

        //先匹配
        SNode *p = S2;
        if (p != NULL && p->data == c) {
            printf("%c在S2中存在\n", c);
            DeStack(S2);
            printf("%c S2出栈成功\n", c);
        }
        else {
            char r = Change_Char(S1, c);
            if (r != ERROR) printf("%c 匹配 %c\n", c, r);
            else printf("%c 跳过\n", c);
            EnStack(S2, r);
        }
    }

    if (S1 == NULL && S2 == NULL) {
        printf("是合法嵌套\n");
        return TRUE;
    }
    else {
        printf("不是合法嵌套\n");
        return FALSE;
    }

    return 0;
}

