#include "RPN.hpp"

RPN::RPN(){}

RPN::~RPN(){}


bool validToken(std::string str) {
    if(str.length() == 1)
    {
        if(std::isdigit(str[0])) {
            int number = std::atoi(str.c_str());
            if (number > 9 || number < 0)
                return false;
            return true;
        } else if (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/') {
            return true;
        }
    }
    return false;
}

void processOfCalculatin(std::stack<int> &m_calculation, char sighn){
    if(m_calculation.size() >= 2){
        int firstValue = m_calculation.top();
        m_calculation.pop();
        int secondValue = m_calculation.top();
        m_calculation.pop();
        if (sighn == '+') {
            m_calculation.push(secondValue + firstValue);
        } else if (sighn == '-') {
            m_calculation.push(secondValue - firstValue);
        } else if (sighn == '*') {
            m_calculation.push(secondValue * firstValue);
        } else if (sighn == '/') {
            if (firstValue == 0) {
                std::cout << "Error: division by zero" << std::endl;
                exit(1);
                }  
                m_calculation.push(secondValue / firstValue);
        }
    } 
}

void parserAndCalculate(std::stack<int> &m_calculation, std::string str){
    if (!validToken(str)) {
        std::cout << "Incorect input " << str << std::endl;
        exit(0); 
    }
    if(std::isdigit(str[0])) {
        m_calculation.push(std::atoi(str.c_str()));
    } else if (((str[0] == '+') || (str[0] == '-') || (str[0] == '*') || (str[0] == '/')) && m_calculation.size() >= 2){
        processOfCalculatin(m_calculation , str[0]);
    } else {
        std::cout << "Incorect input" << std::endl;
        exit(1);
    }
}

void RPN::startCalculating(std::string str){
    std::stringstream ss(str);
    std::string s;
    while (getline(ss, s, ' '))
        parserAndCalculate(m_calculation, s);
    if (m_calculation.size() >= 2)
        std::cout << "Incorect input" << std::endl;
    else
        std::cout << m_calculation.top() << std::endl;
}

