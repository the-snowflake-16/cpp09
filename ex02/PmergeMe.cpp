#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &other){
    pmergeDeq = other.pmergeDeq;
    pmergeVec = other.pmergeVec;
}
PmergeMe& PmergeMe::operator=(const PmergeMe & other)
{
    if(this != &other) {
        pmergeDeq = other.pmergeDeq;
        pmergeVec = other.pmergeVec;
    }
    return *this;
}

PmergeMe::~PmergeMe(){}
