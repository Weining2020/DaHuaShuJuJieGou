#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;

typedef int QElemType; /* QElemType���͸���ʵ������������������Ϊint */

typedef struct QNode /* ���ṹ */ // �⿪ʼ����һ����Ϊ QNode �Ľṹ�壬����ʾ���е�һ���ڵ㡣������ṹ���У���������Ա��
{
	QElemType data;		// data�����Ƕ���Ԫ�ص����ݲ��֣�������Ϊ QElemType��Ҳ���� int��
	struct QNode *next; // next������һ��ָ����һ���ڵ��ָ�룬Ҳ�� QNode ���͵ġ�
} QNode, *QueuePtr;		// QNode����ʾ���нڵ�����͡�QueuePtr����ʾָ����нڵ��ָ������͡�ע�⣡��һ�д���������������ġ������ typedef ����У�QNode �� struct QNode �ı��������ڼ򻯺����Ĵ���д������ *QueuePtr �Ĳ��֣����Ƕ�����һ���µı��� QueuePtr����������������һ��ָ�� QNode ��ָ�롣���仰˵��QueuePtr �� QNode* �ı�������������Ŀ����Ϊ�˽�һ���򻯴��롣���磬�����������һ��ָ�� QNode �ṹ���ָ�룬��������������ַ�ʽ��ʹ��ԭʼ��д����QNode* pointer1; ʹ�� QueuePtr ���������QueuePtr pointer2;�����������ǵȼ۵ġ�ʹ�� QueuePtr ����ʹ�������࣬���������ر�ʾ����һ��ָ����нڵ��ָ�롣

typedef struct /* ���е�����ṹ */
{
	QueuePtr front, rear; /* ��ͷ����βָ�� */
} LinkQueue;

Status visit(QElemType c)
{
	printf("%d ", c);
	return OK;
}

/* ����һ���ն���Q */
Status InitQueue(LinkQueue *Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		exit(OVERFLOW);
	Q->front->next = NULL;
	return OK;
}

/* ���ٶ���Q */
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

/* ��Q��Ϊ�ն��� */
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

/* ��QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
Status QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

/* ����еĳ��� */
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

/* �����в���,����e����Q�Ķ�ͷԪ��,������OK,���򷵻�ERROR */
Status GetHead(LinkQueue Q, QElemType *e)
{
	QueuePtr p;
	if (Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;
	*e = p->data;
	return OK;
}

/* ����Ԫ��eΪQ���µĶ�βԪ�� */
Status EnQueue(LinkQueue *Q, QElemType e)
{
	QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
	if (!s) /* �洢����ʧ�� */
		exit(OVERFLOW);
	s->data = e;
	s->next = NULL;
	Q->rear->next = s;											   /* ��ӵ��Ԫ��e���½��s��ֵ��ԭ��β���ĺ�̣���ͼ�Т� */
	Q->rear = s; /* �ѵ�ǰ��s����Ϊ��β��㣬rearָ��s����ͼ�Т� */ // �����дQ->rear = s;�ǲ��ǻᵼ��ԭ�����ж�β���Ķ�ʧ
	return OK;
}

/* �����в���,ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������OK,���򷵻�ERROR */
Status DeQueue(LinkQueue *Q, QElemType *e)
{
	QueuePtr p;
	if (Q->front == Q->rear)
		return ERROR;
	p = Q->front->next;														  /* ����ɾ���Ķ�ͷ����ݴ��p����ͼ�Т� */
	*e = p->data;															  /* ����ɾ���Ķ�ͷ����ֵ��ֵ��e */
	Q->front->next = p->next;												  /* ��ԭ��ͷ���ĺ��p->next��ֵ��ͷ����̣���ͼ�Т� */
	if (Q->rear == p) /* ����ͷ���Ƕ�β����ɾ����rearָ��ͷ��㣬��ͼ�Т� */ // ע�⣡�����������Ƿ�����ɾ����ǰ�Ķ�β�ڵ㡣��������������ò���frontָ�룬ֻҪrearָ��ָ����ͷ������һ����㣬���൱����������ֻ����һ����Ч��㣬������Ҫɾ�������Ч��㡣�������ȷʵֻ������ rear ָ��� p��Ҫɾ���Ľڵ㣩������Ĺؼ��߼��ǣ���� rear����ǰ��βָ�룩ָ��Ľڵ�� p ��ͬһ������ô����ζ����������ɾ�������е�Ψһһ����ЧԪ�ء�����������£�һ����Ԫ�ر�ɾ�������н���Ϊ�գ����� rear ��Ҫ�����»��ƽڵ㡣���ᵽ�� front ָ��������ض������������ȷʵû��ֱ���ô��������ں����� Q->rear = Q->front; �б�ʹ�ã���ȷ�� rear ����ȷ���»��ƽڵ㡣��Ĺ۲�ǳ�׼ȷ��������ȷʵ��ȫ���� rear �� p����ȷ���˶��е���ȷ�Ժ������ԡ�
		Q->rear = Q->front;													  // ���д���ȷʵ��Ϊ�˸��� rear ָ�룬ʹ��ָ���ƽڵ㣨��ͷ�ڵ㣩������ʽ����ʵ���У�ͨ������һ���ƽڵ㣨ͷ�ڵ㣩�������洢�κ�ʵ�ʵ����ݡ�������Ϊ��ʱ��front �� rear ��ָ������ƽڵ㡣��������ֻ��һ��Ԫ��ʱ��front ��Ȼָ���ƽڵ㣬�� rear ָ�����Ψһ�����ݽڵ㡣��ͼ��3��ָ���ͷ��㡣
	free(p);
	return OK;
}

/* �Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ����� */
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
		printf("�ɹ��ع�����һ���ն���!\n");
	printf("�Ƿ�ն��У�%d(1:�� 0:��)  ", QueueEmpty(q));
	printf("���еĳ���Ϊ%d\n", QueueLength(q));
	EnQueue(&q, -5);
	EnQueue(&q, 5);
	EnQueue(&q, 10);
	printf("����3��Ԫ��(-5,5,10)��,���еĳ���Ϊ%d\n", QueueLength(q));
	printf("�Ƿ�ն��У�%d(1:�� 0:��)  ", QueueEmpty(q));
	printf("���е�Ԫ������Ϊ��");
	QueueTraverse(q);
	i = GetHead(q, &d);
	if (i == OK)
		printf("��ͷԪ���ǣ�%d\n", d);
	DeQueue(&q, &d);
	printf("ɾ���˶�ͷԪ��%d\n", d);
	i = GetHead(q, &d);
	if (i == OK)
		printf("�µĶ�ͷԪ���ǣ�%d\n", d);
	ClearQueue(&q);
	printf("��ն��к�,q.front=%u q.rear=%u q.front->next=%u\n", q.front, q.rear, q.front->next);
	DestroyQueue(&q);
	printf("���ٶ��к�,q.front=%u q.rear=%u\n", q.front, q.rear);

	return 0;
}
