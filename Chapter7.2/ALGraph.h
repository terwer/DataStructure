/************************************************************************/
/*图的邻接表存储表示                                                     */
/************************************************************************/
#define MAX_NAME 3 //顶点字符串的最大长度+1 
typedef int InfoType; //存放网的权值
typedef char VertexType[MAX_NAME]; //字符串类型
#define MAX_VERTEX_NUM 20
#define  OK 1
#define  FALSE 0
#define  TRUE 1
#define  ERROR 0
typedef int Status;
typedef int Boolean;
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum{DG,DN,UDG,UDN}GraphKind; //{有向图,有向网,无向图,无向网}
typedef struct ArcNode{
	int adjvex; //该弧所指向的顶点的位置
	struct ArcNode *nextarc; //指向下一条弧的指针
	InfoType *info; //网的权值指针
}ArcNode; //表结点

typedef struct{
	VertexType data; //顶点信息
	ArcNode *firstarc; //第一个表结点的地址,指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM]; // 头结点

typedef struct{
	AdjList vertices;
	int vexnum,arcnum; //图的当前顶点数和弧数 
	int kind; //图的种类标志
}ALGraph;

/************************************************************************/
/*图的邻接表存储的基本操作(15个)                                          */
/************************************************************************/ 

//初始条件: 图G存在,u和G中顶点有相同特征
//操作结果: 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 

int LocateVex(ALGraph G,VertexType u){
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.vertices[i].data)==0)
			return i;
	return -1;
}

