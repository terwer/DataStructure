/************************************************************************/
/*无向图的邻接多重表存储表示                                              */
/************************************************************************/
#define MAX_VERTEX_NUM 20
#define MAX_NAME 3 //顶点字符串的最大长度+1
#define MAX_INFO 80 //相关信息字符串的最大长度+1
#define  OK 1
#define  ERROR 0
#define  TRUE 1
#define  FALSE 0
typedef char InfoType;
typedef char VertexType[MAX_NAME]; //字符串类型
typedef enum{unvisited,visited}VisitIf;
typedef int Status;
typedef int Boolean;
#include <string.h>

typedef struct EBox{
	VisitIf mark; //访问标记 
	int ivex,jvex; //该边依附的两个顶点的位置
	struct EBox *ilink,*jlink; //分别指向依附这两个顶点的下一条边
	InfoType *info; //该边信息指针
}EBox;

typedef struct{
	VertexType data;
	EBox *firstedge; //指向第一条依附该顶点的边
}VexBox;

typedef struct{
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum,edgenum; //无向图的当前顶点数和边数
}AMLGraph;

/************************************************************************/
/*无向图的邻接多重表存储的基本函数类型(16个)                               */
/************************************************************************/ 

//初始条件: 无向图G存在,u和G中顶点有相同特征
//操作结果: 若G中存在顶点u,则返回该顶点在无向图中位置;否则返回-1
int LocateVex(AMLGraph G,VertexType u){ 
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.adjmulist[i].data)==0)
			return i;
	return -1;
}

//采用邻接多重表存储结构,构造无向图G
Status CreateGraph(AMLGraph *G){ 
	int i,j,k,l,IncInfo;
	char s[MAX_INFO];
	VertexType va,vb;
	EBox *p;
	printf("请输入无向图G的顶点数、边数、边是否含其它信息(是:1，否:0): ");
	scanf("%d%d%d",&(*G).vexnum,&(*G).edgenum,&IncInfo);
	//构造顶点向量
	for(i=0;i<(*G).vexnum;++i) {
		printf("请输入第%d个顶点的值(<%d个字符):\n",i+1,MAX_NAME);
		scanf("%s",(*G).adjmulist[i].data);
		(*G).adjmulist[i].firstedge=NULL;
	}
	//构造表结点链表
	for(k=0;k<(*G).edgenum;++k) 
	{
		printf("请顺序输入第%d条边的两个端点(以空格作为间隔):\n",k+1);
		scanf("%s%s",va,vb); 
		i=LocateVex(*G,va); //一端 
		j=LocateVex(*G,vb); //另一端 
		p=(EBox*)malloc(sizeof(EBox));
		p->mark=unvisited; //设初值
		p->ivex=i;
		p->jvex=j;
		p->info=NULL;
		p->ilink=(*G).adjmulist[i].firstedge; //插在表头
		(*G).adjmulist[i].firstedge=p;
		p->jlink=(*G).adjmulist[j].firstedge; //插在表头
		(*G).adjmulist[j].firstedge=p;
		 //边有相关信息
		if(IncInfo){
			printf("请输入该弧的相关信息(<%d个字符)：",MAX_INFO);
			gets(s);
			l=strlen(s);
			if(l){
				p->info=(char*)malloc((l+1)*sizeof(char));
				strcpy(p->info,s);
			}
		}
	}
	return OK;
}

//初始条件: 无向图G存在,v是G中某个顶点的序号。
//操作结果: 返回v的值 
VertexType* GetVex(AMLGraph G,int v){
	if(v>=G.vexnum||v<0)
		exit(ERROR);
	return &G.adjmulist[v].data;
}

//初始条件: 无向图G存在,v是G中某个顶点 
//操作结果: 对v赋新值value 
Status PutVex(AMLGraph *G,VertexType v,VertexType value){ 
	int i;
	i=LocateVex(*G,v);
	if(i<0) //v不是G的顶点
		return ERROR;
	strcpy((*G).adjmulist[i].data,value);
	return OK;
}

//初始条件: 无向图G存在,v是G中某个顶点
//操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1
int FirstAdjVex(AMLGraph G,VertexType v){ 
	int i;
	i=LocateVex(G,v);
	if(i<0)
		return -1;
	if(G.adjmulist[i].firstedge) //v有邻接顶点 
		if(G.adjmulist[i].firstedge->ivex==i)
			return G.adjmulist[i].firstedge->jvex;
		else
			return G.adjmulist[i].firstedge->ivex;
	else
		return -1;
}

