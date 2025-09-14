#include "BitcoinExchange.hpp"




int main(int argc, char *argv[]){
    if(argc != 2)
        return 0;
    std::ifstream dataCsv("data.csv");
    std::ifstream inputFile(argv[1]);

    BitcoinExchange bitcoin;

    bitcoin.ParseFile(dataCsv);
    bitcoin.ParseInputFile(inputFile);
    dataCsv.close();
    inputFile.close();
}