#include "string.h"
#include "ctype.h"

#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000 /* 存储空间初始分配量 */

typedef int Status;    /* Status???????????,???????????????????OK?? */
typedef char ElemType; /* ElemType???????????????????????????char */

Status visit(ElemType c)
{
    printf("%c ", c);
    return OK;
}

/* 线性表的静态链表存储结构 */
typedef struct
{
    ElemType data;
    int cur; /* 游标(Cursor)，为0时表示无指向 */
} Component, StaticLinkList[MAXSIZE];

/* ????????space?????????????????????????space[0].cur?????"0"???????? */
Status InitList(StaticLinkList space)
{
    int i;
    for (i = 0; i < MAXSIZE - 1; i++)
        space[i].cur = i + 1;
    space[MAXSIZE - 1].cur = 0; /* ???????????????????????cur?0 */
    return OK;
}

/* 若备用空间链表非空，则返回分配的结点下标，否则返回0 */
int Malloc_SSL(StaticLinkList space)
{
    int i = space[0].cur; /* 当前数组的第一个元素的cur的值 */
    /* 就是要返回的第一个备用空闲的下标 */
    // B/c在静态链表中，通常使用第一个元素来维护备用空闲节点链表。这个第一个元素的cur属性存储了下一个可用的备用节点的下标。如果 space[0].cur 的值为0，则可以理解整个链表为空。在这个上下文中，space[0] 通常表示链表的头部或第一个节点，而它的 cur 属性用于指向下一个可用的备用节点。如果 cur 为0，意味着没有下一个备用节点，这通常意味着链表中没有节点被分配，链表是空的。
    // if (space[0].cur) 是一个条件判断语句，它的作用是判断 space[0].cur 的值是否为真（非零）或假（零）。具体来说，它的判断方式如下：如果 space[0].cur 的值为零，那么条件判断为假，代码块中的语句将被跳过。如果 space[0].cur 的值为非零，那么条件判断为真，代码块中的语句将被执行。
    if (space[0].cur)
        space[0].cur = space[i].cur; /* 由于要拿出一个分量来使用了 */
                                     /* 所以我们就得把它的下一个 */
                                     /* 分量用来做备用 */
    return i;
}

/*  把下标为k的空闲结点回收到备用链表 */
void Free_SSL(StaticLinkList space, int k)
{
    space[k].cur = space[0].cur; /* 把第一个元素的cur值赋值给要删除的分量cur */ // 本来第0位元素的cur是指向下一个空闲结点的，现在第一位元素空闲出来了，就把这个空闲出来的第一位元素作为了下一个空闲结点。把第0位元素的cur指向的位置赋给 第一位元素的cur，让第一位元素的cur来指向那个结点。这是为了下一行代码做准备。
    space[0].cur = k; /* 把要删除的分量下标赋值给第一个元素的cur */             // 把 第一位元素的位置 作为值赋给第0位元素的cur，来满足由第0位元素的cur指向下一个空闲结点的要求。
}

/* 初始条件：静态链表L已存在。操作结果：返回L中数据元素的个数。 */ // 注意！统计的元素个数指的是存储了数据的元素的数量，而不是备用链表中的元素数量。
int ListLength(StaticLinkList L)
{
    int j = 0;
    int i = L[MAXSIZE - 1].cur;
    while (i)
    {
        i = L[i].cur;
        j++;
    } // 这其实是由统计循环进行次数来统计元素个数的。
    return j;
}

/*  ??L????i?????????????????????e   */
Status ListInsert(StaticLinkList L, int i, ElemType e)
{
    int j, k, l;
    k = MAXSIZE - 1; /* 注意k首先是最后一个元素的下标 */
    if (i < 1 || i > ListLength(L) + 1)
        return ERROR;
    j = Malloc_SSL(L); /* 获得空闲分量的下标 */
    if (j)
    {
        L[j].data = e;               /* 将数据赋值给此分量的data */
        for (l = 1; l <= i - 1; l++) /* 找到第i个元素之前的位置 */
            k = L[k].cur;
        L[j].cur = L[k].cur; /* 把第i个元素之前的cur赋值给新元素的cur */
        L[k].cur = j;        /* 把新元素的下标赋值给第i个元素之前元素的cur */
        return OK;
    }
    return ERROR;
}

/*  删除在L中第i个数据元素   */ // 仔细体会这个第i个，这其实是隐含了List中首个元素为第0个（虽然这个元素不储存数据）
Status ListDelete(StaticLinkList L, int i)
{
    int j, k;
    if (i < 1 || i > ListLength(L))
        return ERROR;
    k = MAXSIZE - 1;
    for (j = 1; j <= i - 1; j++)
        k = L[k].cur;    // 注意！体会这里。如果是想删除元素甲所在元素（第1个元素），这个for loop会被直接跳过。
    j = L[k].cur;        // 这是把要删除元素的 位置 （即第一个元素的 位置 为1）赋给j。
    L[k].cur = L[j].cur; // 这其实就是把 把要删除元素的 cur （即第一个元素的 cur 为2）赋给 指向要删除元素 的元素 的cur，在本例中是把2 赋给第999位元素的cur。Consequently 第999位元素的cur变为2。实现了删除了 元素甲。
    Free_SSL(L, j);
    return OK;
}

Status ListTraverse(StaticLinkList L)
{
    int j = 0;
    int i = L[MAXSIZE - 1].cur;
    while (i)
    {
        visit(L[i].data);
        i = L[i].cur;
        j++;
    }
    return j;
    printf("\n");
    return OK;
}

int main()
{
    StaticLinkList L;
    Status i;
    i = InitList(L);
    printf("?????L??L.length=%d\n", ListLength(L));

    i = ListInsert(L, 1, 'F');
    i = ListInsert(L, 1, 'E');
    i = ListInsert(L, 1, 'D');
    i = ListInsert(L, 1, 'B');
    i = ListInsert(L, 1, 'A');

    printf("\n??L????????????FEDBA??\nL.data=");
    ListTraverse(L);

    i = ListInsert(L, 3, 'C');
    printf("\n??L???B????D????????C????\nL.data=");
    ListTraverse(L);

    i = ListDelete(L, 1);
    printf("\n??L???????A????\nL.data=");
    ListTraverse(L);

    printf("\n");

    return 0;
}
