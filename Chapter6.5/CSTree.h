/************************************************************************/
/*���Ķ�������(���ӣ��ֵ�)�洢��ʾ                                        */
/************************************************************************/
typedef char TElemType;
TElemType Nil=' '; //�Կո��Ϊ��
typedef int Status;
#define  OK 1
#define  FALSE 0
#define  TRUE 1
#define  ERROR 0
#include <stdlib.h>
#include <string.h>

typedef struct CSNode{
	TElemType data;
	struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

/************************************************************************/
/* ���Ķ�������(���ӣ��ֵ�)�洢�Ļ�������(17��)                            */
/************************************************************************/

//�������: �������T
Status InitTree(CSTree *T){ 
	*T=NULL;
	return OK;
}

//��ʼ����: ��T���ڡ��������: ������T 
void DestroyTree(CSTree *T){ 
	if(*T){
		if((*T)->firstchild) //T�г���
			DestroyTree(&(*T)->firstchild); //����T�ĳ���Ϊ���������� 
		if((*T)->nextsibling) //T����һ���ֵ� 
			DestroyTree(&(*T)->nextsibling); //����T����һ���ֵ�Ϊ����������
		free(*T); /* �ͷŸ���� */
		*T=NULL;
	}
}

typedef CSTree QElemType; //�������Ԫ������
#include "LinkQueue.h" //����LinkQueue���� 

//������T
Status CreateTree(CSTree *T){ 
	char c[20]; //��ʱ��ź��ӽ��(�費����20��)��ֵ 
	CSTree p,p1;
	LinkQueue q;
	int i,l;
	InitQueue(&q);
	printf("����������(�ַ���,�ո�Ϊ��): ");
	scanf("%c%*c",&c[0]);
	if(c[0]!=Nil) {
		*T=(CSTree)malloc(sizeof(CSNode)); //��������� 
		(*T)->data=c[0];
		(*T)->nextsibling=NULL;
		EnQueue(&q,*T); //��Ӹ�����ָ�� 
		while(!QueueEmpty(q)){ //�Ӳ��� 
			DeQueue(&q,&p); //����һ������ָ��
			printf("�밴����˳��������%c�����к���: ",p->data);
			gets(c);
			l=strlen(c);
			if(l>0) {//�к���
				p1=p->firstchild=(CSTree)malloc(sizeof(CSNode)); //�������ӽ�� 
				p1->data=c[0];
				for(i=1;i<l;i++){
					p1->nextsibling=(CSTree)malloc(sizeof(CSNode)); //������һ���ֵܽ�� 
					EnQueue(&q,p1); /* �����һ����� */
					p1=p1->nextsibling;
					p1->data=c[i];
				}
				p1->nextsibling=NULL;
				
				EnQueue(&q,p1); //������һ�����
			}
			else
				p->firstchild=NULL;
		}
	}
	else
		*T=NULL;
	return OK;
}

#define ClearTree DestroyTree //���߲�����ͬ

//��ʼ����: ��T���ڡ�
//�������: ��TΪ����,�򷵻�TURE,���򷵻�FALSE 
Status TreeEmpty(CSTree T){ 
	if(T) //T���� 
		return FALSE;
	else
		return TRUE;
}

//��ʼ����: ��T���ڡ��������: ����T����� 
int TreeDepth(CSTree T){ 
	CSTree p;
	int depth,max=0;
	if(!T) //���� 
		return 0;
	if(!T->firstchild) //���޳���
		return 1;
	for(p=T->firstchild;p;p=p->nextsibling)
	{
		depth=TreeDepth(p);
		if(depth>max)
			max=depth;
	}
	return max+1;
}

//����p��ָ����ֵ 
TElemType Value(CSTree p){ 
	return p->data;
}

//��ʼ����: ��T���ڡ�
//�������: ����T�ĸ� 
TElemType Root(CSTree T){ 
	if(T)
		return Value(T);
	else
		return Nil;
}

//���ض�������(���ӣ��ֵ�)��T��ָ��Ԫ��ֵΪs�Ľ���ָ�롣
CSTree Point(CSTree T,TElemType s){ 
	LinkQueue q;
	QElemType a;
	if(T) {//�ǿ��� 
		InitQueue(&q); //��ʼ������ 
		EnQueue(&q,T); /* �������� */
		while(!QueueEmpty(q)) {//�Ӳ��� 
			DeQueue(&q,&a); //����,����Ԫ�ظ���a 
			if(a->data==s)
				return a;
			if(a->firstchild) //�г��� 
				EnQueue(&q,a->firstchild); //��ӳ��� 
			if(a->nextsibling) //����һ���ֵ� 
				EnQueue(&q,a->nextsibling); //�����һ���ֵ� 
		}
	}
	return NULL;
}

//��ʼ����: ��T����,cur_e����T�н���ֵ��
//�������: ��cur_eΪvalue 
Status Assign(CSTree *T,TElemType cur_e,TElemType value){ 
	CSTree p;
	if(*T) {//�ǿ��� 
		p=Point(*T,cur_e); //pΪcur_e��ָ��
		if(p){ //�ҵ�cur_e 
			p->data=value; //����ֵ 
			return OK;
		}
	}
	return Nil; //���ջ�û�ҵ� 
}

//��ʼ����: ��T����,cur_e��T��ĳ����� 
//�������: ��cur_e��T�ķǸ����,�򷵻�����˫��,������ֵΪ���գ� 
TElemType Parent(CSTree T,TElemType cur_e){
	CSTree p,t;
	LinkQueue q;
	InitQueue(&q);
	if(T) {//���ǿ� 
		if(Value(T)==cur_e) //�����ֵΪcur_e 
			return Nil;
		EnQueue(&q,T); //�������� 
		while(!QueueEmpty(q)){
			DeQueue(&q,&p);
			if(p->firstchild){ //p�г��� 
				if(p->firstchild->data==cur_e) //����Ϊcur_e 
					return Value(p); //����˫�� 
				t=p; //˫��ָ�븳��t 
				p=p->firstchild; //pָ���� 
				EnQueue(&q,p); //��ӳ��� 
				while(p->nextsibling) {//����һ���ֵ� 
					p=p->nextsibling; //pָ����һ���ֵ� 
					if(Value(p)==cur_e) //��һ���ֵ�Ϊcur_e 
						return Value(t); //����˫�� 
					EnQueue(&q,p); //�����һ���ֵ� 
				}
			}
		}
	}
	return Nil; //���ջ�û�ҵ�cur_e 
}

//��ʼ����: ��T����,cur_e��T��ĳ����� 
//�������: ��cur_e��T�ķ�Ҷ�ӽ��,�򷵻�����������,���򷵻أ��գ� 
TElemType LeftChild(CSTree T,TElemType cur_e){ 
	CSTree f;
	f=Point(T,cur_e); //fָ����cur_e 
	if(f&&f->firstchild) //�ҵ����cur_e�ҽ��cur_e�г��� 
		return f->firstchild->data;
	else
		return Nil;
}

//��ʼ����: ��T����,cur_e��T��ĳ����� 
//�������: ��cur_e�����ֵ�,�򷵻��������ֵ�,���򷵻أ��գ� 
TElemType RightSibling(CSTree T,TElemType cur_e){ 
	CSTree f;
	f=Point(T,cur_e); //fָ����cur_e 
	if(f&&f->nextsibling) //�ҵ����cur_e�ҽ��cur_e�����ֵ� 
		return f->nextsibling->data;
	else
		return Nil; //���� 
}

//��ʼ����: ��T����,pָ��T��ĳ�����,1��i��p��ָ���Ķ�+1,�ǿ���c��T���ཻ 
//�������: ����cΪT��p���ĵ�i������ 
//��Ϊp��ָ���ĵ�ַ����ı䣬��p�������������� 
Status InsertChild(CSTree *T,CSTree p,int i,CSTree c){
	int j;
	//T����
	if(*T) {
		if(i==1){ //����cΪp�ĳ���
			c->nextsibling=p->firstchild; //p��ԭ��������c����һ���ֵ�(c�����ֵ�) 
			p->firstchild=c;
		}
		else{ //�Ҳ���� 
			p=p->firstchild; //ָ��p�ĳ��� 
			j=2;
			while(p&&j<i){
				p=p->nextsibling;
				j++;
			}
			if(j==i) {//�ҵ�����λ�� 
				c->nextsibling=p->nextsibling;
				p->nextsibling=c;
			}
			else //pԭ�к�����С��i-1 
				return ERROR;
		}
		return OK;
	}
	else //T��
		return ERROR;
}

//��ʼ����: ��T����,pָ��T��ĳ�����,1��i��p��ָ���Ķ� 
//�������: ɾ��T��p��ָ���ĵ�i������ 
//��Ϊp��ָ���ĵ�ַ����ı䣬��p�������������� 
Status DeleteChild(CSTree *T,CSTree p,int i){
	CSTree b;
	int j;
	if(*T) {//T���� 
		if(i==1) {//ɾ������ 
			b=p->firstchild;
			p->firstchild=b->nextsibling; //p��ԭ�������ǳ��� 
			b->nextsibling=NULL;
			DestroyTree(&b);
		}
		else{ //ɾ���ǳ��� 
			p=p->firstchild; //pָ���� 
			j=2;
			while(p&&j<i){
				p=p->nextsibling;
				j++;
			}
			if(j==i){ //�ҵ���i������
				b=p->nextsibling;
				p->nextsibling=b->nextsibling;
				b->nextsibling=NULL;
				DestroyTree(&b);
			}
			else //pԭ�к�����С��i 
				return ERROR;
		}
		return OK;
	}
	else
		return ERROR;
}

//�ȸ��������ӣ��ֵܶ�������ṹ����T 
void PreOrderTraverse(CSTree T,void(*Visit)(TElemType))
{ 
	if(T){
		Visit(Value(T)); //�ȷ��ʸ���� 
		PreOrderTraverse(T->firstchild,Visit); //���ȸ������������� 
		PreOrderTraverse(T->nextsibling,Visit); //����ȸ�������һ���ֵ����� 
	}
}

 //����������ӣ��ֵܶ�������ṹ����T 
void PostOrderTraverse(CSTree T,void(*Visit)(TElemType))
{
	CSTree p;
	if(T)
	{
		if(T->firstchild){ //�г���
			PostOrderTraverse(T->firstchild,Visit); //��������������� 
			p=T->firstchild->nextsibling; //pָ���ӵ���һ���ֵ� 
			while(p){
				PostOrderTraverse(p,Visit); //���������һ���ֵ����� 
				p=p->nextsibling; //pָ������һ���ֵ� 
			}
		}
		Visit(Value(T)); //�����ʸ���� 
	}
}

//����������ӣ��ֵܶ�������ṹ����T 
void LevelOrderTraverse(CSTree T,void(*Visit)(TElemType)){ 
	CSTree p;
	LinkQueue q;
	InitQueue(&q);
	if(T){
		Visit(Value(T)); //�ȷ��ʸ���� 
		EnQueue(&q,T); //��Ӹ�����ָ�� 
		while(!QueueEmpty(q)) {//�Ӳ��� 
			DeQueue(&q,&p); //����һ������ָ�� 
			if(p->firstchild) {//�г��� 
				p=p->firstchild;
				Visit(Value(p)); //���ʳ��ӽ�� 
				EnQueue(&q,p); //��ӳ��ӽ���ָ�� 
				while(p->nextsibling){ //����һ���ֵ�
					p=p->nextsibling;
					Visit(Value(p)); //������һ���ֵ� 
					EnQueue(&q,p); //����ֵܽ���ָ��
				}
			}
		}
	}
}
