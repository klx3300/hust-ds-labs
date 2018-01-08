#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXISTCHK(gdptr) (gdptr->inited == 19090)
#define EXISTSET(gdptr) (gdptr->inited = 19090)

int InitGraph(GraphDescriptor *desc,int isdirected){
    if(EXISTCHK(desc)) return FAILURE;
    EXISTSET(desc);
    desc->directed = isdirected;
    desc->vertices = qVector_constructor(sizeof(GraphVertex));
    return SUCCESS;
}

int CreateGraph(GraphDescriptor *desc,int isdirected,int* vertices,int vsz,int* edges,int esz){
    if(InitGraph(desc,isdirected) == FAILURE) return FAILURE;
    for(int i=0;i<vsz;i++){
        InsertVex(desc,vertices[i]);
    }
    for(int i=0;i<esz;i+=3){
        InsertArc(desc,edges[i],edges[i+1],edges[i+2],1);
    }
    return SUCCESS;
}

int DestroyGraph(GraphDescriptor *desc){
    if(!EXISTCHK(desc)) return FAILURE;
    // destroy all lists
    for(qVectorIterator i=qVector_begin(desc->vertices);qVectorIterator_isvalid(i);i=qVectorIterator_move(i,1)){
        GraphVertex *v = qVectorIterator_deref(i);
        qList_destructor(v->edges);
    }
    qVector_destructor(desc->vertices);
    desc->inited = 0;
    return SUCCESS;
}

GraphVertex* LocateVex(GraphDescriptor *desc,int index){
    if(!EXISTCHK(desc)) return NULL;
    qVectorIterator i = qVectorIterator_move(qVector_begin(desc->vertices),index);
    if(qVectorIterator_isvalid(i)) return qVectorIterator_deref(i);
    return NULL;
}

int GetIndex(GraphDescriptor *desc,int value,int* ind){
    if(!EXISTCHK(desc)) return FAILURE;
    for(qVectorIterator i = qVector_begin(desc->vertices);
        qVectorIterator_isvalid(i);
        i = qVectorIterator_move(i,1)){
            GraphVertex *vert = qVectorIterator_deref(i);
            if(vert->value == value){
                *ind = qVectorIterator_diff(i,qVector_begin(desc->vertices));
                return SUCCESS;
            }
    }
    return FAILURE;
}

int GetValue(GraphDescriptor *desc,int index,int* v){
    if(!EXISTCHK(desc)) return FAILURE;
    GraphVertex *vert = LocateVex(desc,index);
    if(vert == NULL) return FAILURE;
    *v = vert->value;
    return SUCCESS;
}

int PutValue(GraphDescriptor *desc,int index,int v){
    if(!EXISTCHK(desc)) return FAILURE;
    GraphVertex *vert = LocateVex(desc,index);
    if(vert == NULL) return FAILURE;
    vert->value = v;
    return SUCCESS;
}

GraphEdge* FirstAdjVex(GraphDescriptor *desc,int index){
    if(!EXISTCHK(desc)) return NULL;
    GraphVertex *vert = LocateVex(desc,index);
    if(vert == NULL) return NULL;
    return vert->edges.head->data;
}
GraphEdge* NextAdjVex(GraphDescriptor* desc,int index,int prevex){
    if(!EXISTCHK(desc)) return NULL;
    GraphVertex *vert = LocateVex(desc,index);
    if(vert == NULL) return NULL;
    qList_foreach(vert->edges,eiter){
        GraphEdge *tmpedg = eiter->data;
        if(tmpedg->destination == prevex){
            return eiter->next==NULL?NULL:eiter->next->data;
        }
    }
    return NULL;
}

int InsertVex(GraphDescriptor* desc,int value){
    if(!EXISTCHK(desc)) return FAILURE;
    GraphVertex tmpvert;
    tmpvert.value = value;
    qList_initdesc(tmpvert.edges);
    qVector_push_back(desc->vertices,tmpvert);
    return SUCCESS;
}
int DeleteVex(GraphDescriptor* desc,int index){
    if(!EXISTCHK(desc)) return FAILURE;
    // gotta keep the edges correct after deletion
    // 1. iter through all edges,
    //    remove ones that corr to this
    //    and decrease larger ones
    for(qVectorIterator i = qVector_begin(desc->vertices);
        qVectorIterator_isvalid(i);
        i = qVectorIterator_move(i,1)){
            GraphVertex *vert = qVectorIterator_deref(i);
            qList_foreach(vert->edges,eiter){
                REJUDGE:;
                GraphEdge *edg = eiter->data;
                if(edg->destination == index){
                    qListIterator tmpeiter = eiter->next;
                    qList_erase_elem(vert->edges,eiter);
                    eiter = tmpeiter;
                    if(eiter == NULL) break;
                    goto REJUDGE;
                }
                if(edg->destination > index){
                    edg->destination--;
                }
            }
    }
    // 2. delete it from vertices list
    qVectorIterator deltarget = qVectorIterator_move(qVector_begin(desc->vertices),index);
    qList_destructor(((GraphVertex*)qVectorIterator_deref(deltarget))->edges);
    qVector_erase(desc->vertices,deltarget);
    return SUCCESS;
}

