#include "linear_list_interface.h"
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
/*
 * @Name InitaList
 * @Args *l is the linear list being operated
 * @Return Success or Failure
 */
 int InitaList(SqList * l){
    memset(l,0,sizeof(SqList));
    l->elem = (int*)malloc(sizeof(int)*10);
    l->listsize = 10;
    if(l->elem == NULL) return FAILURE;
    return SUCCESS;
 }
 
 /*
  * @Name DestroyList
  * @Args *l is the linear list being operated
  * @Return Success or Failure
  */
 int DestroyList(SqList * l){
     if(l->elem!=NULL){
         free(l->elem);
     }
     memset(l,0,sizeof(SqList));
     return SUCCESS;
 }
 
 /*
  * @Name ClearList
  * @Args *l is the linear list being operated
  * @Return Success or Failure
  */
 int ClearList(SqList * l){
     if(l->elem == NULL || l->listsize == 0) return FAILURE;
     memset(l->elem,0,l->listsize);
     l->length=0;
     return SUCCESS;
 }
 
 /*
  * @Name ListEmpty
  * @Args *l is the linear list being operated
  * @Return True or False
  */
 int ListEmpty(SqList * l){
     return l->length==0;
 }
 
 /*
  * @Name ListLength
  * @Args *l is the linear list being operated
  * @Return an integer which is the length of List
  */
 int ListLength(SqList * l){
     return l->length;
 }
 
 /*
  * @Name GetElem
  * @Args *l is the linear list being operated
  *        i is the position of elem
  *       *e is the elem
  * @Return Success or Failure
  */
 int GetElem(SqList * l, int i, int * e){
     i = i-1;
     if(i >= l->length || i<0 || l->elem == NULL || l->listsize == 0) return FAILURE;
     *e=(l->elem[i]);
     return SUCCESS;
 }
 
 /*
  * @Name LocateElem
  * @Args *l is the linear list being operated
  *        e is the value provided
  *       compare(a, b) is the function which is provided below
  * @Return an integer which is the position of elem who is able to pass the compare function
  *      and 0 is expected when no one can pass
  */
 int LocateElem(SqList * l, int e, int (* compare) (int a, int b)){
     for(int i=0;i<l->length;i++){
         if(compare(l->elem[i],e)) return i+1;
     }
     return 0;
 }
 
 /*
  * @Name PriorElem
  * @Args *l is the linear list being operated
  *        cur_e is the possible elem
  *       *pre_e is the pre-elem
  * @Return Success or Failure
  */
 int PriorElem(SqList * l, int cur_e, int * pre_e){
     for(int i=0;i<l->length;i++){
         if(l->elem[i]==cur_e){
             if(i==0) return FAILURE;
             *pre_e =  l->elem[i-1];
             return SUCCESS;
         }
     }
     return FAILURE;
 }
 
 /*
  * @Name NextElem
  * @Args *l is the linear list being operated
  *        cur_e is the possible elem
  *       *next_e is the next-elem
  * @Return Success or Failure
  */
 int NextElem(SqList * l, int cur_e, int * next_e){
     for(int i=0;i<l->length;i++){
         if(l->elem[i]==cur_e){
             if(i==l->length-1) return FAILURE;
             *next_e =  l->elem[i+1];
             return SUCCESS;
         }
     }
     return FAILURE;
 }
 
 /*
  * @Name ListInsert
  * @Args *l is the linear list being operated
  *        i is the aim position
  *        e is the elem
  * @Return Success or Failure
  */
 int ListInsert(SqList * l, int pos, int e){
     pos = pos-1;
     if(pos>l->length || pos < 0 || l->elem == NULL || l->listsize == 0) return FAILURE;
     if(l->listsize < l->length+1){
        int* tmprealloc = (int*)malloc(sizeof(int)*(l->listsize)*2);
        if(tmprealloc == NULL) return FAILURE;
        l->listsize*=2;
        memset(tmprealloc,0,sizeof(int)*(l->listsize));
        if(l->elem != NULL)
            memcpy(tmprealloc,l->elem,l->length*sizeof(int));
        l->elem = tmprealloc;
     }
     for(int i=l->length;i>pos;i--){
         l->elem[i]=l->elem[i-1];
     }
     l->elem[pos]=e;
     l->length++;
     return SUCCESS;
 }
 
 /*
  * @Name ListDelete
  * @Args *l is the linear list being operated
  *        i is the aim position
  *       *e is the elem
  * @Return Success or Failure
  */
 int ListDelete(SqList * l, int pos, int * e){
     pos = pos-1;
     if(pos>l->length-1 || pos < 0 || l->elem == NULL || l->listsize == 0) return FAILURE;
     *e = l->elem[pos];
     for(int i=pos;i<l->length-1;i++){
         l->elem[pos] = l->elem[pos+1];
     }
     l->length--;
     return SUCCESS;
 }
 
 /*
  * @Name ListTraverse
  * @Args *l is the linear list being operated
  *       visit(e) is the function which is provided below
  * @Return Success or Failure
  */
 int ListTraverse(SqList * l, int (* visit) (int e)){
     if(ListEmpty(l)) return FAILURE;
     for(int i=0;i<l->length;i++){
         visit(l->elem[i]);
     }
     return SUCCESS;
 }

 int Save(SqList* l,const char* path){
    if(ListEmpty(l) || l->listsize == 0) return FAILURE;
    int fd = open(path,O_WRONLY|O_CREAT|O_TRUNC);
    if(fd == -1){
        return FAILURE;
    }
    write(fd,l,sizeof(SqList));
    write(fd,l->elem,sizeof(int)*l->listsize);
    close(fd);
    return SUCCESS;
 }

 int Load(SqList* l,const char* path){
     int fd = open(path,O_RDONLY);
     if(fd == -1){
         return FAILURE;
     }
     read(fd,l,sizeof(SqList));
     l->elem = (int*)malloc(sizeof(int)*l->listsize);
     read(fd,l->elem,sizeof(int)*l->listsize);
     return SUCCESS;
 }
 