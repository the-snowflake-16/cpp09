#include "RPN.hpp"
#include <cctype> 


int main(){
    std::string str = "9 8 /" ;
    std::string s;
    RPN rpnVariable;
    rpnVariable.startCalculating(str);
}