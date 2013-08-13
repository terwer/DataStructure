/************************************************************************/
/*图的邻接表存储表示                                                     */
/************************************************************************/
#define MAX_NAME 3 //顶点字符串的最大长度+1 
typedef int InfoType; //存放网的权值
typedef char VertexType[MAX_NAME]; //字符串类型
#define MAX_VERTEX_NUM 20
#define  OK 1
#define  FALSE 0
typedef int Status;
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum{DG,DN,UDG,UDN}GraphKind; //{有向图,有向网,无向图,无向网}
typedef struct ArcNode{
	int adjvex; //该弧所指向的顶点的位置
	struct ArcNode *nextarc; //指向下一条弧的指针
	InfoType *info; //网的权值指针） 
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
		printf("请输入第%d个顶点的值(<%d个字符):\n",i+1);
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

//输出图的邻接表
void Display(ALGraph G){
	int i;
	ArcNode *p;
	switch(G.kind){
	case DG: printf("有向图\n");
		break;
	case DN: printf("有向网\n");
		break;
	case UDG: printf("无向图\n");
		break;
	case UDN: printf("无向网\n");
	}
	printf("%d个顶点：\n",G.vexnum);
	for(i=0;i<G.vexnum;++i)
		printf("%s ",G.vertices[i].data);
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