//采用邻接表存储结构,构造没有相关信息的图G(用一个函数构造4种图) 
Status CreateGraph(ALGraph *G){ 
	int i,j,k;
	int w; //权值 
	VertexType va,vb;
	ArcNode *p;
	printf("请输入图的类型:\n0:有向图\n1:有向网\n2:无向图\n3:无向网\n");
	scanf("%d",&(*G).kind);
	printf("请输入图的顶点数,边数: ");
	scanf("%d%d",&(*G).vexnum,&(*G).arcnum);
	//构造顶点向量
	for(i=0;i<(*G).vexnum;++i) {
		printf("请输入第%d个顶点的值(<%d个字符):\n",i+1,MAX_NAME);
		scanf("%s",(*G).vertices[i].data);
		(*G).vertices[i].firstarc=NULL;
	}
	if((*G).kind==1||(*G).kind==3) //网
		printf("请顺序输入每条弧(边)的权值、弧尾和弧头(以空格作为间隔):\n");
	else //图
		printf("请顺序输入每条弧(边)的弧尾和弧头(以空格作为间隔):\n");
	//构造表结点链表
	for(k=0;k<(*G).arcnum;++k) {
		if((*G).kind==1||(*G).kind==3) //网
			scanf("%d%s%s",&w,va,vb);
		else //图
			scanf("%s%s",va,vb);
		i=LocateVex(*G,va); //弧尾
		j=LocateVex(*G,vb); //弧头
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j;
		//网 
		if((*G).kind==1||(*G).kind==3){
			p->info=(int *)malloc(sizeof(int));
			*(p->info)=w;
		}
		else
			p->info=NULL; //图
		p->nextarc=(*G).vertices[i].firstarc; //插在表头
		(*G).vertices[i].firstarc=p;
		//无向图或网,产生第二个表结点 *
		if((*G).kind>=2){
			p=(ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex=i;
			//无向网
			if((*G).kind==3) {
				p->info=(int*)malloc(sizeof(int));
				*(p->info)=w;
			}
			else
				p->info=NULL; //无向图
			p->nextarc=(*G).vertices[j].firstarc; //插在表头
			(*G).vertices[j].firstarc=p;
		}
	}
	return OK;
}

//初始条件: 图G存在。操作结果: 销毁图G 
void DestroyGraph(ALGraph *G){ 
	int i;
	ArcNode *p,*q;
	(*G).vexnum=0;
	(*G).arcnum=0;
	for(i=0;i<(*G).vexnum;++i){
		p=(*G).vertices[i].firstarc;
		while(p){
			q=p->nextarc;
			if((*G).kind%2) //网
				free(p->info);
			free(p);
			p=q;
		}
	}
}

//初始条件: 图G存在,v是G中某个顶点的序号。
//操作结果: 返回v的值 
VertexType* GetVex(ALGraph G,int v){ 
	if(v>=G.vexnum||v<0)
		exit(ERROR);
	return &G.vertices[v].data;
}

//初始条件: 图G存在,v是G中某个顶点
//操作结果: 对v赋新值value 
Status PutVex(ALGraph *G,VertexType v,VertexType value){
	int i;
	i=LocateVex(*G,v);
	// v是G的顶点 
	if(i>-1) {
		strcpy((*G).vertices[i].data,value);
		return OK;
	}
	return ERROR;
}

//初始条件: 图G存在,v是G中某个顶点
//操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 
int FirstAdjVex(ALGraph G,VertexType v){ 	
	ArcNode *p;
	int v1;
	v1=LocateVex(G,v); //v1为顶点v在图G中的序号
	p=G.vertices[v1].firstarc;
	if(p)
		return p->adjvex;
	else
		return -1;
}

//初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点
//操作结果: 返回v的(相对于w的)下一个邻接顶点的序号。 
//若w是v的最后一个邻接点,则返回-1 
int NextAdjVex(ALGraph G,VertexType v,VertexType w){ 	ArcNode *p;
int v1,w1;
v1=LocateVex(G,v); //v1为顶点v在图G中的序号 
w1=LocateVex(G,w); //w1为顶点w在图G中的序号 
p=G.vertices[v1].firstarc;
while(p&&p->adjvex!=w1) //指针p不空且所指表结点不是w
	p=p->nextarc;
if(!p||!p->nextarc) //没找到w或w是最后一个邻接点
	return -1;
else // p->adjvex==w
	return p->nextarc->adjvex; //返回v的(相对于w的)下一个邻接顶点的序号
}

// 初始条件: 图G存在,v和图中顶点有相同特征 
// 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) 
void InsertVex(ALGraph *G,VertexType v){
	strcpy((*G).vertices[(*G).vexnum].data,v); //构造新顶点向量
	(*G).vertices[(*G).vexnum].firstarc=NULL;
	(*G).vexnum++; //图G的顶点数加1 
}

// 初始条件: 图G存在,v是G中某个顶点
//操作结果: 删除G中顶点v及其相关的弧
Status DeleteVex(ALGraph *G,VertexType v){
	int i,j;
	ArcNode *p,*q;
	j=LocateVex(*G,v); //j是顶点v的序号
	if(j<0) // v不是图G的顶点 
		return ERROR;
	p=(*G).vertices[j].firstarc; // 删除以v为出度的弧或边
	while(p){
		q=p;
		p=p->nextarc;
		if((*G).kind%2) //网 
			free(q->info);
		free(q);
		(*G).arcnum--; // 弧或边数减1 
	}
	(*G).vexnum--; // 顶点数减1 
	for(i=j;i<(*G).vexnum;i++) //顶点v后面的顶点前移 
		(*G).vertices[i]=(*G).vertices[i+1];
	//删除以v为入度的弧或边且必要时修改表结点的顶点位置值
	for(i=0;i<(*G).vexnum;i++) {
		p=(*G).vertices[i].firstarc; // 指向第1条弧或边 
		//有弧
		while(p){
			if(p->adjvex==j){
				//待删结点是第1个结点
				if(p==(*G).vertices[i].firstarc) {
					(*G).vertices[i].firstarc=p->nextarc;
					if((*G).kind%2) //网
						free(p->info);
					free(p);
					p=(*G).vertices[i].firstarc;
					if((*G).kind<2) //有向
						(*G).arcnum--; //弧或边数减1
				}
				else
				{
					q->nextarc=p->nextarc;
					if((*G).kind%2) //网
						free(p->info);
					free(p);
					p=q->nextarc;
					if((*G).kind<2) // 有向 
						(*G).arcnum--; //弧或边数减1 
				}
			}
			else{
				if(p->adjvex>j)
					p->adjvex--; // 修改表结点的顶点位置值(序号) 
				q=p;
				p=p->nextarc;
			}
		}
	}
	return OK;
}

// 初始条件: 图G存在,v和w是G中两个顶点
//操作结果: 在G中增添弧<v,w>,若G是无向的,则还增添对称弧<w,v> 
Status InsertArc(ALGraph *G,VertexType v,VertexType w)
{ 
	ArcNode *p;
	int w1,i,j;
	i=LocateVex(*G,v); //弧尾或边的序号 
	j=LocateVex(*G,w); //弧头或边的序号
	if(i<0||j<0)
		return ERROR;
	(*G).arcnum++; // 图G的弧或边的数目加1
	//网
	if((*G).kind%2)	{
		printf("请输入弧(边)%s→%s的权值: ",v,w);
		scanf("%d",&w1);
	}
	p=(ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex=j;
	//网 
	if((*G).kind%2) {
		p->info=(int*)malloc(sizeof(int));
		*(p->info)=w1;
	}
	else
		p->info=NULL;
	p->nextarc=(*G).vertices[i].firstarc; //插在表头 
	(*G).vertices[i].firstarc=p;
	//无向,生成另一个表结点
	if((*G).kind>=2){
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=i;
		// 无向网 
		if((*G).kind==3) {
			p->info=(int*)malloc(sizeof(int));
			*(p->info)=w1;
		}
		else
			p->info=NULL;
		p->nextarc=(*G).vertices[j].firstarc;//插在表头
		(*G).vertices[j].firstarc=p;
	}
	return OK;
}

//初始条件: 图G存在,v和w是G中两个顶点 
//操作结果: 在G中删除弧<v,w>,若G是无向的,则还删除对称弧<w,v> 
Status DeleteArc(ALGraph *G,VertexType v,VertexType w){	
	ArcNode *p,*q;
	int i,j;
	i=LocateVex(*G,v); //i是顶点v(弧尾)的序号 
	j=LocateVex(*G,w); //j是顶点w(弧头)的序号 
	if(i<0||j<0||i==j)
		return ERROR;
	p=(*G).vertices[i].firstarc; //p指向顶点v的第一条出弧
	//p不空且所指之弧不是待删除弧<v,w>
	while(p&&p->adjvex!=j) { 
		q=p;
		p=p->nextarc;//p指向下一条弧 

	}
	//找到弧<v,w> 
	if(p&&p->adjvex==j) {
		if(p==(*G).vertices[i].firstarc) //p所指是第1条弧 
			(*G).vertices[i].firstarc=p->nextarc; //指向下一条弧
		else
			q->nextarc=p->nextarc;// 指向下一条弧
		if((*G).kind%2)//网 
			free(p->info);
		free(p); //释放此结点 
		(*G).arcnum--; //弧或边数减1
	}
	//无向,删除对称弧<w,v>
	if((*G).kind>=2) {
		p=(*G).vertices[j].firstarc; // p指隙サ鉾的第一条出弧 
		//p不空且所指之弧不是待删除弧<w,v> 
		//p指向下一条弧
		while(p&&p->adjvex!=i) { 
			q=p;
			p=p->nextarc;
		}
		//找到弧<w,v> 
		if(p&&p->adjvex==i){
			if(p==(*G).vertices[j].firstarc) //p所指是第1条弧
				(*G).vertices[j].firstarc=p->nextarc; //指向下一条弧
			else
				q->nextarc=p->nextarc; //指向下一条弧
			if((*G).kind==3) //无向网
				free(p->info);
			free(p); //释放此结点
		}
	}
	return OK;
}

Boolean visited[MAX_VERTEX_NUM]; //访问标志数组(全局量)
void(*VisitFunc)(char* v); //函数变量(全局量) 

// 从第v个顶点出发递归地深度优先遍历图G。算法7.5
void DFS(ALGraph G,int v){ 
	int w;
	VertexType v1,w1;
	strcpy(v1,*GetVex(G,v));
	visited[v]=TRUE; //设置访问标志为TRUE(已访问)
	VisitFunc(G.vertices[v].data); // 访问第v个顶点
	for(w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,strcpy(w1,*GetVex(G,w))))
		if(!visited[w])
			DFS(G,w);//对v的尚未访问的邻接点w递归调用DFS
}

//对图G作深度优先遍历。算法7.4
void DFSTraverse(ALGraph G,void(*Visit)(char*)){ 
	printf("\n************************************************************************\n");
	printf("*深度优先遍历                                                          *\n");
	printf("************************************************************************\n");

	int v;
	VisitFunc=Visit; //使用全局变量VisitFunc,使DFS不必设函数指针参数
	for(v=0;v<G.vexnum;v++)
		visited[v]=FALSE; //访问标志数组初始化
	for(v=0;v<G.vexnum;v++)
		if(!visited[v])
			DFS(G,v); //对尚未访问的顶点调用DFS
	printf("\n");
}

typedef int QElemType; //队列类型 
#include "LinkQueue.h"

//按广度优先非递归遍历图G。使用辅助队列Q和访问标志数组visited。算法7.6 
void BFSTraverse(ALGraph G,void(*Visit)(char*)){
	printf("\n************************************************************************\n");
	printf("*广度优先遍历                                                          *\n");
	printf("************************************************************************\n");

	int v,u,w;
	VertexType u1,w1;
	LinkQueue Q;
	for(v=0;v<G.vexnum;++v)
		visited[v]=FALSE; //置初值 
	InitQueue(&Q);//置空的辅助队列Q
	for(v=0;v<G.vexnum;v++) //如果是连通图,只v=0就遍历全图
		//v尚未访问
		if(!visited[v]) {
			visited[v]=TRUE;
			Visit(G.vertices[v].data);
			EnQueue(&Q,v); //v入队列
			//队列不空
			while(!QueueEmpty(Q)){
				DeQueue(&Q,&u);//队头元素出队并置为u
				strcpy(u1,*GetVex(G,u));
				for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,*GetVex(G,w))))
					//w为u的尚未访问的邻接顶点
					if(!visited[w]){
						visited[w]=TRUE;
						Visit(G.vertices[w].data);
						EnQueue(&Q,w); //w入队
					}
			}
		}
		printf("\n");
}


//输出图的邻接表
void Display(ALGraph G){
	int i;
	ArcNode *p;
	char *kind;
	switch(G.kind){
	case DG: 
		kind="有向图";
		break;
	case DN: 
		kind="有向网";
		break;
	case UDG: 
		kind="无向图";
		break;
	case UDN: 
		kind="无向网";
	}
	printf("\n************************************************************************\n");
	printf("*输出%s的邻接表                                                    *\n",kind);
	printf("************************************************************************\n");

	//输出顶点信息
	printf("%d个顶点：\n",G.vexnum);
	for(i=0;i<G.vexnum;++i)
		printf("%s ",G.vertices[i].data);

	//输出弧（边）的信息
	printf("\n%d条弧(边):\n",G.arcnum);
	for(i=0;i<G.vexnum;i++){
		p=G.vertices[i].firstarc;
		while(p){
			//有向
			if(G.kind<=1) {
				printf("%s→%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
				if(G.kind==DN) //网
					printf(":%d ",*(p->info));
			}
			//无向(避免输出两次) 
			else {
				if(i<p->adjvex){
					printf("%s－%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
					if(G.kind==UDN) //网
						printf(":%d ",*(p->info));
				}
			}
			p=p->nextarc;
		}
		printf("\n");
	}
}
