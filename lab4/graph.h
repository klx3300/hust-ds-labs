#ifndef HUST_DS_LAB_GRAPH_H
#define HUST_DS_LAB_GRAPH_H

#include "qVector.h"
#include "qList.h"

struct q_graph_vertex_st{
    qListDescriptor edges;
    int value;
};

struct q_graph_edge_st{
    int priority;
    int destination;
};

struct q_graph_desc_st{
    qVectorDescriptor vertices;
    int directed;
    int inited;
};

typedef struct q_graph_desc_st GraphDescriptor;
typedef struct q_graph_vertex_st GraphVertex;
typedef struct q_graph_edge_st GraphEdge;

typedef void (*Visitor)(GraphVertex* v,void* extrargs);

// ------------------------ garbage definitions

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0

// ------------------------ function protos

int InitGraph(GraphDescriptor *desc,int isdirected);

int CreateGraph(GraphDescriptor *desc,int isdirected,int* vertices,int vsz,int* edges,int esz);

int DestroyGraph(GraphDescriptor *desc);

GraphVertex* LocateVex(GraphDescriptor *desc,int i);

int GetIndex(GraphDescriptor *desc,int value,int* i);

int GetValue(GraphDescriptor *desc,int index,int* v);
int PutValue(GraphDescriptor *desc,int index,int v);

GraphEdge* FirstAdjVex(GraphDescriptor *desc,int index);
GraphEdge* NextAdjVex(GraphDescriptor* desc,int index,int prevex);

int InsertVex(GraphDescriptor* desc,int value);
int DeleteVex(GraphDescriptor* desc,int index);

int InsertArc(GraphDescriptor* desc,int srcindex,int dstindex,int priority,int WILLCHK);
int DeleteArc(GraphDescriptor* desc,int srcindex,int dstindex,int WILLCHK);

int DFSTraverse(GraphDescriptor* desc,Visitor visitor);
int BFSTraverse(GraphDescriptor* desc,Visitor visitor);

#endif