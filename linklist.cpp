#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>


//定义ElemType和Status
typedef int ElemType;
typedef bool Status;
#define OK true

// 第一单链表节点LNode
typedef struct LNode {
    int data;
    struct LNode *next;
}LNode, *LinkList;

//创建一个单链表
LNode *Create_LinkList(void) {
    int data; LNode *head, *p, *q;
    //创建头结点
    head = (LNode *)malloc(sizeof(LNode));
    head->next = NULL; q = head;

    int i = 0;
    while(i<10) {
        p = (LNode *)malloc(sizeof(LNode));
        p->data = rand() % 1000;
        q->next = p;
        p->next = NULL;
        q = p;
        i++;
    }
    return head;
}

//打印单链表中的所有数据
void Print_LinkList(LNode *h) {
    LNode *p = h->next;
    while (p) {
        printf("%d",p->data);
        if (p->next != NULL) {
            printf("->");
        }
        p = p->next;
    }
    printf("\n");
}

//读入一个整数，查看该整数是否在表中，若在，输出其位置(首位置为 1)，若不在，返回-1；
int Locate_LNode(LNode *h, int key) {
    LNode *p = h->next;
    int i = 1;// 从第 1 个数据结点开始数
    while (p && p->data != key) {
        p = p->next;
        i++;
    }
    if (p) return i;
    else return -1;
}

//读入一个整数，以及要插入的位置，把该整数插入到链表中，输出链表的内容,要求判断输入的位置是否合理
Status Insert_LNode(LNode *h, int key, int pos) {
    //判断输入的位置是否合理
    if (pos < 1) return ERROR;
    //移动到pos的上一个节点
    LNode *p = h;
    int i = 0;
    while (p && i < pos-1) {
        p = p->next;
        i++;
    }
    if (!p || i > pos-1) return ERROR;
    //创建并插入新节点
    LNode *q = (LNode *)malloc(sizeof(LNode));
    q->data = key;//注入数据
    q->next = p->next;
    p->next = q;
    return OK;
}

//读入一个整数，若该整数在链表里，删除该整数，输出链表的内容；若该证书不在链表中，返回-1
int Delete_LNode(LNode *h,int key) {
    //扫描，确定节点位置i
    int i = 1;
    LNode *p = h->next;
    while (p && p->data != key) {
        p = p->next;
        i++;
    };
    if (!p) return -1;
    //移动至i-1
    int j = 0;
    LNode *q = h;
    while (j < i-1) {
        q = q->next;
        j++;
    }
    //删除节点
    q->next = p->next;
    free(p);
    return 1;

}

//把链表的内容翻转，输出链表的内容，要求不占用新的存储空间
Status Reverse_LinkList(LNode *h) {
    LNode *p = NULL;//已经处理好的节点
    LNode *q = h->next;//当下要处理的节点
    LNode *n = NULL;//下一个节点

    while (q){
        n = q->next;
        q->next = p;

        //p和q各前进一个节点
        p = q;
        q = n;
    }
    h->next = p;
    return OK;
}

//创建两个非递减的有序链表
LNode *Create_SortedList(void) {
    int data; LNode *head, *p, *q;
    //创建头结点
    head = (LNode *)malloc(sizeof(LNode));
    head->next = NULL; q = head;

    int i = 0;
    q->data = 0;
    while(i<10) {
        p = (LNode *)malloc(sizeof(LNode));
        p->data = q->data + rand() % 100;
        q->next = p;
        p->next = NULL;
        q = p;
        i++;
    }
    return head;
}

//将两个非递增的有序链表合并成一个非递增的有序链表，
//要求结果链表仍使用原来两个链表的存储空间，不占用其他的存储空间，表中允许有重复的数据
Status Merge_LinkLists(LNode *h1,LNode *h2) {
    //取第一个节点，默认合并后表的头指针为h1
    LNode *p1 = h1->next;
    LNode *p2 = h2->next;
    LNode *p3 = h1;

    //逐个比对选最大值
    while (p1 && p2) {
        if (p1->data >= p2->data) {
            p3->next = p1;
            p3 = p1;
            p1 = p1->next;
        }
        else {
            p3->next = p2;
            p3 = p2;
            p2 = p2->next;
        }
    }
    p3->next = p1 ? p1 : p2;//当两表节点数量并不完全相同时，把剩余节点挂在后面
    h2->next = NULL;
    return OK;
}

//main函数
int main() {
    SetConsoleOutputCP(65001);   // 65001 = UTF-8
    srand((unsigned)time(NULL)); //播种一次，暂不知原理
    LNode *head;
    head = Create_LinkList();

    //输出链表的内容
    Print_LinkList(head);

    //读入一个整数，查看该整数是否在表中，若在，输出其位置(首位置为 1)，若不在，返回-1
    int key, pos;
    printf("[Locate]int:");
    scanf("%d", &key);
    pos = Locate_LNode(head, key);
    if (pos == -1) {
        printf("%d不在表中！\n", key);
    }
    else {
        printf("%d在表中的位置为：%d\n", key, pos);
    }

    //读入一个整数，以及要插入的位置，把该整数插入到链表中，输出链表的内容,要求判断输入的位置是否合理
    bool Insert_is_OK;
    printf("[Insert]key:");
    scanf("%d", &key);
    printf("[Insert]pos:");
    scanf("%d", &pos);
    Insert_is_OK = Insert_LNode(head, key, pos);
    if (Insert_is_OK == ERROR) {
        printf("[Insert]ERROR\n");
    }
    Print_LinkList(head);

    //读入一个整数，若该整数在链表里，删除该整数，输出链表的内容；若该证书不在链表中，返回-1
    printf("[Delete]key:");
    scanf("%d", &key);
    int res = Delete_LNode(head, key);
    if (res == -1) {
        printf("[Delete]ERROR\n");
    }
    Print_LinkList(head);

    //把链表的内容翻转，输出链表的内容，要求不占用新的存储空间
    bool Reserve_is_OK;
    Reserve_is_OK = Reverse_LinkList(head);
    if (Reserve_is_OK == TRUE) Print_LinkList(head);
    else printf("[Reserve]ERROR");

    //创建并打印两个有序表
    LNode *S_head1 = Create_SortedList();
    printf("[SortedList1]");
    Print_LinkList(S_head1);

    LNode *S_head2 = Create_SortedList();
    printf("[SortedList2]");
    Print_LinkList(S_head2);

    //将两个非递减的有序链表合并成一个非递增的有序链表，
    //要求结果链表仍使用原来两个链表的存储空间，不占用其他的存储空间，表中允许有重复的数据

    //将两个非递减的有序链表翻转为两个非递增的有序链表
    Reserve_is_OK = Reverse_LinkList(S_head1);
    if (Reserve_is_OK == TRUE) {
        printf("[SortedList1]");
        Print_LinkList(S_head1);
    }
    else {
        printf("[SortedList1]");
        printf("[Reserve]ERROR");
    }

    Reserve_is_OK = Reverse_LinkList(S_head2);
    if (Reserve_is_OK == TRUE) {
        printf("[SortedList2]");
        Print_LinkList(S_head2);
    }
    else {
        printf("[SortedList2]");
        printf("[Reserve]ERROR");
    }

    //合并两个有序单链表
    bool Merge_is_OK = Merge_LinkLists(S_head1,S_head2);
    if (Merge_is_OK == OK) {
        printf("[MergeList]");
        Print_LinkList(S_head1);
    }


    return 0;
};
