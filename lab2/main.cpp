#include <iostream>
#include <array>
#include "prompt.h"
#include <cstdio>
extern "C" {
    #include "linear_list_interface.h"
}

using namespace std;

int visit(int e){
    printf("%d ", e);
    return 0;
}
int compare(int a, int b) {
    return a == b ? TRUE : FALSE;
}

#define PTR(x) (&(x))

#define LIST_MAX_NUMBER 100
array<SqList,LIST_MAX_NUMBER> lists;

// convert string to int
int str_int(string str){
    int tmpint = 0;
    sscanf(str.c_str(),"%d",&tmpint);
    return tmpint;
}
// check parameter number
#define PACHECK(pararr,parnums) do{if((pararr).size()!=(parnums+1)){\
cout << "[FAIL] Call parameter number mismatch: given " << (pararr).size() << " expected " << (parnums+1) << endl;\
return ;}}while(0)
// short version:read from environment
#define PAC(parnums) PACHECK(params,parnums)
// check the return value of spec function is SUCCESS or FAILED
#define ERRCHECK(x,dispname) do{if((x)==SUCCESS){\
    cout << "[SUCC] Call " << dispname << "() succeed." << endl;\
}else{\
    cout << "[FAIL] Call " << dispname << "() failed." << endl; return ;\
}}while(0)
// check the return value of spec function is TRUE or FALSE
#define BOOLCHECK(x,dispname) do{if((x)==TRUE){\
    cout << "[TRUE] Call " << dispname << "() returned true." << endl;\
}else{\
    cout << "[FALS] Call " << dispname << "() returned false." << endl; return ;\
}}while(0)
// print out the returned int value
#define INTRETURN(x,dispname) do{cout << "[OUTV] Call " << dispname << "() returned value " << (x) << endl;}while(0)
// print out the returned int value(via pointer)
#define INTOUTV (&intout__retv)
#define INTOUT(x,dispname) do{int intout__retv = 0;\
ERRCHECK(x,dispname);\
cout << "[OUTV] Call " << dispname << "() returned value " << intout__retv << endl;}while(0)
// dispatch strings
#define ISFUNC(x) (params[0].str==(x))
// check if exceed max list numbers
#define EXCEED(input,maximum) do{if(input >= maximum){cout << "[FAIL] Attempt to exceed " << #maximum << endl; return;}}while(0)
#define LNEX(x) EXCEED(x,LIST_MAX_NUMBER)
// dispatch to corresponding list functions
void dispatcher(vector<FuncParams> params){
    if(ISFUNC("Init")){
        PAC(1);
        int number = str_int(params[1].str);
        LNEX(number);
        ERRCHECK(InitaList(PTR(lists[number])),"InitList");
    }else if(ISFUNC("Destroy")){
        PAC(1);
        int number = str_int(params[1].str);
        LNEX(number);
        ERRCHECK(DestroyList(PTR(lists[number])),"DestroyList");
    }else if(ISFUNC("Clear")){
        PAC(1);
        int number = str_int(params[1].str);
        LNEX(number);
        ERRCHECK(ClearList(PTR(lists[number])),"ClearList");
    }else if(ISFUNC("Empty")){
        PAC(1);
        int number = str_int(params[1].str);
        LNEX(number);
        BOOLCHECK(ListEmpty(PTR(lists[number])),"ListEmpty");
    }else if(ISFUNC("Length")){
        PAC(1);
        int number = str_int(params[1].str);
        LNEX(number);
        INTRETURN(ListLength(PTR(lists[number])),"ListLength");
    }else if(ISFUNC("GetElem")){
        PAC(2);
        int number = str_int(params[1].str);
        int position = str_int(params[2].str);
        LNEX(number);
        INTOUT(GetElem(PTR(lists[number]),position,INTOUTV),"GetElem");
    }else if(ISFUNC("LocateElem")){
        PAC(2);
        int no = str_int(params[1].str);
        int el = str_int(params[2].str);
        LNEX(no);
        INTRETURN(LocateElem(PTR(lists[no]),el,compare),"LocateElem");
    }else if(ISFUNC("PriorElem")){
        PAC(2);
        int no = str_int(params[1].str);
        int cur = str_int(params[2].str);
        LNEX(no);
        INTOUT(PriorElem(PTR(lists[no]),cur,INTOUTV),"PriorElem");
    }else if(ISFUNC("NextElem")){
        PAC(2);
        int no = str_int(params[1].str);
        int cur = str_int(params[2].str);
        LNEX(no);
        INTOUT(NextElem(PTR(lists[no]),cur,INTOUTV),"NextElem");
    }else if(ISFUNC("Insert")){
        PAC(3);
        int no = str_int(params[1].str);
        int pos = str_int(params[2].str);
        int el =str_int(params[3].str);
        LNEX(no);
        ERRCHECK(ListInsert(PTR(lists[no]),pos,el),"ListInsert");
    }else if(ISFUNC("Delete")){
        PAC(2);
        int no = str_int(params[1].str);
        int pos = str_int(params[2].str);
        LNEX(no);
        INTOUT(ListDelete(PTR(lists[no]),pos,INTOUTV),"ListDelete");
    }else if(ISFUNC("Traverse")){
        PAC(1);
        int no = str_int(params[1].str);
        LNEX(no);
        ERRCHECK(ListTraverse(PTR(lists[no]),visit),"ListTraverse");
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
        cout << "[FAIL] No matching function calls for " << params[0].str << endl;
    }
}

// add help lines
#define FN(x) pr.avail_funcs.push_back(x)

int main(void){
    Prompt pr;
    FN("Init(int listid)");
    FN("Destroy(int listid)");
    FN("Clear(int listid)");
    FN("Empty(int listid)");
    FN("Length(int listid)");
    FN("GetElem(int listid,int position)");
    FN("LocateElem(int listid,int elemv)");
    FN("PriorElem(int listid,int current_elemv)");
    FN("NextElem(int listid,int current_elemv)");
    FN("Insert(int listid,int position,int elemv)");
    FN("Delete(int listid,int position)");
    FN("Traverse(int listid)");
    FN("Save(int listid,const char* file_path_to_save)");
    FN("Load(int listid,const char* file_path_to_load)");
    FN("Note 1: Traverse visit() function is predefined in header files.");
    FN("Note 2: Only supports maximum of 100 lists.(listid 0~99)");
    pr.dispatch = dispatcher;
    // start interactive interpreter
    pr.start();
}