//初始条件: 无向图G存在,v是G中某个顶点,w是v的邻接顶点 
//操作结果: 返回v的(相对于w的)下一个邻接顶点的序号。
//若w是v的最后一个邻接点,则返回-1 
int NextAdjVex(AMLGraph G,VertexType v,VertexType w){
	int i,j;
	EBox *p;
	i=LocateVex(G,v); //i是顶点v的序号 
	j=LocateVex(G,w); //j是顶点w的序号 
	if(i<0||j<0) //v或w不是G的顶点
		return -1;
	p=G.adjmulist[i].firstedge; //p指向顶点v的第1条边
	while(p)
		if(p->ivex==i&&p->jvex!=j) //不是邻接顶点w(情况1)
			p=p->ilink; //找下一个邻接顶点
		else if(p->jvex==i&&p->ivex!=j) //不是邻接顶点w(情况2) 
			p=p->jlink; /* 找下一个邻接顶点 */
		else //是邻接顶点w
			break;
		//找到邻接顶点w(情况1)
		if(p&&p->ivex==i&&p->jvex==j) {
			p=p->ilink;
			if(p&&p->ivex==i)
				return p->jvex;
			else if(p&&p->jvex==i)
				return p->ivex;
		}
		//找到邻接顶点w(情况2)
		if(p&&p->ivex==j&&p->jvex==i) {
			p=p->jlink;
			if(p&&p->ivex==i)
				return p->jvex;
			else if(p&&p->jvex==i)
				return p->ivex;
		}
		return -1;
}

//初始条件: 无向图G存在,v和G中顶点有相同特征
//操作结果: 在G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做)
Status InsertVex(AMLGraph *G,VertexType v){ 
	if((*G).vexnum==MAX_VERTEX_NUM) //结点已满，不能插入
		return ERROR;
	if(LocateVex(*G,v)>=0) //结点已存在,不能插入
		return ERROR;
	strcpy((*G).adjmulist[(*G).vexnum].data,v);
	(*G).adjmulist[(*G).vexnum].firstedge=NULL;
	(*G).vexnum++;
	return OK;
}

//初始条件: 无向图G存在,v和w是G中两个顶点
//操作结果: 在G中删除弧<v,w> */
Status DeleteArc(AMLGraph *G,VertexType v,VertexType w){ 
	int i,j;
	EBox *p,*q;
	i=LocateVex(*G,v);
	j=LocateVex(*G,w);
	if(i<0||j<0||i==j)
		return ERROR;  //图中没有该点或弧 
	//以下使指向待删除边的第1个指针绕过这条边
	p=(*G).adjmulist[i].firstedge; //p指向顶点v的第1条边
	if(p&&p->jvex==j) //第1条边即为待删除边(情况1)
		(*G).adjmulist[i].firstedge=p->ilink;
	else if(p&&p->ivex==j) //第1条边即为待删除边(情况2) 
		(*G).adjmulist[i].firstedge=p->jlink;
	//第1条边不是待删除边
	else {
		//向后查找弧<v,w>
		while(p) {
			//不是待删除边 
			if(p->ivex==i&&p->jvex!=j) {
				q=p;
				p=p->ilink; //找下一个邻接顶点
			}
			//不是待删除边 
			else if(p->jvex==i&&p->ivex!=j) {
				q=p;
				p=p->jlink; //找下一个邻接顶点
			}
			else //是邻接顶点w
				break;
		}
		if(!p) //没找到该边
			return ERROR;
		if(p->ivex==i&&p->jvex==j) //找到弧<v,w>(情况1) 
			if(q->ivex==i)
				q->ilink=p->ilink;
			else
				q->jlink=p->ilink;
		else if(p->ivex==j&&p->jvex==i) //找到弧<v,w>(情况2) 
			if(q->ivex==i)
				q->ilink=p->jlink;
			else
				q->jlink=p->jlink;
	}
	//以下由另一顶点起找待删除边且删除之 
	p=(*G).adjmulist[j].firstedge; //p指向顶点w的第1条边 
	//第1条边即为待删除边(情况1)
	if(p->jvex==i) {
		(*G).adjmulist[j].firstedge=p->ilink;
		if(p->info) //有相关信息
			free(p->info);
		free(p);
	}
	//第1条边即为待删除边(情况2)
	else if(p->ivex==i) {
		(*G).adjmulist[j].firstedge=p->jlink;
		if(p->info) //有相关信息 
			free(p->info);
		free(p);
	}
	//第1条边不是待删除边
	else {
		//向后查找弧<v,w>
		while(p)
			//不是待删除边
			if(p->ivex==j&&p->jvex!=i) {
				q=p;
				p=p->ilink; //找下一个邻接顶点
			}
			//不是待删除边
			else if(p->jvex==j&&p->ivex!=i) {
				q=p;
				p=p->jlink; //找下一个邻接顶点
			}
			else //是邻接顶点v
				break;
			 //找到弧<v,w>(情况1)
			if(p->ivex==i&&p->jvex==j){
				if(q->ivex==j)
					q->ilink=p->jlink;
				else
					q->jlink=p->jlink;
				if(p->info) //有相关信息
					free(p->info);
				free(p);
			}
			//找到弧<v,w>(情况2)
			else if(p->ivex==j&&p->jvex==i) {
				if(q->ivex==j)
					q->ilink=p->ilink;
				else
					q->jlink=p->ilink;
				if(p->info) //有相关信息
					free(p->info);
				free(p);
			}
	}
	(*G).edgenum--;
	return OK;
}

