#include "RPN.hpp"
#include <cctype> 


int main(int argc, char *argv[]){
    if(argc < 1)
        return 1;
    RPN rpnVariable;
    rpnVariable.startCalculating(argv[1]);
    return 0;
}