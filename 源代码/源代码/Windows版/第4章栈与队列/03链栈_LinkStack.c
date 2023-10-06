#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;
typedef int SElemType; /* SElemType类型根据实际情况而定，这里假设为int */

/* 链栈结构 */
typedef struct StackNode // StackNode结构包含一个data成员，其类型是SElemType。请注意，你需要在其他地方定义SElemType的类型（可能是int，float，char或其他类型）。
{
        SElemType data;
        struct StackNode *next; // next是一个指针，指向下一个StackNode结构的地址，形成链表结构。
} StackNode, *LinkStackPtr;     // LinkStackPtr是struct StackNode *的别名，用于方便地创建StackNode类型的指针。

typedef struct
{
        LinkStackPtr top; // top是一个指针，指向链栈顶部的StackNode。使用LinkStackPtr类型简化了指针的定义。
        int count;        // count记录了链栈中的元素数量。
} LinkStack;

Status visit(SElemType c)
{
        printf("%d ", c);
        return OK;
}

/*  构造一个空栈S */
Status InitStack(LinkStack *S)
{
        S->top = (LinkStackPtr)malloc(sizeof(StackNode));
        if (!S->top)
                return ERROR;
        S->top = NULL;
        S->count = 0;
        return OK;
}

/* 把S置为空栈 */
Status ClearStack(LinkStack *S)
{
        LinkStackPtr p, q;
        p = S->top;
        while (p)
        {
                q = p;
                p = p->next;
                free(q);
        }
        S->count = 0;
        return OK;
}

/* 若栈S为空栈，则返回TRUE，否则返回FALSE */
Status StackEmpty(LinkStack S)
{
        if (S.count == 0)
                return TRUE;
        else
                return FALSE;
}

/* 返回S的元素个数，即栈的长度 */
int StackLength(LinkStack S)
{
        return S.count;
}

/* 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR */
Status GetTop(LinkStack S, SElemType *e)
{
        if (S.top == NULL)
                return ERROR;
        else
                *e = S.top->data;
        return OK;
}

/* 插入元素e为新的栈顶元素 */
Status Push(LinkStack *S, SElemType e)
{
        LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));               // 使用 malloc 函数动态分配一块内存来存储新的 StackNode，并将其地址赋值给指针 s。注意，malloc 返回的是 void * 类型的指针，所以需要将其强制类型转换为 LinkStackPtr。
        s->data = e;                                                            // 将传入的元素 e 的值赋值给新节点 s 的 data 成员。
        s->next = S->top; /* 把当前的栈顶元素赋值给新结点的直接后继，见图中① */ // 即设置新节点 s 的 next 指针指向当前的栈顶元素。这样，新节点 s 就成了链表中的第一个节点。
        S->top = s; /* 将新的结点s赋值给栈顶指针，见图中② */                    // 即更新栈 S 的 top 指针，使其指向新插入的节点 s。
        S->count++;
        return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(LinkStack *S, SElemType *e)
{
        LinkStackPtr p;
        if (StackEmpty(*S)) // 首先检查栈是否为空，如果为空则返回ERROR。
                return ERROR;
        *e = S->top->data;                           // 如果栈不空，函数将栈顶元素的data赋值给*e。
        p = S->top; /* 将栈顶结点赋值给p，见图中③ */ // 注意！在Pop()函数中，将栈顶节点赋值给p是为了在更新栈顶指针S->top之后，能正确地释放原栈顶节点的内存。当S->top更新后，如果不将原栈顶节点的地址保存在另一个变量中（在这里是p），我们将无法访问并正确释放这个节点的内存，从而可能导致内存泄漏。
        S->top = S->top->next;                       /* 使得栈顶指针下移一位，指向后一结点，见图中④ */
        free(p);                                     /* 释放结点p */
        S->count--;
        return OK;
}

Status StackTraverse(LinkStack S)
{
        LinkStackPtr p;
        p = S.top;
        while (p)
        {
                visit(p->data);
                p = p->next;
        }
        printf("\n");
        return OK;
}

int main()
{
        int j;
        LinkStack s;
        int e;
        if (InitStack(&s) == OK)
                for (j = 1; j <= 10; j++)
                        Push(&s, j);
        printf("栈中元素依次为：");
        StackTraverse(s);
        Pop(&s, &e);
        printf("弹出的栈顶元素 e=%d\n", e);
        printf("栈空否：%d(1:空 0:否)\n", StackEmpty(s));
        GetTop(s, &e);
        printf("栈顶元素 e=%d 栈的长度为%d\n", e, StackLength(s));
        ClearStack(&s);
        printf("清空栈后，栈空否：%d(1:空 0:否)\n", StackEmpty(s));
        return 0;
}