/************************************************************************/
/*单链队列－－队列的链式存储结构                                          */
/************************************************************************/
#define OK 1
#define ERROR 0
//#define OVERFLOW -2
typedef int Status;
//typedef int QElemType;

typedef struct QNode {
	QElemType data;
	struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
	QueuePtr front, rear; //队头、队尾指针
} LinkQueue;

/************************************************************************/
/* 链队列的基本操作(9个)                                                 */
/************************************************************************/ 

//构造一个空队列Q
Status InitQueue(LinkQueue *Q){ 
	(*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
	if(!(*Q).front)
		exit(OVERFLOW);
	(*Q).front->next=NULL;
	return OK;
}

//销毁队列Q(无论空否均可) 
Status DestroyQueue(LinkQueue *Q){
	while((*Q).front){
		(*Q).rear=(*Q).front->next;
		free((*Q).front);
		(*Q).front=(*Q).rear;
	}
	return OK;
}

//将Q清为空队列
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

//若Q为空队列,则返回TRUE,否则返回FALSE
Status QueueEmpty(LinkQueue Q){
	if(Q.front==Q.rear)
		return TRUE;
	else
		return FALSE;
}

//求队列的长度
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

//若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR
Status GetHead_Q(LinkQueue Q,QElemType *e) { 
	QueuePtr p;
	if(Q.front==Q.rear)
		return ERROR;
	p=Q.front->next;
	*e=p->data;
	return OK;
}

//插入元素e为Q的新的队尾元素
Status EnQueue(LinkQueue *Q,QElemType e)
{ 
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) //存储分配失败
		exit(OVERFLOW);
	p->data=e;
	p->next=NULL;
	(*Q).rear->next=p;
	(*Q).rear=p;
	return OK;
}

//若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR
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

//从队头到队尾依次对队列Q中每个元素调用函数vi()。一旦vi失败,则操作失败。
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

