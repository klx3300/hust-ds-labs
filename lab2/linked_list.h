#ifndef HUST_DS_LINKED_LIST_H
#define HUST_DS_LINKED_LIST_H

#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define SUCCESS 1
#define FAILURE 0

typedef struct LkList_st{
    int elem;       // elem of current node
    struct LkList_st * next;  // pointer of next node
}LkList;

/*
 * @Name InitaList
 * @Args *l is the linked list being operated
 * @Return Success or Failure
 */
extern int InitaList(LkList * l);

/*
 * @Name DestroyList
 * @Args *l is the linked list being operated
 * @Return Success or Failure
 */
extern int DestroyList(LkList * l);

/*
 * @Name ClearList
 * @Args *l is the linked list being operated
 * @Return Success or Failure
 */
extern int ClearList(LkList * l);

/*
 * @Name ListEmpty
 * @Args *l is the linked list being operated
 * @Return True or False
 */
extern int ListEmpty(LkList * l);

/*
 * @Name ListLength
 * @Args *l is the linked list being operated
 * @Return an integer which is the length of List
 */
extern int ListLength(LkList * l);

/*
 * @Name GetElem
 * @Args *l is the linked list being operated
 *        i is the position of elem
 *       *e is the elem
 * @Return Success or Failure
 */
extern int GetElem(LkList * l, int i, int * e);

/*
 * @Name LocateElem
 * @Args *l is the linked list being operated
 *        e is the value provided
 *       compare(a, b) is the function which is provided below
 * @Return an integer which is the position of elem who is able to pass the compare function
 *      and 0 is expected when no one can pass
 */
extern int LocateElem(LkList * l, int e, int (* compare) (int a, int b));

/*
 * @Name PriorElem
 * @Args *l is the linked list being operated
 *        cur_e is the possible elem
 *       *pre_e is the pre-elem
 * @Return Success or Failure
 */
extern int PriorElem(LkList * l, int cur_e, int * pre_e);

/*
 * @Name NextElem
 * @Args *l is the linked list being operated
 *        cur_e is the possible elem
 *       *next_e is the next-elem
 * @Return Success or Failure
 */
extern int NextElem(LkList * l, int cur_e, int * next_e);

/*
 * @Name ListInsert
 * @Args *l is the linked list being operated
 *        i is the aim position
 *        e is the elem
 * @Return Success or Failure
 */
extern int ListInsert(LkList * l, int i, int e);

/*
 * @Name ListDelete
 * @Args *l is the linked list being operated
 *        i is the aim position
 *       *e is the elem
 * @Return Success or Failure
 */
extern int ListDelete(LkList * l, int i, int * e);

/*
 * @Name ListTraverse
 * @Args *l is the linked list being operated
 *       visit(e) is the function which is provided below
 * @Return Success or Failure
 */
extern int ListTraverse(LkList * l, void (* visit) (int e));

/*
 * @Name compare
 * @Args a is the first var
 *       b is the second var
 * @Return True or False
 * @Usage this function is expected to be called in LocateElem
 */
int compare(int a, int b);

/*
 * @Name visit
 * @Args e
 * @Return void
 * @Usage this function is expected to be called in ListTraverse
 */
void visit(int e);

int Save(LkList* l,const char* filepath);

int Load(LkList* l,const char* filepath);

#endif