#include "prompt.h"
#include <iostream>
extern "C"{
    #include "log.h"
}

using namespace std;

void Prompt::start(){
    string linebuffer;
    int lineno = 0;
    qLogInfofmt("Welcome to %s!",this->prompt_name.c_str());
    qLogInfo("Try help() to list available functions.");
    while(1){
        cout << "zhwk_prompt > ";
        if(!getline(cin,linebuffer)){
            cout << endl;
            qLogInfo("Parser reached end-of-file. Terminated.");
            return;
        }
        lineno++;
        auto paramvec = parsefunc(linebuffer,lineno);
        if(paramvec.size() == 0) continue;
        if(paramvec[0].str == "help"){
            // ask for help
            qLogInfo("Available functions are:");
            for(auto x:this->avail_funcs){
                qLogInfofmt("%s",x.c_str());
            }
            continue;
        }
        // not help. then dispatch
        this->dispatch(paramvec);
    }
}