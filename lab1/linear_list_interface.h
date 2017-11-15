#ifndef HUSTDS_LINEAR_LIST_INTERFACE
#define HUSTDS_LINEAR_LIST_INTERFACE

#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define SUCCESS 1
#define FAILURE 0

typedef struct{
    int * elem;    // pointer of the start position of elems list
    int length;    // current length of list
    int listsize;  // size of memory which has been malloc for list
}SqList;

/*
 * @Name InitaList
 * @Args *l is the linear list being operated
 * @Return Success or Failure
 */
int InitaList(SqList * l);

/*
 * @Name DestroyList
 * @Args *l is the linear list being operated
 * @Return Success or Failure
 */
int DestroyList(SqList * l);

/*
 * @Name ClearList
 * @Args *l is the linear list being operated
 * @Return Success or Failure
 */
int ClearList(SqList * l);

/*
 * @Name ListEmpty
 * @Args *l is the linear list being operated
 * @Return True or False
 */
int ListEmpty(SqList * l);

/*
 * @Name ListLength
 * @Args *l is the linear list being operated
 * @Return an integer which is the length of List
 */
int ListLength(SqList * l);

/*
 * @Name GetElem
 * @Args *l is the linear list being operated
 *        i is the position of elem
 *       *e is the elem
 * @Return Success or Failure
 */
int GetElem(SqList * l, int i, int * e);

/*
 * @Name LocateElem
 * @Args *l is the linear list being operated
 *        e is the value provided
 *       compare(a, b) is the function which is provided below
 * @Return an integer which is the position of elem who is able to pass the compare function
 *      and 0 is expected when no one can pass
 */
int LocateElem(SqList * l, int e, int (* compare) (int a, int b));

/*
 * @Name PriorElem
 * @Args *l is the linear list being operated
 *        cur_e is the possible elem
 *       *pre_e is the pre-elem
 * @Return Success or Failure
 */
int PriorElem(SqList * l, int cur_e, int * pre_e);

/*
 * @Name NextElem
 * @Args *l is the linear list being operated
 *        cur_e is the possible elem
 *       *next_e is the next-elem
 * @Return Success or Failure
 */
int NextElem(SqList * l, int cur_e, int * next_e);

/*
 * @Name ListInsert
 * @Args *l is the linear list being operated
 *        i is the aim position
 *        e is the elem
 * @Return Success or Failure
 */
int ListInsert(SqList * l, int i, int e);

/*
 * @Name ListDelete
 * @Args *l is the linear list being operated
 *        i is the aim position
 *       *e is the elem
 * @Return Success or Failure
 */
int ListDelete(SqList * l, int i, int * e);

/*
 * @Name ListTraverse
 * @Args *l is the linear list being operated
 *       visit(e) is the function which is provided below
 * @Return Success or Failure
 */
int ListTraverse(SqList * l, int (* visit) (int e));

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
#endif