//初始条件: 无向图G存在,v是G中某个顶点 
//操作结果: 删除G中顶点v及其相关的边 
Status DeleteVex(AMLGraph *G,VertexType v){ 
	int i,j;
	VertexType w;
	EBox *p;
	i=LocateVex(*G,v); //i为待删除顶点的序号
	if(i<0)
		return ERROR;
	//删除与顶点v相连的边(如果有的话)
	for(j=0;j<(*G).vexnum;j++) {
		if(j==i)
			continue;
		strcpy(w,*GetVex(*G,j)); //w是第j个顶点的值
		DeleteArc(G,v,w);
	}
	for(j=i+1;j<(*G).vexnum;j++) //排在顶点v后面的顶点的序号减1
		(*G).adjmulist[j-1]=(*G).adjmulist[j];
	(*G).vexnum--; //顶点数减1 
	//修改顶点的序号
	for(j=i;j<(*G).vexnum;j++) {
		p=(*G).adjmulist[j].firstedge;
		if(p){
			if(p->ivex==j+1){
				p->ivex--;
				p=p->ilink;
			}
			else{
				p->jvex--;
				p=p->jlink;
			}
		}
	}
	return OK;
}

//销毁无向图
void DestroyGraph(AMLGraph *G){
	int i;
	for(i=(*G).vexnum-1;i>=0;i--)
		DeleteVex(G,(*G).adjmulist[i].data);
}

//初始条件: 无向图G存在,v和W是G中两个顶点
//操作结果: 在G中增添弧<v,w> 
Status InsertArc(AMLGraph *G,VertexType v,VertexType w){
	int i,j,l,IncInfo;
	char s[MAX_INFO];
	EBox *p;
	i=LocateVex(*G,v); //一端
	j=LocateVex(*G,w); //另一端
	if(i<0||j<0)
		return ERROR;
	p=(EBox*)malloc(sizeof(EBox));
	p->mark=unvisited;
	p->ivex=i;
	p->jvex=j;
	p->info=NULL;
	p->ilink=(*G).adjmulist[i].firstedge; //插在表头
	(*G).adjmulist[i].firstedge=p;
	p->jlink=(*G).adjmulist[j].firstedge; //插在表头
	(*G).adjmulist[j].firstedge=p;
	printf("该边是否有相关信息(1:有 0:无): ");
	scanf("%d%*c",&IncInfo); //吃掉回车符 
	 //边有相关信息
	if(IncInfo){
		printf("请输入该边的相关信息(<%d个字符)：",MAX_INFO);
		gets(s);
		l=strlen(s);
		if(l){
			p->info=(char*)malloc((l+1)*sizeof(char));
			strcpy(p->info,s);
		}
	}
	(*G).edgenum++;
	return OK;
}

Boolean visite[MAX_VERTEX_NUM]; /* 访问标志数组(全局量) */
Status(*VisitFunc)(VertexType v);

