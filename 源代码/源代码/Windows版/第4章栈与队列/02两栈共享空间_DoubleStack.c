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

/* 两栈共享空间结构 */
typedef struct
{
        SElemType data[MAXSIZE];
        int top1; /* 栈1栈顶指针 */
        int top2; /* 栈2栈顶指针 */
} SqDoubleStack;

Status visit(SElemType c)
{
        printf("%d ", c);
        return OK;
}

/*  构造一个空栈S */
Status InitStack(SqDoubleStack *S)
{
        S->top1 = -1;
        S->top2 = MAXSIZE;
        return OK;
}

/* 把S置为空栈 */
Status ClearStack(SqDoubleStack *S)
{
        S->top1 = -1;
        S->top2 = MAXSIZE;
        return OK;
}

/* 若栈S为空栈，则返回TRUE，否则返回FALSE */
Status StackEmpty(SqDoubleStack S)
{
        if (S.top1 == -1 && S.top2 == MAXSIZE)
                return TRUE;
        else
                return FALSE;
}

/* 返回S的元素个数，即栈的长度 */
int StackLength(SqDoubleStack S)
{
        return (S.top1 + 1) + (MAXSIZE - S.top2);
}

/* 插入元素e为新的栈顶元素 */
Status Push(SqDoubleStack *S, SElemType e, int stackNumber)
{
        if (S->top1 + 1 == S->top2) /* 栈已满，不能再push新元素了 */
                return ERROR;
        if (stackNumber == 1)                                                     /* 栈1有元素进栈 */
                S->data[++S->top1] = e; /* 若是栈1则先top1+1后给数组元素赋值。 */ // 改写成S->data[S->top1++]也没问题。
        else if (stackNumber == 2)                                                /* 栈2有元素进栈 */
                S->data[--S->top2] = e;                                           /* 若是栈2则先top2-1后给数组元素赋值。 */
        return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(SqDoubleStack *S, SElemType *e, int stackNumber)
{
        if (stackNumber == 1)
        {
                if (S->top1 == -1)
                        return ERROR;                              /* 说明栈1已经是空栈，溢出 */
                *e = S->data[S->top1--]; /* 将栈1的栈顶元素出栈 */ // 注意！这里把我绕进去了。他这里的写法是对的。在这种写法中，首先将 S->top1 所指向的栈顶元素（在top1位置，而不是top1 – 1位置）的值赋给 e，然后再将 S->top1 减一，表示出栈操作。这种写法的好处是可以在一行代码中完成出栈操作，但需要注意的是 e 变量会保存出栈前的栈顶元素的值。
                // 其次，我想写成两行*e = S->data[S->top1]; S->top1--; 这种写法也是对的。这种写法将操作分为两行，更容易理解和阅读。你可以在第一行获取栈顶元素的值，然后在第二行更新栈顶指针。
        }
        else if (stackNumber == 2)
        {
                if (S->top2 == MAXSIZE)
                        return ERROR;    /* 说明栈2已经是空栈，溢出 */
                *e = S->data[S->top2++]; /* 将栈2的栈顶元素出栈 */
        }
        return OK;
}
/*
        插播Question：为什么
                *e = S->data[S->top1--];
                这种写法是正确的？
        答：我明白你的疑问。让我来详细解释一下 `*e = S->data[S->top1--];` 这种写法为什么也是正确的：

        1. `S->top1` 是栈1的栈顶指针。首先，它被用来访问栈1中的栈顶元素的值。

        2. `S->top1--` 部分表示先使用 `S->top1` 的值来访问栈1中的栈顶元素，然后再将 `S->top1`（这是说把S的top1成员的值减一） 减一。

        3. 在这个操作中，`S->top1` 的值被用于访问栈顶元素，然后才进行了减一的操作。这意味着 `S->top1` 在访问栈顶元素之前仍然是指向当前栈顶元素的位置。

        4. `*e = S->data[S->top1--];` 这一行的作用是将栈1的栈顶元素的值赋给 `e`，然后再将 `S->top1` 减一，以表示栈顶元素已经出栈。

        所以，虽然这一行代码是合并了访问栈顶元素和减少栈顶指针的操作，但由于 `S->top1` 的值在访问元素之前被使用，所以它依然有效，能够正确地获取栈顶元素的值并更新栈顶指针。这是因为在 C 语言中，后缀 `--` 操作符表示先使用变量的值，然后再将变量减一。

        总之，`*e = S->data[S->top1--];` 这种写法是正确的，可以用来出栈并获取栈顶元素的值。

        注意！*e = S->data[S->top1--];这里使用了后减操作（post-decrement）。首先，S->data[S->top1]的值被获取并赋值给*e，然后S->top1减1。在这个操作过程中，你是在获取S->top1当前指向的元素，并且在获取后top1减1。

        *e = S->data[S->--top1];这里使用了前减操作（pre-decrement）。首先，S->top1减1，然后S->data[S->top1]的值被获取并赋值给*e。在这个操作过程中，你实际上获取的是S->top1 - 1位置的元素。
        举一个实际的例子来帮助理解：

        假设S->top1初始值为5。

        对于*e = S->data[S->top1--];:

        *e被赋值为S->data[5]，然后S->top1变为4。
        对于*e = S->data[S->--top1];:

        S->top1首先变为4，然后*e被赋值为S->data[4]。
        所以，这两个代码段访问的是不同的数组元素。确保你了解这个区别，并根据你的具体需求选择正确的操作。
*/

Status StackTraverse(SqDoubleStack S)
{
        int i;
        i = 0;
        while (i <= S.top1)
        {
                visit(S.data[i++]);
        }
        i = S.top2;
        while (i < MAXSIZE)
        {
                visit(S.data[i++]);
        }
        printf("\n");
        return OK;
}

int main()
{
        int j;
        SqDoubleStack s;
        int e;
        if (InitStack(&s) == OK)
        {
                for (j = 1; j <= 5; j++)
                        Push(&s, j, 1);
                for (j = MAXSIZE; j >= MAXSIZE - 2; j--)
                        Push(&s, j, 2);
        }

        printf("栈中元素依次为：");
        StackTraverse(s);

        printf("当前栈中元素有：%d \n", StackLength(s));

        Pop(&s, &e, 2);
        printf("弹出的栈顶元素 e=%d\n", e);
        printf("栈空否：%d(1:空 0:否)\n", StackEmpty(s));

        for (j = 6; j <= MAXSIZE - 2; j++)
                Push(&s, j, 1);

        printf("栈中元素依次为：");
        StackTraverse(s);

        printf("栈满否：%d(1:否 0:满)\n", Push(&s, 100, 1));

        ClearStack(&s);
        printf("清空栈后，栈空否：%d(1:空 0:否)\n", StackEmpty(s));

        return 0;
}