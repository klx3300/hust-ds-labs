#include "linked_list.h"
#include <stdlib.h>
#include <string.h>
#include "log.h"

typedef int (*Comparator)(int,int);
typedef void (*Visitor)(int);

typedef LkList* LkListIterator;
#define HUST_DS_STARTPOS 1

#define ALLOCCHK(clvar,size) do{(clvar)=(LkList*)malloc(size);if((clvar) == NULL){return FAILURE;}}while(0)
#define ZEROINIT(ptr,size) memset(ptr,0,size)

#define DEFALLOC(ptr,size) ALLOCCHK(ptr,size);ZEROINIT(ptr,size);

#define INITCHECK(lst) do{if((lst).next == NULL) return FAILURE;}while(0)

#define INITPRCHECK(lst) do{if((lst).next == NULL) qLogFail("List uninitialized.");}while(0)

#define OVERFLOW(lst,index) do{if((lst).elem <= ((index)-HUST_DS_STARTPOS)){return FAILURE;}}while(0)
#define INSOVERFLOW(lst,index) do{if((lst).elem < ((index)-HUST_DS_STARTPOS)){return FAILURE;}}while(0)

int InitaList(LkList* l){
    if(l->next != NULL){
        // previously inited
        return FAILURE;
    }
    l->elem = 0;
    DEFALLOC(l->next,sizeof(LkList));
    return SUCCESS;
}

int DestroyList(LkList* l){
    if(l->next == NULL){
        return FAILURE;
    }
    DestroyList(l->next);
    free(l->next);
    l->next = NULL;
    return SUCCESS;
}

int ClearList(LkList* l){
    INITCHECK(*l);
    for(LkListIterator iter = l->next;iter->next != NULL;){
        LkListIterator next = iter->next;
        free(iter);
        l->next=next;
        iter=next;
    }
    l->elem = 0;
    return SUCCESS;
} 

int ListEmpty(LkList* l){
    INITPRCHECK(*l);
    return l->elem == 0;
}

int ListLength(LkList* l){
    INITPRCHECK(*l);
    return l->elem;
}

int GetElem(LkList* l,int pos,int* retpos){
    INITCHECK(*l);
    OVERFLOW(*l,pos);
    int iterpos = HUST_DS_STARTPOS;
    for(LkListIterator iter = l->next;iter->next!=NULL;iter=iter->next){
        if(iterpos == pos){
            *retpos = iter->elem;
            return SUCCESS;
        }
        iterpos++;
    }
    return FAILURE;
}

int LocateElem(LkList *l,int elem,Comparator cmp){
    INITCHECK(*l);
    int iterpos = HUST_DS_STARTPOS;
    for(LkListIterator iter=l->next;iter->next != NULL;iter=iter->next){
        if(cmp(iter->elem,elem)){
            // get
            return iterpos;
        }
        iterpos++;
    }
    return 0;
}

int PriorElem(LkList* l,int cur_e,int* prev_e){
    INITCHECK(*l);
    LkListIterator iter = l->next;
    for(;iter->next->next!=NULL;iter=iter->next){
        if(iter->next->elem == cur_e){
            *prev_e = iter->elem;
            return SUCCESS;
        }
    }
    return FAILURE;
}

int NextElem(LkList* l,int cur_e,int* next_e){
    INITCHECK(*l);
    LkListIterator iter=l->next;
    for(;iter->next != NULL;iter=iter->next){
        if(iter->elem == cur_e) break;
    }
    if(iter->next != NULL && iter->next->next != NULL){
        *next_e = iter->next->elem;
        return SUCCESS;
    }
    return FAILURE;
}

int ListInsert(LkList* l,int pos,int elem){
    INITCHECK(*l);
    INSOVERFLOW(*l,pos);
    LkListIterator iter = l;
    for(int iterpos = HUST_DS_STARTPOS;iterpos<pos;iterpos++){
        iter=iter->next;
    }
    LkListIterator next = iter->next;
    LkListIterator newone = NULL;
    DEFALLOC(newone,sizeof(LkList));
    newone ->next = next;
    newone ->elem = elem;
    iter->next = newone;
    l->elem++;
    return SUCCESS;
}

int ListDelete(LkList* l,int pos,int* elem){
    INITCHECK(*l);
    OVERFLOW(*l,pos);
    LkListIterator iter = l;
    for(int iterpos = HUST_DS_STARTPOS;iterpos<pos;iterpos++){
        iter=iter->next;
    }
    LkListIterator next = iter->next->next;
    *elem = iter->next->elem;
    free(iter->next);
    iter->next = next;
    l->elem--;
    return SUCCESS;
}

int ListTraverse(LkList* l,Visitor v){
    INITCHECK(*l);
    for(LkListIterator iter=l->next;iter->next!=NULL;iter=iter->next){
        v(iter->elem);
    }
    return SUCCESS;
}

int Save(LkList* l,const char* filepath){
    INITCHECK(*l);
    FILE* fd = fopen(filepath,"w");
    if(fd == NULL){
        return FAILURE;
    }
    fwrite(&(l->elem),sizeof(int),1,fd);
    for(LkListIterator iter=l->next;iter->next != NULL;iter=iter->next){
        fwrite(&(iter->elem),sizeof(int),1,fd);
    }
    fclose(fd);
    return SUCCESS;
}

int Load(LkList* l,const char* filepath){
    if(l->next == NULL){
        InitaList(l);
    }else{
        ClearList(l);
    }
    FILE* fd = fopen(filepath,"r");
    if(fd == NULL){
        return FAILURE;
    }
    int cnts = 0;
    fread(&cnts,sizeof(int),1,fd);
    for(int i=0;i<cnts;i++){
        int tmp = 0;
        fread(&tmp,sizeof(int),1,fd);
        ListInsert(l,i+HUST_DS_STARTPOS,tmp);
    }
    fclose(fd);
    return SUCCESS;
}