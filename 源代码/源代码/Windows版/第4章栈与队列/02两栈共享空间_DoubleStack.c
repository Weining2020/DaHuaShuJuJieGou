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

/* ��ջ����ռ�ṹ */
typedef struct
{
        SElemType data[MAXSIZE];
        int top1; /* ջ1ջ��ָ�� */
        int top2; /* ջ2ջ��ָ�� */
} SqDoubleStack;

Status visit(SElemType c)
{
        printf("%d ", c);
        return OK;
}

/*  ����һ����ջS */
Status InitStack(SqDoubleStack *S)
{
        S->top1 = -1;
        S->top2 = MAXSIZE;
        return OK;
}

/* ��S��Ϊ��ջ */
Status ClearStack(SqDoubleStack *S)
{
        S->top1 = -1;
        S->top2 = MAXSIZE;
        return OK;
}

/* ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE */
Status StackEmpty(SqDoubleStack S)
{
        if (S.top1 == -1 && S.top2 == MAXSIZE)
                return TRUE;
        else
                return FALSE;
}

/* ����S��Ԫ�ظ�������ջ�ĳ��� */
int StackLength(SqDoubleStack S)
{
        return (S.top1 + 1) + (MAXSIZE - S.top2);
}

/* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
Status Push(SqDoubleStack *S, SElemType e, int stackNumber)
{
        if (S->top1 + 1 == S->top2) /* ջ������������push��Ԫ���� */
                return ERROR;
        if (stackNumber == 1)                                                     /* ջ1��Ԫ�ؽ�ջ */
                S->data[++S->top1] = e; /* ����ջ1����top1+1�������Ԫ�ظ�ֵ�� */ // ��д��S->data[S->top1++]Ҳû���⡣
        else if (stackNumber == 2)                                                /* ջ2��Ԫ�ؽ�ջ */
                S->data[--S->top2] = e;                                           /* ����ջ2����top2-1�������Ԫ�ظ�ֵ�� */
        return OK;
}

/* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR */
Status Pop(SqDoubleStack *S, SElemType *e, int stackNumber)
{
        if (stackNumber == 1)
        {
                if (S->top1 == -1)
                        return ERROR;                              /* ˵��ջ1�Ѿ��ǿ�ջ����� */
                *e = S->data[S->top1--]; /* ��ջ1��ջ��Ԫ�س�ջ */ // ע�⣡��������ƽ�ȥ�ˡ��������д���ǶԵġ�������д���У����Ƚ� S->top1 ��ָ���ջ��Ԫ�أ���top1λ�ã�������top1 �C 1λ�ã���ֵ���� e��Ȼ���ٽ� S->top1 ��һ����ʾ��ջ����������д���ĺô��ǿ�����һ�д�������ɳ�ջ����������Ҫע����� e �����ᱣ���ջǰ��ջ��Ԫ�ص�ֵ��
                // ��Σ�����д������*e = S->data[S->top1]; S->top1--; ����д��Ҳ�ǶԵġ�����д����������Ϊ���У������������Ķ���������ڵ�һ�л�ȡջ��Ԫ�ص�ֵ��Ȼ���ڵڶ��и���ջ��ָ�롣
        }
        else if (stackNumber == 2)
        {
                if (S->top2 == MAXSIZE)
                        return ERROR;    /* ˵��ջ2�Ѿ��ǿ�ջ����� */
                *e = S->data[S->top2++]; /* ��ջ2��ջ��Ԫ�س�ջ */
        }
        return OK;
}
/*
        �岥Question��Ϊʲô
                *e = S->data[S->top1--];
                ����д������ȷ�ģ�
        ��������������ʡ���������ϸ����һ�� `*e = S->data[S->top1--];` ����д��ΪʲôҲ����ȷ�ģ�

        1. `S->top1` ��ջ1��ջ��ָ�롣���ȣ�������������ջ1�е�ջ��Ԫ�ص�ֵ��

        2. `S->top1--` ���ֱ�ʾ��ʹ�� `S->top1` ��ֵ������ջ1�е�ջ��Ԫ�أ�Ȼ���ٽ� `S->top1`������˵��S��top1��Ա��ֵ��һ�� ��һ��

        3. ����������У�`S->top1` ��ֵ�����ڷ���ջ��Ԫ�أ�Ȼ��Ž����˼�һ�Ĳ���������ζ�� `S->top1` �ڷ���ջ��Ԫ��֮ǰ��Ȼ��ָ��ǰջ��Ԫ�ص�λ�á�

        4. `*e = S->data[S->top1--];` ��һ�е������ǽ�ջ1��ջ��Ԫ�ص�ֵ���� `e`��Ȼ���ٽ� `S->top1` ��һ���Ա�ʾջ��Ԫ���Ѿ���ջ��

        ���ԣ���Ȼ��һ�д����Ǻϲ��˷���ջ��Ԫ�غͼ���ջ��ָ��Ĳ����������� `S->top1` ��ֵ�ڷ���Ԫ��֮ǰ��ʹ�ã���������Ȼ��Ч���ܹ���ȷ�ػ�ȡջ��Ԫ�ص�ֵ������ջ��ָ�롣������Ϊ�� C �����У���׺ `--` ��������ʾ��ʹ�ñ�����ֵ��Ȼ���ٽ�������һ��

        ��֮��`*e = S->data[S->top1--];` ����д������ȷ�ģ�����������ջ����ȡջ��Ԫ�ص�ֵ��

        ע�⣡*e = S->data[S->top1--];����ʹ���˺��������post-decrement�������ȣ�S->data[S->top1]��ֵ����ȡ����ֵ��*e��Ȼ��S->top1��1����������������У������ڻ�ȡS->top1��ǰָ���Ԫ�أ������ڻ�ȡ��top1��1��

        *e = S->data[S->--top1];����ʹ����ǰ��������pre-decrement�������ȣ�S->top1��1��Ȼ��S->data[S->top1]��ֵ����ȡ����ֵ��*e����������������У���ʵ���ϻ�ȡ����S->top1 - 1λ�õ�Ԫ�ء�
        ��һ��ʵ�ʵ�������������⣺

        ����S->top1��ʼֵΪ5��

        ����*e = S->data[S->top1--];:

        *e����ֵΪS->data[5]��Ȼ��S->top1��Ϊ4��
        ����*e = S->data[S->--top1];:

        S->top1���ȱ�Ϊ4��Ȼ��*e����ֵΪS->data[4]��
        ���ԣ�����������η��ʵ��ǲ�ͬ������Ԫ�ء�ȷ�����˽�������𣬲�������ľ�������ѡ����ȷ�Ĳ�����
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

        printf("ջ��Ԫ������Ϊ��");
        StackTraverse(s);

        printf("��ǰջ��Ԫ���У�%d \n", StackLength(s));

        Pop(&s, &e, 2);
        printf("������ջ��Ԫ�� e=%d\n", e);
        printf("ջ�շ�%d(1:�� 0:��)\n", StackEmpty(s));

        for (j = 6; j <= MAXSIZE - 2; j++)
                Push(&s, j, 1);

        printf("ջ��Ԫ������Ϊ��");
        StackTraverse(s);

        printf("ջ����%d(1:�� 0:��)\n", Push(&s, 100, 1));

        ClearStack(&s);
        printf("���ջ��ջ�շ�%d(1:�� 0:��)\n", StackEmpty(s));

        return 0;
}