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

/* 顺序栈结构 */
typedef struct
{
        SElemType data[MAXSIZE];
        int top; /* 用于栈顶指针 */
} SqStack;

Status visit(SElemType c)
{
        printf("%d ", c);
        return OK;
}

/*  构造一个空栈S */
Status InitStack(SqStack *S)
{
        /* S.data=(SElemType *)malloc(MAXSIZE*sizeof(SElemType)); */
        S->top = -1;
        return OK;
}

/* 把S置为空栈 */
Status ClearStack(SqStack *S)
{
        S->top = -1;
        return OK;
}

/* 若栈S为空栈，则返回TRUE，否则返回FALSE */
Status StackEmpty(SqStack S)
{
        if (S.top == -1)
                return TRUE;
        else
                return FALSE;
}

/* 返回S的元素个数，即栈的长度 */
int StackLength(SqStack S)
{
        return S.top + 1;
}

/* 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR */
Status GetTop(SqStack S, SElemType *e)
{
        if (S.top == -1)
                return ERROR;
        else
                *e = S.data[S.top];
        return OK;
}

/* 插入元素e为新的栈顶元素 */
// 通常在进行入栈操作时，首先将栈顶指针 top 增加一个位置，然后再将新的元素赋值给新的栈顶位置。这是因为栈是一个后进先出（LIFO）的数据结构，最后入栈的元素应该成为栈顶元素。
Status Push(SqStack *S, SElemType e)
{
        if (S->top == MAXSIZE - 1) /* 栈满 */
        {
                return ERROR;
        }
        S->top++;                                             /* 栈顶指针增加一 */
        S->data[S->top] = e; /* 将新插入元素赋值给栈顶空间 */ // 注意！这里有点把我绕进去了。S->data是访问指针S所指向结构体的成员data，而[S->top]用来表示位序即List[Index]。只是这里的Index由S->top表示而已，top也是S指针所指向结构体的top成员，其值为一个int。我查了后认为这里写成S->data[S->top]或S->data[top]的效果应该是一致的，前提是你正确地维护了 top 变量，确保它总是指向栈中当前的栈顶元素位置，那么使用 S->data[top] 是有效的，因为它将访问栈顶元素。
        return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(SqStack *S, SElemType *e)
{
        if (S->top == -1)
                return ERROR;
        *e = S->data[S->top]; /* 将要删除的栈顶元素赋值给e */
        S->top--;             /* 栈顶指针减一 */
        return OK;
}

/* 从栈底到栈顶依次对栈中每个元素显示 */
Status StackTraverse(SqStack S)
{
        int i;
        i = 0;
        while (i <= S.top)
        {
                visit(S.data[i++]);
        }
        printf("\n");
        return OK;
}

int main()
{
        int j;
        SqStack s;
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
