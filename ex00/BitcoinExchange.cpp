#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other){
    dataStone = other.dataStone;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other) {
    if(this != &other) {
        dataStone = other.dataStone;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange(){}

std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

bool isValidDate(int year, int month, int day) {
    // std::cout << "h"<< year << std::endl;
    std::tm t = {};
    t.tm_year = year - 1900;
    t.tm_mon  = month - 1;
    t.tm_mday = day;

    time_t temp = mktime(&t);
    if (temp == -1)
        return false;

    return (t.tm_year == year - 1900) && (t.tm_mon == month - 1) && (t.tm_mday == day);
}

bool checkData(std::string dataString){
    int year;
    int month;
    int day;
    std::string date[3];
    std::istringstream stream(dataString);

    std::string token;
    int i = 0;
    while (getline(stream, token, '-'))
    {
        date[i++] = token;
    }
    year = std::atoi(date[0].c_str());
    // std::cout << year << std::endl;
    month = std::atoi(date[1].c_str());
    day = std::atoi(date[2].c_str());
    if(!isValidDate(year, month, day)){
        return false;
    }
    std::string minDate = "2009-01-02";
    std::string maxDate = "2023-01-03";
    
    if (dataString < minDate || dataString > maxDate) {
        return false;
    }

    return true;
}

void BitcoinExchange::ParseFile(std::ifstream  &nameOfFile){

    std::string dataText;

    while (getline(nameOfFile, dataText)) {
        size_t pos = dataText.find(',');

        std::string before = trim(dataText.substr(0, pos));
        std::string after  = trim(dataText.substr(pos + 1));
        
        float afterFloat = std::atof(after.c_str());
        dataStone.insert(std::make_pair(before, afterFloat));
    }

}

void BitcoinExchange::ParseInputFile(std::ifstream &nameOfInputFile){

    std::string inputText;

    while (getline(nameOfInputFile, inputText)) {
        size_t pos = inputText.find('|');
        if(pos == std::string::npos) {
            std::cout << "Error: bad input => " << inputText << std::endl;
            continue;
        }
        std::string before = trim(inputText.substr(0, pos));
        std::string after = trim(inputText.substr(pos + 1));
        if(before == "date"){
            continue;
        }else if (after.empty()) {
            std::cout << "Error: missing value => " << inputText << std::endl;
            continue;
        } else if(std::atof(after.c_str()) < 0) {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        } else if (std::atof(after.c_str()) > INT_MAX){
            std::cout << "Error: too large a number." << std::endl;
            continue;
        } 
        float afterFloat = std::atof(after.c_str());

        std::map<std::string, float>::iterator it = dataStone.upper_bound(before);
        if (it == dataStone.begin()) {
            std::cout << "Error: no available rate for date <= " << before << std::endl;
        } else {
            --it; 
            std::cout << before << " => " << after << " = " << afterFloat * it->second << std::endl;
        }
        if(checkData(before)){
        std::map<std::string, float>::iterator it = this->dataStone.begin();
        std::string dateStr;
        while (it->first <= before)
        {
            dateStr = it->first;
            it++;
        }
        std::cout << before << " => " << after << " = " << afterFloat * it->second << std::endl;
        } else{
        std::cout << "Not valide date" << std::endl;
        }
    }
}

// struct tm {
//     int tm_sec;   // sec [0, 60]
//     int tm_min;   // min [0, 59]
//     int tm_hour;  // hour [0, 23]
//     int tm_mday;  // days [1, 31]
//     int tm_mon;   // monthes [0, 11]  !!! jan = 0
//     int tm_year;  // from 1900
//     int tm_wday;  // day [0,6] sun = 0
//     int tm_yday;  // day of year [0,365]
//     int tm_isdst; // summer time
// };


