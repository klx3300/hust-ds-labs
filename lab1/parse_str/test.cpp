#include <iostream>
#include "strparse.h"
#include <string>

using namespace std;

int main(void){
    string linebuffer;
    int lineno = 0;
    while(getline(cin,linebuffer)){
        lineno++;
        auto rvec = parsefunc(linebuffer,lineno);
        for(auto x:rvec){
            cout << x.str << (x.is_literal?" as string":" as normal") << endl;
        }
    }
    return 0;
}