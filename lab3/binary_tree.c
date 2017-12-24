#include "binary_tree.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "log.h"
#include "qList.h"

// ------- divider --------

#define ORDER_PRE 0
#define ORDER_IN 1
#define ORDER_POST 2

#define POSITION_L 0
#define POSITION_R 1

typedef void (*Reacher)(TreeNode*,void*);
typedef void (*Visitor)(TreeNode*,void*);

#define INITCHK(node) ((node)->index == -1 && (node)->rightChild == NULL)
#define DEFALLOC(type,var) type* var=malloc(sizeof(type));memset(var,0,sizeof(type));
#define EXISTCHK(node) (INITCHK(node) && (node)->leftChild != NULL)

int searcharr(int *arr,int size,int target){
    for(int i=0;i<size;i++)
        if(arr[i]==target) return i;
    return -1;
}

int InitBiTree(TreeNode* head){
    if(INITCHK(head)){
        return FAILURE;// re-init
    }
    head->index = -1;
    head->value = 0;
    head->rightChild = NULL;
    head->leftChild = NULL;
    return SUCCESS;
}

void DestroyBiTreeRecursively(TreeNode* root){
    if(root == NULL) return;
    DestroyBiTreeRecursively(root->leftChild);
    DestroyBiTreeRecursively(root->rightChild);
    free(root);
    return;
}

int DestroyBiTree(TreeNode* head){
    // you need to re-init it.
    // so invalidate the head.
    if(!INITCHK(head)){
        return FAILURE;
    }
    head->index = 0;
    DestroyBiTreeRecursively(head->leftChild);
    return SUCCESS;
}

TreeNode* CreateBiTreeRecursively(int* defa,int* defb,int lesser,int most,int *curr){
    if(curr == NULL){
        int ncurr = 0;
        return CreateBiTreeRecursively(defa,defb,lesser,most,&ncurr);
    }
    int whereis = searcharr(defb+lesser,most-lesser,defa[*curr]);
    if(whereis != -1) whereis = whereis + lesser;
    if(whereis == -1){
        // should not be allocated here
        return NULL;
    }
    DEFALLOC(TreeNode,root);
    root->index = root->value = defa[*curr];
    (*curr)++;
    root->leftChild = CreateBiTreeRecursively(defa,defb,lesser,whereis,curr);
    root->rightChild = CreateBiTreeRecursively(defa,defb,whereis+1,most,curr);
    return root;
}

int CreateBiTree(TreeNode * head, int * definition1, int * definition2, int lengthOfDef){
    if(!INITCHK(head) || EXISTCHK(head)){
        return FAILURE;
    }
    head->leftChild = CreateBiTreeRecursively(definition1,definition2,0,lengthOfDef,NULL);
    return SUCCESS;
}

int ClearBiTree(TreeNode* head){
    // destroy without invalidate the head
    if(!INITCHK(head)){
        return FAILURE;
    }
    head->value = 0;
    DestroyBiTreeRecursively(head->leftChild);
    return SUCCESS;
}

int BiTreeEmpty(TreeNode* head){
    if(!INITCHK(head)) return 1;
    return !(head->value);
}

int BiTreeDepthRecursively(TreeNode* head,int depthmeter){
    if(head == NULL) return depthmeter;
    int a=BiTreeDepthRecursively(head->leftChild,depthmeter+1),b=BiTreeDepthRecursively(head->rightChild,depthmeter+1);
    return a>b?a:b;
}

int BiTreeDepth(TreeNode* head){
    if(!INITCHK(head)) return 0;
    return BiTreeDepthRecursively(head->leftChild,0);
}

TreeNode* Root(TreeNode* head){
    if(!INITCHK(head)) return NULL;
    return head->leftChild;
}

int BiTreeSearch(TreeNode* head,int index,Reacher reacher,void* extrargs){
    if(head == NULL) return 0;
    if(head->index == index){
        reacher(head,extrargs);
        return 1;
    }
    return BiTreeSearch(head->leftChild,index,reacher,extrargs)||BiTreeSearch(head->rightChild,index,reacher,extrargs);
}

void GetValueOnReach(TreeNode* head,void* extrargs){
    int* x = extrargs;
    *x = head->value;
}

int Value(TreeNode* head,int index){
    if(!EXISTCHK(head)){
        srand(time(NULL));
        return rand();
    }
    srand(time(NULL));
    int val=rand();
    BiTreeSearch(head->leftChild,index,GetValueOnReach,&val);
    return val;
}

void AssignValueOnReach(TreeNode* node,void* extrargs){
    int x = (int)extrargs;
    node->value = x;
}

int Assign(TreeNode* head,int index,int value){
    if(!EXISTCHK(head)) return FAILURE;
    return BiTreeSearch(head->leftChild,index,AssignValueOnReach,(void*)(unsigned long)value);
}

