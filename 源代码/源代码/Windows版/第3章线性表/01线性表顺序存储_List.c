
#include "stdio.h"

#include "stdlib.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20    /* 存储空间初始分配量 */
typedef int ElemType; /* ElemType类型根据实际情况而定，这里假设为int */
typedef struct
{
    ElemType data[MAXSIZE]; /* 数组，存储数据元素 */ // 注意！别误解，这里的data[X]格式就代表了data是个数组Array。这个结构体SqList有两个成员，data和length。
    int length; /* 线性表当前长度 */                 // length 不包含 data 中尚未使用或未初始化的位置。length 变量表示 data 数组中当前已使用或已赋值的元素数量。当 SqList 结构体刚被初始化并且没有元素被加入到 data 时，length 应该是 0。如果你向 data 中添加一个元素，length 应该增加 1，表示 data 的长度增加了。当你继续向 data 添加元素时，每添加一个元素，length 就增加 1。length 的目的是告诉你 data 数组中有多少元素是已赋值或已使用的。这样，你可以确保在访问 data 时不会超出其已使用的部分，从而避免访问未定义的值。所以，length仅表示 data 数组中已经赋值或已使用的元素的数量，而不包括尚未使用的空位置。

} SqList;

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */

Status visit(ElemType c)
{
    printf("%d ", c);
    return OK;
}

/* 初始化顺序线性表 */
Status InitList(SqList *L)
{
    L->length = 0;
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(SqList L)
{
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(SqList *L)
{
    L->length = 0;
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(SqList L)
{
    return L.length;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值,注意i是指位置，第1个位置的数组是从0开始 */
Status GetElem(SqList L, int i, ElemType *e)
{
    if (L.length == 0 || i < 1 || i > L.length)
        return ERROR;
    *e = L.data[i - 1];

    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
int LocateElem(SqList L, ElemType e)
{
    int i;
    if (L.length == 0)
        return 0;
    for (i = 0; i < L.length; i++)
    {
        if (L.data[i] == e)
            break;
    }
    if (i >= L.length)
        return 0;

    return i + 1;
}

/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(SqList *L, int i, ElemType e)
{
    int k;
    if (L->length == MAXSIZE) /* 顺序线性表已经满 */
        return ERROR;
    if (i < 1 || i > L->length + 1) /* 当i比第一位置小或者比最后一位置后一位置还要大时 */
        return ERROR;

    if (i <= L->length) /* 若插入数据位置不在表尾 */
    {
        for (k = L->length - 1; k >= i - 1; k--) /* 将要插入位置之后的数据元素向后移动一位 */
            L->data[k + 1] = L->data[k];
    }
    L->data[i - 1] = e; /* 将新元素插入 */
    L->length++;

    return OK;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(SqList *L, int i, ElemType *e)
{
    int k;
    if (L->length == 0) /* 线性表为空 */
        return ERROR;
    if (i < 1 || i > L->length) /* 删除位置不正确 */
        return ERROR;
    *e = L->data[i - 1];
    if (i < L->length) /* 如果删除不是最后位置 */
    {
        for (k = i; k < L->length; k++) /* 将删除位置后继元素前移 */
            L->data[k - 1] = L->data[k];
    } // 如果删除最后一个元素,则不执行 for 循环，L->length 被减少 1，通过减少 L->length 的值来更新线性表的逻辑长度，L->data 数组的物理空间没有改变，也没有真正的删除操作发生在物理层面。
    L->length--;
    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(SqList L)
{
    int i;
    for (i = 0; i < L.length; i++)
        visit(L.data[i]);
    printf("\n");
    return OK;
}

/*将所有的在线性表Lb中但不在La中的数据元素插入到La中*/
void unionL(SqList *La, SqList Lb)
{
    int La_len, Lb_len, i;
    ElemType e;               /*声明与La和Lb相同的数据元素e*/
    La_len = ListLength(*La); /*求线性表的长度 */
    Lb_len = ListLength(Lb);
    for (i = 1; i <= Lb_len; i++)
    {
        GetElem(Lb, i, &e);                       /*取Lb中第i个数据元素赋给e*/
        if (!LocateElem(*La, e))                  /*La中不存在和e相同数据元素*/
            ListInsert(La, ++La_len, e); /*插入*/ // 注意！这里的ListInsert function的签名要求了第一个变量是指针变量，所以这里用的是La这个指针变量作为输入变量。
    }
}

int main()
{

    SqList L;
    SqList Lb;

    ElemType e;
    Status i;
    int j, k;
    i = InitList(&L);
    printf("初始化L后：L.length=%d\n", L.length);
    for (j = 1; j <= 5; j++)
        i = ListInsert(&L, 1, j);
    printf("在L的表头依次插入1～5后：L.data=");
    ListTraverse(L);

    printf("L.length=%d \n", L.length);
    i = ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n", i);

    i = ClearList(&L);
    printf("清空L后：L.length=%d\n", L.length);
    i = ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n", i);

    for (j = 1; j <= 10; j++)
        ListInsert(&L, j, j);
    printf("在L的表尾依次插入1～10后：L.data=");
    ListTraverse(L);

    printf("L.length=%d \n", L.length);

    ListInsert(&L, 1, 0);
    printf("在L的表头插入0后：L.data=");
    ListTraverse(L);
    printf("L.length=%d \n", L.length);

    GetElem(L, 5, &e);
    printf("第5个元素的值为：%d\n", e);
    for (j = 3; j <= 4; j++)
    {
        k = LocateElem(L, j);
        if (k)
            printf("第%d个元素的值为%d\n", k, j);
        else
            printf("没有值为%d的元素\n", j);
    }

    k = ListLength(L); /* k为表长 */
    for (j = k + 1; j >= k; j--)
    {
        i = ListDelete(&L, j, &e); /* 删除第j个数据 */
        if (i == ERROR)
            printf("删除第%d个数据失败\n", j);
        else
            printf("删除第%d个的元素值为：%d\n", j, e);
    }
    printf("依次输出L的元素：");
    ListTraverse(L);

    j = 5;
    ListDelete(&L, j, &e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为：%d\n", j, e);

    printf("依次输出L的元素：");
    ListTraverse(L);

    // 构造一个有10个数的Lb
    i = InitList(&Lb);
    for (j = 6; j <= 15; j++)
        i = ListInsert(&Lb, 1, j);

    unionL(&L, Lb);

    printf("依次输出合并了Lb的L的元素：");
    ListTraverse(L);

    return 0;
}
