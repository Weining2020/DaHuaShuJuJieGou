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
typedef int SElemType; /* SElemType���͸���ʵ������������������Ϊint */

/* ��ջ�ṹ */
typedef struct StackNode // StackNode�ṹ����һ��data��Ա����������SElemType����ע�⣬����Ҫ�������ط�����SElemType�����ͣ�������int��float��char���������ͣ���
{
        SElemType data;
        struct StackNode *next; // next��һ��ָ�룬ָ����һ��StackNode�ṹ�ĵ�ַ���γ�����ṹ��
} StackNode, *LinkStackPtr;     // LinkStackPtr��struct StackNode *�ı��������ڷ���ش���StackNode���͵�ָ�롣

typedef struct
{
        LinkStackPtr top; // top��һ��ָ�룬ָ����ջ������StackNode��ʹ��LinkStackPtr���ͼ���ָ��Ķ��塣
        int count;        // count��¼����ջ�е�Ԫ��������
} LinkStack;

Status visit(SElemType c)
{
        printf("%d ", c);
        return OK;
}

/*  ����һ����ջS */
Status InitStack(LinkStack *S)
{
        S->top = (LinkStackPtr)malloc(sizeof(StackNode));
        if (!S->top)
                return ERROR;
        S->top = NULL;
        S->count = 0;
        return OK;
}

/* ��S��Ϊ��ջ */
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

/* ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE */
Status StackEmpty(LinkStack S)
{
        if (S.count == 0)
                return TRUE;
        else
                return FALSE;
}

/* ����S��Ԫ�ظ�������ջ�ĳ��� */
int StackLength(LinkStack S)
{
        return S.count;
}

/* ��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR */
Status GetTop(LinkStack S, SElemType *e)
{
        if (S.top == NULL)
                return ERROR;
        else
                *e = S.top->data;
        return OK;
}

/* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
Status Push(LinkStack *S, SElemType e)
{
        LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));               // ʹ�� malloc ������̬����һ���ڴ����洢�µ� StackNode���������ַ��ֵ��ָ�� s��ע�⣬malloc ���ص��� void * ���͵�ָ�룬������Ҫ����ǿ������ת��Ϊ LinkStackPtr��
        s->data = e;                                                            // �������Ԫ�� e ��ֵ��ֵ���½ڵ� s �� data ��Ա��
        s->next = S->top; /* �ѵ�ǰ��ջ��Ԫ�ظ�ֵ���½���ֱ�Ӻ�̣���ͼ�Т� */ // �������½ڵ� s �� next ָ��ָ��ǰ��ջ��Ԫ�ء��������½ڵ� s �ͳ��������еĵ�һ���ڵ㡣
        S->top = s; /* ���µĽ��s��ֵ��ջ��ָ�룬��ͼ�Т� */                    // ������ջ S �� top ָ�룬ʹ��ָ���²���Ľڵ� s��
        S->count++;
        return OK;
}

/* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR */
Status Pop(LinkStack *S, SElemType *e)
{
        LinkStackPtr p;
        if (StackEmpty(*S)) // ���ȼ��ջ�Ƿ�Ϊ�գ����Ϊ���򷵻�ERROR��
                return ERROR;
        *e = S->top->data;                           // ���ջ���գ�������ջ��Ԫ�ص�data��ֵ��*e��
        p = S->top; /* ��ջ����㸳ֵ��p����ͼ�Т� */ // ע�⣡��Pop()�����У���ջ���ڵ㸳ֵ��p��Ϊ���ڸ���ջ��ָ��S->top֮������ȷ���ͷ�ԭջ���ڵ���ڴ档��S->top���º��������ԭջ���ڵ�ĵ�ַ��������һ�������У���������p�������ǽ��޷����ʲ���ȷ�ͷ�����ڵ���ڴ棬�Ӷ����ܵ����ڴ�й©��
        S->top = S->top->next;                       /* ʹ��ջ��ָ������һλ��ָ���һ��㣬��ͼ�Т� */
        free(p);                                     /* �ͷŽ��p */
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
        printf("ջ��Ԫ������Ϊ��");
        StackTraverse(s);
        Pop(&s, &e);
        printf("������ջ��Ԫ�� e=%d\n", e);
        printf("ջ�շ�%d(1:�� 0:��)\n", StackEmpty(s));
        GetTop(s, &e);
        printf("ջ��Ԫ�� e=%d ջ�ĳ���Ϊ%d\n", e, StackLength(s));
        ClearStack(&s);
        printf("���ջ��ջ�շ�%d(1:�� 0:��)\n", StackEmpty(s));
        return 0;
}