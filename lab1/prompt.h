#ifndef ZHWK_LAB_PROMPT_H
#define ZHWK_LAB_PROMPT_H

#include <vector>
#include <string>
#include "parse_str/strparse.h"

class Prompt{
public: 
    std::vector<std::string> avail_funcs;
    void (*dispatch)(std::vector<FuncParams> parameters);
    void start();
};

#endif