TreeNode* ParentRecursively(TreeNode* head,int index){
    if(head==NULL) return NULL;
    if((head->leftChild!=NULL&&head->leftChild->index==index)||(head->rightChild!=NULL&&head->rightChild->index==index)){
        return head;
    }
    TreeNode* a = ParentRecursively(head->leftChild,index);
    if(a == NULL) return ParentRecursively(head->rightChild,index);
    else return a;
}

TreeNode* Parent(TreeNode* head,int index){
    if(!EXISTCHK(head)){return NULL;}
    return ParentRecursively(head->leftChild,index);
}

void GetLChildOnReach(TreeNode* node,void* extrargs){
    TreeNode** tn = extrargs;
    (*tn)=node->leftChild;
}

void GetRChildOnReach(TreeNode* node,void* extrargs){
    TreeNode** tn = extrargs;
    (*tn)=node->rightChild;
}

TreeNode* LeftChild(TreeNode* head,int index){
    TreeNode* thenode=NULL;
    if(!EXISTCHK(head)) return NULL;
    BiTreeSearch(head->leftChild,index,GetLChildOnReach,&thenode);
    return thenode;
}

TreeNode* RightChild(TreeNode* head,int index){
    TreeNode* thenode=NULL;
    if(!EXISTCHK(head)) return NULL;
    BiTreeSearch(head->leftChild,index,GetRChildOnReach,&thenode);
    return thenode;
}

TreeNode* LeftSibling(TreeNode* head,int index){
    TreeNode* par = Parent(head,index);
    if(par == NULL) return NULL;
    return par->leftChild == NULL?NULL:par->leftChild->index == index?NULL:par->leftChild;
}

TreeNode* RightSibling(TreeNode* head,int index){
    TreeNode* par = Parent(head,index);
    if(par == NULL) return NULL;
    return par->rightChild == NULL?NULL:par->rightChild->index == index?NULL:par->rightChild;
}

void GetNodeOnReach(TreeNode* node,void* extrargs){
    TreeNode** thenode = extrargs;
    (*thenode)=node;
}

void BiTreeTraverse(TreeNode* node,int order,Visitor visitor,void* extrargs){
    if(node == NULL) return;
    if(order == ORDER_PRE){
        visitor(node,extrargs);
        BiTreeTraverse(node->leftChild,order,visitor,extrargs);
        BiTreeTraverse(node->rightChild,order,visitor,extrargs);
    }else if(order == ORDER_IN){
        BiTreeTraverse(node->leftChild,order,visitor,extrargs);
        visitor(node,extrargs);
        BiTreeTraverse(node->rightChild,order,visitor,extrargs);
    }else{
        BiTreeTraverse(node->leftChild,order,visitor,extrargs);
        BiTreeTraverse(node->rightChild,order,visitor,extrargs);
        visitor(node,extrargs);
    }
}

void AccumulateOnTraverse(TreeNode* node,void* vptr_accumulator){
    int* accumulator = vptr_accumulator;
    (*accumulator)++;
}

void UpdateWithAccumulatorOnTraverse(TreeNode* node,void* vptr_accumulator){
    int* accumulator = vptr_accumulator;
    node->index = *accumulator;
    (*accumulator)++;
}

void LargestIndexOnTraverse(TreeNode* node,void* vptr_lindex){
    int* lindex = vptr_lindex;
    if(node->index > *(lindex)) *lindex = node->index;
}

int InsertChild(TreeNode* head,int index,int position,TreeNode* node){
    if(!EXISTCHK(head)) return FAILURE;
    TreeNode* dstnode=NULL;
    BiTreeSearch(head->leftChild,index,GetNodeOnReach,&dstnode);
    if(dstnode == NULL) return FAILURE;
    TreeNode** opernode;
    if(position == POSITION_L){
        opernode = &(dstnode->leftChild);
    }else{
        opernode = &(dstnode->rightChild);
    }
    if(*opernode != NULL){
        // have to count how many nodes deleted,
        // update the size and free the space
        int counts = 0;
        BiTreeTraverse(*opernode,ORDER_IN,AccumulateOnTraverse,&counts);
        head->value -= counts;
        DestroyBiTreeRecursively(*opernode);
        *opernode = NULL;
    }
    // prepare to update indexes
    int lindex=0;
    BiTreeTraverse(head->leftChild,ORDER_IN,LargestIndexOnTraverse,&lindex);
    lindex++;
    head->value+=node->value;
    *opernode = node->leftChild;
    return SUCCESS;
}