void DFS(AMLGraph G,int v){
	int j;
	EBox *p;
	VisitFunc(G.adjmulist[v].data);
	visite[v]=TRUE;
	p=G.adjmulist[v].firstedge;
	while(p){
		j=p->ivex==v?p->jvex:p->ivex;
		if(!visite[j])
			DFS(G,j);
		p=p->ivex==v?p->ilink:p->jlink;
	}
}

//初始条件: 图G存在,Visit是顶点的应用函数。算法7.4 
//操作结果: 从第1个顶点起,深度优先遍历图G,并对每个顶点调用函数Visit 
//一次且仅一次。一旦Visit()失败,则操作失败 
void DFSTraverse(AMLGraph G,Status(*visit)(VertexType)){ 
	printf("\n************************************************************************\n");
	printf("*深度优先遍历                                                          *\n");
	printf("************************************************************************\n");

	int v;
	VisitFunc=visit;
	for(v=0;v<G.vexnum;v++)
		visite[v]=FALSE;
	for(v=0;v<G.vexnum;v++)
		if(!visite[v])
			DFS(G,v);
	printf("\n");
}

typedef int QElemType; //队列类型
#include "LinkQueue.h" //BFSTraverse()用 

//初始条件: 图G存在,Visit是顶点的应用函数。算法7.6 
//操作结果: 从第1个顶点起,按广度优先非递归遍历图G,并对每个顶点调用函数 
//Visit一次且仅一次。一旦Visit()失败,则操作失败。
//使用辅助队列Q和访问标志数组visite
void BFSTraverse(AMLGraph G,Status(*Visit)(VertexType))
{
	printf("\n************************************************************************\n");
    printf("*广度优先遍历                                                          *\n");
    printf("************************************************************************\n");

	int v,u,w;
	VertexType w1,u1;
	LinkQueue Q;
	for(v=0;v<G.vexnum;v++)
		visite[v]=FALSE; //置初值 
	InitQueue(&Q); //置空的辅助队列Q 
	for(v=0;v<G.vexnum;v++)
		//v尚未访问 
		if(!visite[v]) {
			visite[v]=TRUE; //设置访问标志为TRUE(已访问) 
			Visit(G.adjmulist[v].data);
			EnQueue(&Q,v); //v入队列 
			//队列不空
			while(!QueueEmpty(Q)) {
				DeQueue(&Q,&u); //队头元素出队并置为u
				strcpy(u1,*GetVex(G,u));
				for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,*GetVex(G,w))))
					//w为u的尚未访问的邻接顶点的序号
					if(!visite[w]) {
						visite[w]=TRUE;
						Visit(G.adjmulist[w].data);
						EnQueue(&Q,w);
					}
			}
		}
		printf("\n");
}

//置边的访问标记为未被访问
void MarkUnvizited(AMLGraph G){ 
	int i;
	EBox *p;
	for(i=0;i<G.vexnum;i++){
		p=G.adjmulist[i].firstedge;
		while(p){
			p->mark=unvisited;
			if(p->ivex==i)
				p=p->ilink;
			else
				p=p->jlink;
		}
	}
}

//输出无向图的邻接多重表G 
void Display(AMLGraph G)
{ 	
	printf("\n************************************************************************\n");
    printf("*输出无向图的邻接多重表                                                *\n");
    printf("************************************************************************\n");
	int i;
	EBox *p;
	MarkUnvizited(G); //置边的访问标记为未被访问
	printf("%d个顶点：\n",G.vexnum);
	for(i=0;i<G.vexnum;++i)
		printf("%s ",G.adjmulist[i].data);
	printf("\n%d条边:\n",G.edgenum);
	for(i=0;i<G.vexnum;i++)
	{
		p=G.adjmulist[i].firstedge;
		while(p)
			//边的i端与该顶点有关
			if(p->ivex==i) {
				//只输出一次 
				if(!p->mark){
					printf("%s－%s ",G.adjmulist[i].data,G.adjmulist[p->jvex].data);
					p->mark=visited;
					if(p->info) //输出附带信息
						printf("相关信息: %s ",p->info);
				}
				p=p->ilink;
			}
			//边的j端与该顶点有关 
			else {
				//只输出一次 
				if(!p->mark) {
					printf("%s－%s ",G.adjmulist[p->ivex].data,G.adjmulist[i].data);
					p->mark=visited;
					if(p->info) //输出附带信息
						printf("相关信息: %s ",p->info);
				}
				p=p->jlink;
			}
			printf("\n");
	}
}
