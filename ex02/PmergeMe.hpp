#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath> 
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <utility>
#include <cmath>
#include <ctime>
#include <iomanip> 

class PmergeMe
{

public:
    std::vector<int> pmergeVec;
    std::deque<int> pmergeDeq;

    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();
};
