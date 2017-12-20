#include <iostream>
#include <array>
#include "prompt.h"
#include <cstdio>
extern "C" {
    #include "binary_tree.h"
    #include "log.h"
}

using namespace std;

#define PTR(x) (&(x))

void visit(int e) {
    printf("%d ", e);
}
int compare(int a, int b) {
    return a == b ? TRUE : FALSE;
}

#define LIST_MAX_NUMBER 100
array<TreeNode,LIST_MAX_NUMBER> lists;

// convert string to int
int str_int(string str){
    int tmpint = 0;
    sscanf(str.c_str(),"%d",&tmpint);
    return tmpint;
}

vector<int> str_intarr(string str){
    vector<int> v;
    int nextpos;
    do{
        nextpos = str.find_first_of(",");
        string tmpstr = str.substr(0,nextpos);
        if(nextpos != string::npos)
            str = str.substr(nextpos+1,string::npos);
        v.push_back(str_int(tmpstr));
    }while(nextpos != string::npos);
    return v;
}
// check parameter number
#define PACHECK(pararr,parnums) do{if((pararr).size()!=(parnums+1)){\
qLogFailfmt("Call parameter number mismatch: given %lu expected %d",(pararr).size(),(parnums)+1);\
return ;}}while(0)
// short version:read from environment
#define PAC(parnums) PACHECK(params,parnums)
// check the return value of spec function is SUCCESS or FAILED
#define ERRCHECK(x,dispname) do{if((x)==SUCCESS){\
    qLogSuccfmt("Call %s() succeed.",dispname);\
}else{\
    qLogFailfmt("Call %s() failed.",dispname); return ;\
}}while(0)
// check the return value of spec function is TRUE or FALSE
#define BOOLCHECK(x,dispname) do{if((x)==TRUE){\
    qLogSuccfmt("Call %s() returned true.",dispname);\
}else{\
    qLogFailfmt("Call %s() returned false.",dispname); return ;\
}}while(0)
// print out the returned int value
#define INTRETURN(x,dispname) do{qLogSuccfmt("Call %s() returned value %d",dispname,x);}while(0)
#define PTRRETURN(x,dispname) do{TreeNode* ptr = (x);\
if(ptr != NULL) qLogSuccfmt("Call %s() returned Index[%d],Value[%d]",dispname,ptr->index,ptr->value);\
else qLogFailfmt("Call %s() failed",dispname);}while(0)
// print out the returned int value(via pointer)
#define INTOUTV (&intout__retv)
#define INTOUT(x,dispname) do{int intout__retv = 0;\
ERRCHECK(x,dispname);\
qLogSuccfmt("Call %s() returned value %d",dispname,intout__retv);}while(0)
// dispatch strings
#define ISFUNC(x) (params[0].str==(x))
// check if exceed max list numbers
#define EXCEED(input,maximum) do{if(input >= maximum){qLogFailfmt("Attempt to exceed %s",#maximum); return;}}while(0)
#define LNEX(x) EXCEED(x,LIST_MAX_NUMBER)
// dispatch to corresponding list functions
void dispatcher(vector<FuncParams> params){
    if(ISFUNC("Init")){
        PAC(1);
        int number = str_int(params[1].str);
        LNEX(number);
        ERRCHECK(InitBiTree(PTR(lists[number])),"InitBiTree");
    }else if(ISFUNC("Destroy")){
        PAC(1);
        int number = str_int(params[1].str);
        LNEX(number);
        ERRCHECK(DestroyBiTree(PTR(lists[number])),"DestroyBiTree");
    }else if(ISFUNC("Clear")){
        PAC(1);
        int number = str_int(params[1].str);
        LNEX(number);
        ERRCHECK(ClearBiTree(PTR(lists[number])),"ClearBiTree");
    }else if(ISFUNC("Create")){
        PAC(3);
        vector<int> preorder = str_intarr(params[2].str);
        vector<int> inorder = str_intarr(params[3].str);
        int number = str_int(params[1].str);
        LNEX(number);
        ERRCHECK(CreateBiTree(PTR(lists[number]),preorder.data(),inorder.data(),preorder.size()),"CreateBiTree");
    }else if(ISFUNC("Empty")){
        PAC(1);
        int number = str_int(params[1].str);
        LNEX(number);
        BOOLCHECK(BiTreeEmpty(PTR(lists[number])),"BiTreeEmpty");
    }else if(ISFUNC("Depth")){
        PAC(1);
        int number = str_int(params[1].str);
        LNEX(number);
        INTRETURN(BiTreeDepth(PTR(lists[number])),"BiTreeDepth");
    }else if(ISFUNC("Root")){
        PAC(1);
        int number = str_int(params[1].str);
        LNEX(number);
        PTRRETURN(Root(PTR(lists[number])),"Root");
    }else if(ISFUNC("Value")){
        PAC(2);
        int number = str_int(params[1].str);
        int position = str_int(params[2].str);
        LNEX(number);
        INTRETURN(Value(PTR(lists[number]),position),"Value");
    }else if(ISFUNC("Assign")){
        PAC(3);
        int no = str_int(params[1].str);
        int el = str_int(params[2].str);
        int as = str_int(params[3].str);
        LNEX(no);
        INTRETURN(Assign(PTR(lists[no]),el,as),"Assign");
    }else if(ISFUNC("Parent")){
        PAC(2);
        int no = str_int(params[1].str);
        int cur = str_int(params[2].str);
        LNEX(no);
        PTRRETURN(Parent(PTR(lists[no]),cur),"Parent");
    }else if(ISFUNC("LeftChild")){
        PAC(2);
        int no = str_int(params[1].str);
        int cur = str_int(params[2].str);
        LNEX(no);
        PTRRETURN(LeftChild(PTR(lists[no]),cur),"LeftChild");
    }else if(ISFUNC("RightChild")){
        PAC(2);
        int no = str_int(params[1].str);
        int pos = str_int(params[2].str);
        LNEX(no);
        PTRRETURN(RightChild(PTR(lists[no]),pos),"RightChild");
    }else if(ISFUNC("LeftSibling")){
        PAC(2);
        int no = str_int(params[1].str);
        int cur = str_int(params[2].str);
        LNEX(no);
        PTRRETURN(LeftSibling(PTR(lists[no]),cur),"LeftSibling");
    }else if(ISFUNC("RightSibling")){
        PAC(2);
        int no = str_int(params[1].str);
        int pos = str_int(params[2].str);
        LNEX(no);
        PTRRETURN(RightSibling(PTR(lists[no]),pos),"RightSibling");
    }else if(ISFUNC("Insert")){
        PAC(4);
        int no = str_int(params[1].str);
        int pos = str_int(params[2].str);
        int LorR = str_int(params[3].str);
        int as = str_int(params[4].str);
        LNEX(no);
        LNEX(as);
        if(LorR > 1 || LorR < 0){qLogFail("Invalid parameter LorR!");return;}
        ERRCHECK(InsertChild(PTR(lists[no]),pos,LorR,PTR(lists[as])),"InsertChild");
    }else if(ISFUNC("Delete")){
        PAC(3);
        int no = str_int(params[1].str);
        int pos = str_int(params[2].str);
        int LorR = str_int(params[3].str);
        LNEX(no);
        if(LorR > 1 || LorR < 0){qLogFail("Invalid parameter LorR!");return;}
        ERRCHECK(DeleteChild(PTR(lists[no]),pos,LorR),"DeleteChild");
    }else if(ISFUNC("PreOrderTraverse")){
        PAC(1);
        int no = str_int(params[1].str);
        LNEX(no);
        ERRCHECK(PreOrderTraverse(PTR(lists[no]),visit),"PreOrderTraverse");
    }else if(ISFUNC("InOrderTraverse")){
        PAC(1);
        int no = str_int(params[1].str);
        LNEX(no);
        ERRCHECK(InOrderTraverse(PTR(lists[no]),visit),"InOrderTraverse");
    }else if(ISFUNC("PostOrderTraverse")){
        PAC(1);
        int no = str_int(params[1].str);
        LNEX(no);
        ERRCHECK(PostOrderTraverse(PTR(lists[no]),visit),"PostOrderTraverse");
    }else if(ISFUNC("LevelOrderTraverse")){
        PAC(1);
        int no = str_int(params[1].str);
        LNEX(no);
        ERRCHECK(LevelOrderTraverse(PTR(lists[no]),visit),"LevelOrderTraverse");
    }else if(ISFUNC("Save")){
        PAC(2);
        int no = str_int(params[1].str);
        LNEX(no);
        ERRCHECK(Save(PTR(lists[no]),params[2].str.c_str()),"Save");
    }else if(ISFUNC("Load")){
        PAC(2);
        int no = str_int(params[1].str);
        LNEX(no);
        ERRCHECK(Load(PTR(lists[no]),params[2].str.c_str()),"Load");
    }else{
        qLogFailfmt("No matching function calls for %s",params[0].str.c_str());
    }
}

