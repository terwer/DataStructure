/************************************************************************/
/*ͼ���ڽӱ�洢��ʾ                                                     */
/************************************************************************/
#define MAX_NAME 3 //�����ַ�������󳤶�+1 
typedef int InfoType; //�������Ȩֵ
typedef char VertexType[MAX_NAME]; //�ַ�������
#define MAX_VERTEX_NUM 20
#define  OK 1
#define  FALSE 0
typedef int Status;
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum{DG,DN,UDG,UDN}GraphKind; //{����ͼ,������,����ͼ,������}
typedef struct ArcNode{
	int adjvex; //�û���ָ��Ķ����λ��
	struct ArcNode *nextarc; //ָ����һ������ָ��
	InfoType *info; //����Ȩֵָ�룩 
}ArcNode; //����

typedef struct{
	VertexType data; //������Ϣ
	ArcNode *firstarc; //��һ������ĵ�ַ,ָ���һ�������ö���Ļ���ָ��
}VNode,AdjList[MAX_VERTEX_NUM]; // ͷ���

typedef struct{
	AdjList vertices;
	int vexnum,arcnum; //ͼ�ĵ�ǰ�������ͻ��� 
	int kind; //ͼ�������־
}ALGraph;

/************************************************************************/
/*ͼ���ڽӱ�洢�Ļ�������(15��)                                          */
/************************************************************************/ 

//��ʼ����: ͼG����,u��G�ж�������ͬ����
//�������: ��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 
int LocateVex(ALGraph G,VertexType u){
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.vertices[i].data)==0)
			return i;
	return -1;
}

//�����ڽӱ�洢�ṹ,����û�������Ϣ��ͼG(��һ����������4��ͼ) 
Status CreateGraph(ALGraph *G){ 
	int i,j,k;
	int w; //Ȩֵ 
	VertexType va,vb;
	ArcNode *p;
	printf("������ͼ������:\n0:����ͼ\n1:������\n2:����ͼ\n3:������\n");
	scanf("%d",&(*G).kind);
	printf("������ͼ�Ķ�����,����: ");
	scanf("%d%d",&(*G).vexnum,&(*G).arcnum);
	//���춥������
	for(i=0;i<(*G).vexnum;++i) {
		printf("�������%d�������ֵ(<%d���ַ�):\n",i+1);
		scanf("%s",(*G).vertices[i].data);
		(*G).vertices[i].firstarc=NULL;
	}
	if((*G).kind==1||(*G).kind==3) //��
		printf("��˳������ÿ����(��)��Ȩֵ����β�ͻ�ͷ(�Կո���Ϊ���):\n");
	else //ͼ
		printf("��˳������ÿ����(��)�Ļ�β�ͻ�ͷ(�Կո���Ϊ���):\n");
	//�����������
	for(k=0;k<(*G).arcnum;++k) {
		if((*G).kind==1||(*G).kind==3) //��
			scanf("%d%s%s",&w,va,vb);
		else //ͼ
			scanf("%s%s",va,vb);
		i=LocateVex(*G,va); //��β
		j=LocateVex(*G,vb); //��ͷ
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j;
		//�� 
		if((*G).kind==1||(*G).kind==3){
			p->info=(int *)malloc(sizeof(int));
			*(p->info)=w;
		}
		else
			p->info=NULL; //ͼ
		p->nextarc=(*G).vertices[i].firstarc; //���ڱ�ͷ
		(*G).vertices[i].firstarc=p;
		//����ͼ����,�����ڶ������� *
		if((*G).kind>=2){
			p=(ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex=i;
			//������
			if((*G).kind==3) {
				p->info=(int*)malloc(sizeof(int));
				*(p->info)=w;
			}
			else
				p->info=NULL; //����ͼ
			p->nextarc=(*G).vertices[j].firstarc; //���ڱ�ͷ
			(*G).vertices[j].firstarc=p;
		}
	}
	return OK;
}

//���ͼ���ڽӱ�
void Display(ALGraph G){
	int i;
	ArcNode *p;
	switch(G.kind){
	case DG: printf("����ͼ\n");
		break;
	case DN: printf("������\n");
		break;
	case UDG: printf("����ͼ\n");
		break;
	case UDN: printf("������\n");
	}
	printf("%d�����㣺\n",G.vexnum);
	for(i=0;i<G.vexnum;++i)
		printf("%s ",G.vertices[i].data);
	printf("\n%d����(��):\n",G.arcnum);
	for(i=0;i<G.vexnum;i++){
		p=G.vertices[i].firstarc;
		while(p){
			//����
			if(G.kind<=1) {
				printf("%s��%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
				if(G.kind==DN) //��
					printf(":%d ",*(p->info));
			}
			//����(�����������) 
			else {
				if(i<p->adjvex){
					printf("%s��%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
					if(G.kind==UDN) //��
						printf(":%d ",*(p->info));
				}
			}
			p=p->nextarc;
		}
		printf("\n");
	}
}
