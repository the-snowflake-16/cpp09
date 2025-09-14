#pragma once

#include <stack>
#include <bits/stdc++.h>

class RPN
{
private:
    std::stack<int> m_calculation;

public:

    RPN();
    RPN(const RPN &);
    RPN &operator=(const RPN &);
    ~RPN();

    void startCalculating(std::string str);

    std::stack<int> printVariables()const{
        return m_calculation;
    };

};


