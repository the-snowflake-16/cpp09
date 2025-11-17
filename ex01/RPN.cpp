#include "RPN.hpp"

RPN::RPN(){}

RPN::RPN(const RPN &other) {
    m_calculation = other.m_calculation;
}

RPN& RPN::operator=(const RPN &other){
    if(this != &other) {
        m_calculation = other.m_calculation;
    }
    return *this;
}

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

void checkResult(int a, int b, char op) {
    if (op == '+') {
        if (a > INT_MAX - b)
            throw std::runtime_error("overflow");
    }
    else if (op == '*') {
        if (b != 0 && a > INT_MAX / b)
            throw std::runtime_error("overflow");
    }
}

void processOfCalculatin(std::stack<int> &m_calculation, char sighn){
    if(m_calculation.size() >= 2){
        int firstValue = m_calculation.top();
        m_calculation.pop();
        int secondValue = m_calculation.top();
        m_calculation.pop();
    if (sighn == '+') {
        checkResult(secondValue, firstValue, sighn);
        m_calculation.push(secondValue + firstValue);
    }
    else if (sighn == '-') {
        m_calculation.push(secondValue - firstValue);
    }
    else if (sighn == '*') {
        checkResult(secondValue, firstValue, sighn);
        m_calculation.push(secondValue * firstValue);
    }
    else if (sighn == '/') {
        if (firstValue == 0)
            throw std::runtime_error("Incorrect input");
        m_calculation.push(secondValue / firstValue);
    }
    } 
}

void RPN::parserAndCalculate(std::stack<int> &m_calculation, std::string str){
    if (!validToken(str)) {
        throw std::runtime_error("Incorrect input");
    }
    if(std::isdigit(str[0])) {
        m_calculation.push(std::atoi(str.c_str()));
    } else if (((str[0] == '+') || (str[0] == '-') || (str[0] == '*') || (str[0] == '/')) && m_calculation.size() >= 2){
        processOfCalculatin(m_calculation , str[0]);
    } else {
        throw std::runtime_error("Incorrect input");
    }
}

void RPN::startCalculating(std::string str){
    try {
        std::stringstream ss(str);
        std::string s;

        while (getline(ss, s, ' ')) {
            if (!s.empty())
                parserAndCalculate(m_calculation, s);
        }

        if (m_calculation.size() != 1)
            throw std::runtime_error("Incorrect input");

        std::cout << m_calculation.top() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
