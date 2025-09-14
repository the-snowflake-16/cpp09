#pragma once

#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
#include <iomanip>
#include <limits.h>

class BitcoinExchange
{
private:
    std::map<std::string, float> dataStone;
public:
    BitcoinExchange();
    ~BitcoinExchange();

    std::map<std::string, float> getDataStone()const{
        return dataStone;
    }

    void ParseFile(std::ifstream  &nameOfFile);
    void ParseInputFile(std::ifstream &nameOfInputFile);
};