int DeleteChild(TreeNode* head,int index,int position){
    if(!EXISTCHK(head)) return FAILURE;
    TreeNode* dstnode = NULL;
    BiTreeSearch(head->leftChild,index,GetNodeOnReach,&dstnode);
    if(dstnode == NULL) return FAILURE;
    TreeNode** opernode;
    if(position == POSITION_L){
        opernode = &(dstnode->leftChild);
    }else{
        opernode = &(dstnode->rightChild);
    }
    if(*opernode == NULL) return FAILURE;
    int counts = 0;
    BiTreeTraverse(*opernode,ORDER_IN,AccumulateOnTraverse,&counts);
    head->value-=counts;
    DestroyBiTreeRecursively(*opernode);
    *opernode = NULL;
    return SUCCESS;
}

void BroadFirstTraverse(TreeNode* node,Visitor visitor,void* args){
    qListDescriptor desc;
    qList_initdesc(desc);
    qList_push_back(desc,node);
    while(desc.size){
        qListDescriptor nextlayer;
        qList_initdesc(nextlayer);
        qList_foreach(desc,iter){
            TreeNode* currnode = *(TreeNode**)(iter->data);
            visitor(currnode,args);
            if(currnode->leftChild!=NULL) qList_push_back(nextlayer,currnode->leftChild);
            if(currnode->rightChild!=NULL) qList_push_back(nextlayer,currnode->rightChild);
        }
        qList_destructor(desc);
        desc=nextlayer;
    }
}

void XFSVisitor(TreeNode* node,void* visitfunc){
    void (*visit)(int) = visitfunc;
    visit(node->value);
}

int PreOrderTraverse(TreeNode * head, void (*visit)(int value)){
    if(!EXISTCHK(head)) return FAILURE;
    BiTreeTraverse(head->leftChild,ORDER_PRE,XFSVisitor,visit);
    printf("\n");
    return SUCCESS;
}

int InOrderTraverse(TreeNode * head, void (*visit)(int value)){
    if(!EXISTCHK(head)) return FAILURE;
    BiTreeTraverse(head->leftChild,ORDER_IN,XFSVisitor,visit);
    printf("\n");
    return SUCCESS;
}

int PostOrderTraverse(TreeNode * head, void (*visit)(int value)){
    if(!EXISTCHK(head)) return FAILURE;
    BiTreeTraverse(head->leftChild,ORDER_POST,XFSVisitor,visit);
    printf("\n");
    return SUCCESS;
}

int LevelOrderTraverse(TreeNode * head, void (*visit)(int value)){
    if(!EXISTCHK(head)) return FAILURE;
    BroadFirstTraverse(head->leftChild,XFSVisitor,visit);
    printf("\n");
    return SUCCESS;
}

void ListInsertOnTraverse(TreeNode* node,void* vptr_listdesc){
    qListDescriptor* desc = vptr_listdesc;
    qList_push_back(*desc,node->value);
}

int Save(TreeNode* head,const char* path){
    if(!EXISTCHK(head)) return FAILURE;
    qListDescriptor pre_desc,in_desc;
    qList_initdesc(pre_desc);
    qList_initdesc(in_desc);
    BiTreeTraverse(head->leftChild,ORDER_PRE,ListInsertOnTraverse,&pre_desc);
    BiTreeTraverse(head->leftChild,ORDER_IN,ListInsertOnTraverse,&in_desc);
    int *prearr=malloc(sizeof(int)*pre_desc.size);
    int *inarr=malloc(sizeof(int)*in_desc.size);
    memset(prearr,0,sizeof(int)*pre_desc.size);
    memset(inarr,0,sizeof(int)*in_desc.size);
    int curr = 0;
    qList_foreach(pre_desc,iter){
        prearr[curr] = *(int*)(iter->data);
        curr ++;
    }
    curr = 0;
    qList_foreach(in_desc,iter){
        inarr[curr] = *(int*)(iter->data);
        curr ++;
    }
    FILE* fd = fopen(path,"w");
    if(fd == NULL) return FAILURE;
    fwrite(&(pre_desc.size),sizeof(int),1,fd);
    fwrite(&(in_desc.size),sizeof(int),1,fd);
    fwrite(prearr,sizeof(int)*pre_desc.size,1,fd);
    fwrite(inarr,sizeof(int)*in_desc.size,1,fd);
    fclose(fd);
    free(prearr);free(inarr);
    qList_destructor(pre_desc);
    qList_destructor(in_desc);
    return SUCCESS;
}

int Load(TreeNode* head,const char* path){
    InitBiTree(head);
    FILE* fd = fopen(path,"r");
    int sizes[2];
    fread(sizes,sizeof(int)*2,1,fd);
    int* prearr = malloc(sizeof(int)*sizes[0]);
    int* inarr = malloc(sizeof(int)*sizes[1]);
    fread(prearr,sizeof(int)*sizes[0],1,fd);
    fread(inarr,sizeof(int)*sizes[1],1,fd);
    CreateBiTree(head,prearr,inarr,sizes[0]);
    free(prearr);
    free(inarr);
    fclose(fd);
    return SUCCESS;
}