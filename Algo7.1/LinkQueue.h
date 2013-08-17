/************************************************************************/
/*�������У������е���ʽ�洢�ṹ                                          */
/************************************************************************/
#define OK 1
#define ERROR 0
#define OVERFLOW 2
typedef int Status;
//typedef int QElemType;

typedef struct QNode {
	QElemType data;
	struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
	QueuePtr front, rear; //��ͷ����βָ��
} LinkQueue;

/************************************************************************/
/* �����еĻ�������(9��)                                                 */
/************************************************************************/ 

//����һ���ն���Q
Status InitQueue(LinkQueue *Q){ 
	(*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
	if(!(*Q).front)
		exit(OVERFLOW);
	(*Q).front->next=NULL;
	return OK;
}

//���ٶ���Q(���ۿշ����) 
Status DestroyQueue(LinkQueue *Q){
	while((*Q).front){
		(*Q).rear=(*Q).front->next;
		free((*Q).front);
		(*Q).front=(*Q).rear;
	}
	return OK;
}

//��Q��Ϊ�ն���
Status ClearQueue(LinkQueue *Q){
	QueuePtr p,q;
	(*Q).rear=(*Q).front;
	p=(*Q).front->next;
	(*Q).front->next=NULL;
	while(p){
		q=p;
		p=p->next;
		free(q);
	}
	return OK;
}

//��QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE
Status QueueEmpty(LinkQueue Q){
	if(Q.front==Q.rear)
		return TRUE;
	else
		return FALSE;
}

//����еĳ���
int QueueLength(LinkQueue Q){ 
	int i=0;
	QueuePtr p;
	p=Q.front;
	while(Q.rear!=p) {
		i++;
		p=p->next;
	}
	return i;
}

//�����в���,����e����Q�Ķ�ͷԪ��,������OK,���򷵻�ERROR
Status GetHead_Q(LinkQueue Q,QElemType *e) { 
	QueuePtr p;
	if(Q.front==Q.rear)
		return ERROR;
	p=Q.front->next;
	*e=p->data;
	return OK;
}

//����Ԫ��eΪQ���µĶ�βԪ��
Status EnQueue(LinkQueue *Q,QElemType e)
{ 
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) //�洢����ʧ��
		exit(OVERFLOW);
	p->data=e;
	p->next=NULL;
	(*Q).rear->next=p;
	(*Q).rear=p;
	return OK;
}

//�����в���,ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������OK,���򷵻�ERROR
Status DeQueue(LinkQueue *Q,QElemType *e)
{ 
	QueuePtr p;
	if((*Q).front==(*Q).rear)
		return ERROR;
	p=(*Q).front->next;
	*e=p->data;
	(*Q).front->next=p->next;
	if((*Q).rear==p)
		(*Q).rear=(*Q).front;
	free(p);
	return OK;
}

//�Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi()��һ��viʧ��,�����ʧ�ܡ�
Status QueueTraverse(LinkQueue Q,void(*vi)(QElemType)){
	QueuePtr p;
	p=Q.front->next;
	while(p){
		vi(p->data);
		p=p->next;
	}
	printf("\n");
	return OK;
}

