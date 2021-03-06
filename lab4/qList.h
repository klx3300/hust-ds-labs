#ifndef Q_LIST_H
#define Q_LIST_H
#define Q__LD_MAGIC "__listdesc"
struct q__List{
    void* data;
    unsigned int size;
    struct q__List *prev;
    struct q__List *next;
};
struct q__ListDescriptor{
    char ldmagic[10];
    struct q__List* head;
    struct q__List* tail;
    unsigned int size;
};

typedef struct q__List *qListIterator;
typedef struct q__ListDescriptor qListDescriptor;

#define qList_initdesc(desc) q__List_initdesc(&(desc))
void q__List_initdesc(void* descriptor);

qListDescriptor qList_constructor();

#define qList_push_back(desc,target) q__List_push_back(&(desc),&(target),sizeof(target))
int q__List_push_back(void* descriptor,void* target,unsigned int target_size);
#define qList_push_front(desc,target) q__List_push_front(&(desc),&(target),sizeof(target))
int q__List_push_front(void* descriptor,void* target,unsigned int target_size);
#define qList_pop_back(desc) q__List_pop_back(&(desc))
int q__List_pop_back(void* descriptor);
#define qList_pop_front(desc) q__List_pop_front(&(desc))
int q__List_pop_front(void* descriptor);
#define qList_erase_elem(desc,iter) q__List_erase_elem(&(desc),iter)
int q__List_erase_elem(void* descriptor,qListIterator iter);
#define qList_swap_elem(desc,itera,iterb) q__List_swap_elem(&(desc),itera,iterb)
int q__List_swap_elem(void* descriptor,qListIterator itera,qListIterator iterb);
// notice: unlike cpp behaivor, the destructor here plays the role of
// clear the whole list and set the necessary parameters to its starting status.
#define qList_destructor(desc) q__List_destructor(&(desc))
int q__List_destructor(void* descriptor);

#define qList_foreach(desc,itername) for(qListIterator itername=(desc).head;itername != NULL;itername = itername->next)

#define qList_islist(desc) q__List_islist(&(desc),sizeof(desc))
int q__List_islist(void* descriptor,unsigned int size);

#define qList_copy(desc) q__List_copy(&(desc))
qListDescriptor q__List_copy(struct q__ListDescriptor *desc);
#endif