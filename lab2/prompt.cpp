#include "prompt.h"
#include <iostream>

using namespace std;

void Prompt::start(){
    string linebuffer;
    int lineno = 0;
    cout<<"[INFO] Welcome to imzhwk interactive shell!" << endl;
    cout<<"[INFO] Try help() to list available functions." << endl;
    while(1){
        cout << "zhwk_prompt > ";
        if(!getline(cin,linebuffer)){
            cout << endl << "[EXIT] Parser reached end-of-file. Terminated." << endl;
            return;
        }
        lineno++;
        auto paramvec = parsefunc(linebuffer,lineno);
        if(paramvec.size() == 0) continue;
        if(paramvec[0].str == "help"){
            // ask for help
            cout << "[HINT] Available functions are:" << endl;
            for(auto x:this->avail_funcs){
                cout << "[HINT] " << x << endl;
            }
            continue;
        }
        // not help. then dispatch
        this->dispatch(paramvec);
    }
}