int InsertArc(GraphDescriptor* desc,int srcindex,int dstindex,int priority,int WILLCHK){
    if(!EXISTCHK(desc)) return FAILURE;
    if(WILLCHK && !desc->directed){
        InsertArc(desc,dstindex,srcindex,priority,0);
    }
    GraphEdge tmpedg;
    tmpedg.destination = dstindex;
    tmpedg.priority = priority;
    GraphVertex *vert = LocateVex(desc,srcindex);
    if(vert == NULL) return FAILURE;
    return qList_push_back(vert->edges,tmpedg) == 0?SUCCESS:FAILURE;
}
int DeleteArc(GraphDescriptor* desc,int srcindex,int dstindex,int WILLCHK){
    if(!EXISTCHK(desc)) return FAILURE;
    if(WILLCHK && !desc->directed){
        DeleteArc(desc,dstindex,srcindex,0);
    }
    GraphVertex *vert = LocateVex(desc,srcindex);
    if(vert == NULL) return FAILURE;
    qList_foreach(vert->edges,eiter){
        GraphEdge *edg = eiter->data;
        if(edg->destination == dstindex){
            qList_erase_elem(vert->edges,eiter);
            return SUCCESS;
        }
    }
    return FAILURE;
}

void DFSTraverse_recursive(GraphDescriptor* desc,int vexindex,qVectorDescriptor* visited,Visitor visitor,void* extrargs){
    if(*(int*)qVectorIterator_deref(qVectorIterator_move(qVector_begin(*visited),vexindex)))
        return; // visited already
    *(int*)qVectorIterator_deref(qVectorIterator_move(qVector_begin(*visited),vexindex)) = 1;
    GraphVertex *vert = LocateVex(desc,vexindex);
    if(vert == NULL) return;
    visitor(vert,extrargs);
    qList_foreach(vert->edges,eiter){
        GraphEdge *edg = eiter->data;
        DFSTraverse_recursive(desc,edg->destination,visited,visitor,extrargs);
    }
}

void printOnVisit(GraphVertex* v,void* extrargs){
    printf("%d ",v->value);
}

int DFSTraverse(GraphDescriptor* desc,Visitor visitor){
    if(!EXISTCHK(desc)) return FAILURE;
    qVectorDescriptor visited = qVector_constructor(sizeof(int));
    for(int i=0;i<*(desc->vertices.size);i++){
        int k = 0;
        qVector_push_back(visited,k);
    }
    DFSTraverse_recursive(desc,0,&visited,printOnVisit,NULL);
    printf("\n");
    return SUCCESS;
}

int BFSTraverse(GraphDescriptor* desc,Visitor visitor){
    if(!EXISTCHK(desc)) return FAILURE;
    qVectorDescriptor visited = qVector_constructor(sizeof(int));
    for(int i=0;i<*(desc->vertices.size);i++){
        int k = 0;
        qVector_push_back(visited,k);
    }
    qListDescriptor currlist,nextlist;
    qList_initdesc(currlist);
    qList_initdesc(nextlist);
    int tmp = 0;
    qList_push_back(currlist,tmp);
    while(currlist.size){
        qList_foreach(currlist,viter){
            int *vertindex = viter->data;
            if(*(int*)qVectorIterator_deref(qVectorIterator_move(qVector_begin(visited),*vertindex)))
                continue; // visited already
            GraphVertex *vert = LocateVex(desc,*vertindex);
            if(vert == NULL) continue;
            *(int*)qVectorIterator_deref(qVectorIterator_move(qVector_begin(visited),*vertindex)) = 1;
            printOnVisit(vert,NULL);
            qList_foreach(vert->edges,eiter){
                GraphEdge *edg = eiter->data;
                qList_push_back(nextlist,edg->destination);
            }
        }
        qList_destructor(currlist);
        currlist = nextlist;
        qList_initdesc(nextlist);
    }
    printf("\n");
    return SUCCESS;
}
