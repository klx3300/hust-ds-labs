#include <iostream>
#include <array>
#include "prompt.h"
#include <cstdio>
extern "C" {
    #include "graph.h"
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
array<GraphDescriptor,LIST_MAX_NUMBER> lists;

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
qLogFailfmt("Call parameter number mismatch: given %lu expected %d",(pararr).size()-1,(parnums));\
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
#define VEXRETURN(x,dispname) do{GraphVertex* ptr = (x);\
if(ptr != NULL) qLogSuccfmt("Call %s() returned Value[%d]",dispname,ptr->value);\
else qLogFailfmt("Call %s() failed",dispname);}while(0)
#define EDGRETURN(x,dispname) do{GraphEdge* ptr = (x);\
if(ptr != NULL) qLogSuccfmt("Call %s() returned Destination[%d],Priority[%d]",dispname,ptr->destination,ptr->priority);\
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
        PAC(2);
        int number = str_int(params[1].str);
        int isdir = str_int(params[2].str);
        LNEX(number);
        ERRCHECK(InitGraph(PTR(lists[number]),isdir),"InitGraph");
    }else if(ISFUNC("Destroy")){
        PAC(1);
        int number = str_int(params[1].str);
        LNEX(number);
        ERRCHECK(DestroyGraph(PTR(lists[number])),"DestroyGraph");
    }else if(ISFUNC("Create")){
        PAC(4);
        vector<int> verts = str_intarr(params[3].str);
        vector<int> edges = str_intarr(params[4].str);
        int number = str_int(params[1].str);
        int isdir = str_int(params[2].str);
        LNEX(number);
        ERRCHECK(CreateGraph(PTR(lists[number]),isdir,verts.data(),verts.size(),edges.data(),edges.size()),"CreateGraph");
    }else if(ISFUNC("LocateVex")){
        PAC(2);
        int number = str_int(params[1].str);
        int position = str_int(params[2].str);
        LNEX(number);
        VEXRETURN(LocateVex(PTR(lists[number]),position),"LocateVex");
    }else if(ISFUNC("GetIndex")){
        PAC(2);
        int number = str_int(params[1].str);
        int position = str_int(params[2].str);
        LNEX(number);
        INTOUT(GetIndex(PTR(lists[number]),position,INTOUTV),"GetIndex");
    }else if(ISFUNC("GetValue")){
        PAC(2);
        int number = str_int(params[1].str);
        int position = str_int(params[2].str);
        LNEX(number);
        INTOUT(GetValue(PTR(lists[number]),position,INTOUTV),"GetValue");
    }else if(ISFUNC("PutValue")){
        PAC(3);
        int no = str_int(params[1].str);
        int el = str_int(params[2].str);
        int as = str_int(params[3].str);
        LNEX(no);
        ERRCHECK(PutValue(PTR(lists[no]),el,as),"PutValue");
    }else if(ISFUNC("FirstAdjVex")){
        PAC(2);
        int no = str_int(params[1].str);
        int cur = str_int(params[2].str);
        LNEX(no);
        EDGRETURN(FirstAdjVex(PTR(lists[no]),cur),"FirstAdjVex");
    }else if(ISFUNC("NextAdjVex")){
        PAC(3);
        int no = str_int(params[1].str);
        int cur = str_int(params[2].str);
        int prev = str_int(params[3].str);
        LNEX(no);
        EDGRETURN(NextAdjVex(PTR(lists[no]),cur,prev),"NextAdjVex");
    }else if(ISFUNC("InsertVex")){
        PAC(2);
        int no = str_int(params[1].str);
        int val = str_int(params[2].str);
        LNEX(no);
        ERRCHECK(InsertVex(PTR(lists[no]),val),"InsertVex");
    }else if(ISFUNC("DeleteVex")){
        PAC(2);
        int no = str_int(params[1].str);
        int ind = str_int(params[2].str);
        LNEX(no);
        ERRCHECK(DeleteVex(PTR(lists[no]),ind),"DeleteVex");
    }else if(ISFUNC("InsertArc")){
        PAC(4);
        int no = str_int(params[1].str);
        int srid = str_int(params[2].str);
        int dtid = str_int(params[3].str);
        int pr = str_int(params[4].str);
        LNEX(no);
        ERRCHECK(InsertArc(PTR(lists[no]),srid,dtid,pr,1),"InsertArc");
    }else if(ISFUNC("DeleteArc")){
        PAC(3);
        int no = str_int(params[1].str);
        int srid = str_int(params[2].str);
        int dtid = str_int(params[3].str);
        LNEX(no);
        ERRCHECK(DeleteArc(PTR(lists[no]),srid,dtid,1),"DeleteArc");
    }else if(ISFUNC("DFSTraverse")){
        PAC(1);
        int no = str_int(params[1].str);
        LNEX(no);
        ERRCHECK(DFSTraverse(PTR(lists[no]),NULL),"DFSTraverse");
    }else if(ISFUNC("BFSTraverse")){
        PAC(1);
        int no = str_int(params[1].str);
        LNEX(no);
        ERRCHECK(BFSTraverse(PTR(lists[no]),NULL),"BFSTraverse");
    }else{
        qLogFailfmt("No matching function calls for %s",params[0].str.c_str());
    }
}

// add help lines
#define FN(x) pr.avail_funcs.push_back(x)

int main(void){
    Prompt pr;
    pr.prompt_name = "Graph demonstration system";
    FN("Init(int graphid,int isDirected)");
    FN("Destroy(int graphid)");
    FN("Create(int graphid,int isDirected,char* vertices,char* edges)");
    FN("LocateVex(int graphid,int index)");
    FN("GetIndex(int graphid,int value)");
    FN("GetValue(int graphid,int index)");
    FN("PutValue(int graphid,int index,int value)");
    FN("FirstAdjVex(int graphid,int index)");
    FN("NextAdjVex(int graphid,int index,int prevdest)");
    FN("InsertArc(int graphid,int srcindex,int dstindex,int priority)");
    FN("DeleteArc(int graphid,int srcindex,int dstindex)");
    FN("DFSTraverse(int graphid)");
    FN("BFSTraverse(int graphid)");
    FN("Note 1: Traverse visit() function is predefined in header files.");
    FN("Note 2: Only supports maximum of 100 graphs.(graphid 0~99)");
    FN("Note 3: Create() last two parameters must be in \"1,2,3\"-like form.");
    pr.dispatch = dispatcher;
    // start interactive interpreter
    pr.start();
}