// add help lines
#define FN(x) pr.avail_funcs.push_back(x)

int main(void){
    Prompt pr;
    pr.prompt_name = "Binary Tree demonstration system";
    FN("Init(int treeid)");
    FN("Destroy(int treeid)");
    FN("Clear(int treeid)");
    FN("Create(int treeid,char* preorder_traverse,char* inorder_traverse)");
    FN("Empty(int treeid)");
    FN("Depth(int treeid)");
    FN("Root(int treeid)");
    FN("Value(int treeid,int index)");
    FN("Assign(int treeid,int index,int value");
    FN("Parent(int treeid,int index)");
    FN("LeftChild(int treeid,int index)");
    FN("RightChild(int treeid,int index)");
    FN("LeftSibling(int treeid,int index)");
    FN("RightSibling(int treeid,int index)");
    FN("Insert(int treeid,int index,int LorR,int another_tree_id)");
    FN("Delete(int treeid,int index,int LorR)");
    FN("PreOrderTraverse(int treeid)");
    FN("InOrderTraverse(int treeid)");
    FN("PostOrderTraverse(int treeid)");
    FN("LevelOrderTraverse(int treeid)");
    FN("Save(int treeid,const char* file_path_to_save)");
    FN("Load(int treeid,const char* file_path_to_load)");
    FN("Note 1: Traverse visit() function is predefined in header files.");
    FN("Note 2: Only supports maximum of 100 lists.(listid 0~99)");
    FN("Note 3: Create() last two parameters must be in \"1,2,3\"-like form.");
    pr.dispatch = dispatcher;
    // start interactive interpreter
    pr.start();
}