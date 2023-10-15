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

typedef int QElemType; /* QElemType类型根据实际情况而定，这里假设为int */

typedef struct QNode /* 结点结构 */ // 这开始定义一个名为 QNode 的结构体，它表示队列的一个节点。在这个结构体中，有两个成员。
{
	QElemType data;		// data：这是队列元素的数据部分，其类型为 QElemType，也就是 int。
	struct QNode *next; // next：这是一个指向下一个节点的指针，也是 QNode 类型的。
} QNode, *QueuePtr;		// QNode：表示队列节点的类型。QueuePtr：表示指向队列节点的指针的类型。注意！这一行纯是用来定义别名的。在这个 typedef 语句中，QNode 是 struct QNode 的别名，用于简化后续的代码写法。而 *QueuePtr 的部分，它是定义了一个新的别名 QueuePtr，这个别名代表的是一个指向 QNode 的指针。换句话说，QueuePtr 是 QNode* 的别名。这样做的目的是为了进一步简化代码。例如，如果你想声明一个指向 QNode 结构体的指针，你可以有以下两种方式：使用原始的写法：QNode* pointer1; 使用 QueuePtr 这个别名：QueuePtr pointer2;这两个声明是等价的。使用 QueuePtr 可以使代码更简洁，并更清晰地表示这是一个指向队列节点的指针。

typedef struct /* 队列的链表结构 */
{
	QueuePtr front, rear; /* 队头、队尾指针 */
} LinkQueue;

Status visit(QElemType c)
{
	printf("%d ", c);
	return OK;
}

/* 构造一个空队列Q */
Status InitQueue(LinkQueue *Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		exit(OVERFLOW);
	Q->front->next = NULL;
	return OK;
}

/* 销毁队列Q */
Status DestroyQueue(LinkQueue *Q)
{
	while (Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
}

/* 将Q清为空队列 */
Status ClearQueue(LinkQueue *Q)
{
	QueuePtr p, q;
	Q->rear = Q->front;
	p = Q->front->next;
	Q->front->next = NULL;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
	return OK;
}

/* 若Q为空队列,则返回TRUE,否则返回FALSE */
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

/* 求队列的长度 */
int QueueLength(LinkQueue Q)
{
	int i = 0;
	QueuePtr p;
	p = Q.front;
	while (Q.rear != p)
	{
		i++;
		p = p->next;
	}
	return i;
}

/* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
Status GetHead(LinkQueue Q, QElemType *e)
{
	QueuePtr p;
	if (Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;
	*e = p->data;
	return OK;
}

/* 插入元素e为Q的新的队尾元素 */
Status EnQueue(LinkQueue *Q, QElemType e)
{
	QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
	if (!s) /* 存储分配失败 */
		exit(OVERFLOW);
	s->data = e;
	s->next = NULL;
	Q->rear->next = s;											   /* 把拥有元素e的新结点s赋值给原队尾结点的后继，见图中① */
	Q->rear = s; /* 把当前的s设置为队尾结点，rear指向s，见图中② */ // 如果先写Q->rear = s;是不是会导致原链队列队尾结点的丢失
	return OK;
}

/* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
Status DeQueue(LinkQueue *Q, QElemType *e)
{
	QueuePtr p;
	if (Q->front == Q->rear)
		return ERROR;
	p = Q->front->next;														  /* 将欲删除的队头结点暂存给p，见图中① */
	*e = p->data;															  /* 将欲删除的队头结点的值赋值给e */
	Q->front->next = p->next;												  /* 将原队头结点的后继p->next赋值给头结点后继，见图中② */
	if (Q->rear == p) /* 若队头就是队尾，则删除后将rear指向头结点，见图中③ */ // 注意！这个条件检查是否正在删除当前的队尾节点。所以这个检查根本用不到front指针，只要rear指针指向着头结点的下一个结点，就相当于整个队列只有这一个有效结点，而我们要删除这个有效结点。这个条件确实只依赖于 rear 指针和 p（要删除的节点）。这里的关键逻辑是：如果 rear（当前队尾指针）指向的节点和 p 是同一个，那么这意味着我们正在删除队列中的唯一一个有效元素。在这种情况下，一旦该元素被删除，队列将变为空，所以 rear 需要被更新回哑节点。你提到的 front 指针在这个特定的条件检查中确实没有直接用处，但它在后续的 Q->rear = Q->front; 中被使用，以确保 rear 被正确更新回哑节点。你的观察非常准确，这个检查确实完全基于 rear 和 p，并确保了队列的正确性和完整性。
		Q->rear = Q->front;													  // 这行代码确实是为了更新 rear 指针，使其指向哑节点（或头节点）。在链式队列实现中，通常会有一个哑节点（头节点），它不存储任何实际的数据。当队列为空时，front 和 rear 都指向这个哑节点。当队列中只有一个元素时，front 仍然指向哑节点，但 rear 指向这个唯一的数据节点。即图中3所指向的头结点。
	free(p);
	return OK;
}

/* 从队头到队尾依次对队列Q中每个元素输出 */
Status QueueTraverse(LinkQueue Q)
{
	QueuePtr p;
	p = Q.front->next;
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
	int i;
	QElemType d;
	LinkQueue q;
	i = InitQueue(&q);
	if (i)
		printf("成功地构造了一个空队列!\n");
	printf("是否空队列？%d(1:空 0:否)  ", QueueEmpty(q));
	printf("队列的长度为%d\n", QueueLength(q));
	EnQueue(&q, -5);
	EnQueue(&q, 5);
	EnQueue(&q, 10);
	printf("插入3个元素(-5,5,10)后,队列的长度为%d\n", QueueLength(q));
	printf("是否空队列？%d(1:空 0:否)  ", QueueEmpty(q));
	printf("队列的元素依次为：");
	QueueTraverse(q);
	i = GetHead(q, &d);
	if (i == OK)
		printf("队头元素是：%d\n", d);
	DeQueue(&q, &d);
	printf("删除了队头元素%d\n", d);
	i = GetHead(q, &d);
	if (i == OK)
		printf("新的队头元素是：%d\n", d);
	ClearQueue(&q);
	printf("清空队列后,q.front=%u q.rear=%u q.front->next=%u\n", q.front, q.rear, q.front->next);
	DestroyQueue(&q);
	printf("销毁队列后,q.front=%u q.rear=%u\n", q.front, q.rear);

	return 0;
}
