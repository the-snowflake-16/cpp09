#include "PmergeMe.hpp"

void parse_input(int argc, char *argv[], std::vector<int> &pmerge){
    (void) pmerge;
    for(int i = 1; i < argc; i++){
        pmerge.push_back(std::atoi(argv[i]));
        // std::cout << argv[i] << std::endl;
    }
}

std::vector<int> generate_jacobsthal(int n) {
    // (void) n;
    std::vector<int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);

    for(int i = 1; i < n; i++) {
        jacobsthal.push_back(jacobsthal[i] +  2 * jacobsthal[i-1]);
    }
    for(unsigned int i = 0; i < jacobsthal.size(); i++) {
        std::cout << jacobsthal[i] << " ";
    }
    std::cout << std::endl;

    return jacobsthal;
}

std::vector<int> build_final(std::vector<int*> &biggest, std::vector<int*> &lowest) {
    std::vector<int> sorted;

    if (lowest.empty()) return sorted;

    // Шаг 1: кладём первый элемент lowest в начало
    sorted.push_back(*lowest[0]);

    // Шаг 2: добавляем отсортированные biggest
    for (size_t i = 0; i < biggest.size(); i++) {
        sorted.push_back(*biggest[i]);
    }

    std::vector<int> jacobsthal = generate_jacobsthal(lowest.size());
    return sorted;
}

void sorting_ptrs(std::vector<int*> &pmerge) {
    // std::cout << "pmerge" << std::endl;
    // for (unsigned long i = 0; i < pmerge.size(); i++) {
    //     std::cout << *pmerge[i] << " | ";
    // }
    // std::cout << std::endl;
    std::vector<int*> biggest;
    std::vector<int*> lowest;
    if (pmerge.size() >= 2) {

        // unsigned long paire = (pmerge.size() % 2 == 0) ? pmerge.size() : pmerge.size() - 1;

        // for (unsigned long i = 0; i < paire; i += 2) {
        //     if (*pmerge[i] > *pmerge[i+1])
        //         std::swap(*pmerge[i], *pmerge[i+1]);
        // }
        for (unsigned long j = 0; j < pmerge.size(); j++){
            std::cout << *pmerge[j] << " | ";
        }
        std::cout  << std::endl;
        for(unsigned long j = 0; j < pmerge.size(); j+=2){
            lowest.push_back(pmerge[j]);
            if(pmerge[j+1])
                biggest.push_back(pmerge[j+1]);
        }
        std::cout << "BIGGEST" << std::endl;
        for (unsigned long i = 0; i < biggest.size(); i++) {
            std::cout << *biggest[i] << " | ";
        }
        std::cout << std::endl;
        std::cout << "lOWEST" << std::endl;
        for (unsigned long i = 0; i < lowest.size(); i++) {
            std::cout << *lowest[i] << " | ";
        }
        std::cout << std::endl;
        unsigned long paire = (biggest.size() % 2 == 0) ? biggest.size() : biggest.size() - 1;
        for (unsigned long i = 0; i < paire; i += 2) {
            if (*biggest[i] > *biggest[i+1]){
                std::swap(*biggest[i], *biggest[i+1]);
                std::swap(*lowest[i], *lowest[i+1]);
            }
        }
        std::cout << "BIGGEST after" << std::endl;
        for (unsigned long i = 0; i < biggest.size(); i++) {
            std::cout << *biggest[i] << " | ";
        }
        std::cout << std::endl;
        std::cout << "lOWEST after" << std::endl;
        for (unsigned long i = 0; i < lowest.size(); i++) {
            std::cout << *lowest[i] << " | ";
        }
        std::cout << std::endl;
        sorting_ptrs(biggest);
    }

        // int i = 0;
        // biggest.push_back(lowest[i]);
    std::cout << "BIGGEST afterRRRRRR" << std::endl;
    for (unsigned long i = 0; i < biggest.size(); i++) {
        std::cout << *biggest[i] << " | ";
    }
    std::cout << std::endl;
    std::cout << "lOWEST afterRRRRRRR" << std::endl;
        for (unsigned long i = 0; i < lowest.size(); i++) {
            std::cout << *lowest[i] << " | ";
        }
    std::cout << std::endl;

    std::vector<int> final = build_final(biggest, lowest);
    std::cout << "final after final" << std::endl;
        for (unsigned long i = 0; i < final.size(); i++) {
            std::cout << final[i] << " | ";
        }
    std::cout << std::endl;  
}

void sorting (std::vector<int> &pmerge){
    std::cout << "vector pmerge:" << std::endl;
    for (unsigned long i = 0; i < pmerge.size(); i++) {
        std::cout << pmerge[i] << " | ";
    }
    std::cout << std::endl;
        unsigned long paire;
        if(pmerge.size() % 2 == 0){
            paire = pmerge.size();
        } else {
            paire = pmerge.size() -1;
        }
        for (unsigned long i = 0; i < paire; i+=2) {
            if(pmerge[i] > pmerge[i+1])
                std::swap(pmerge[i], pmerge[i+1]);
            // for (unsigned long j = 0; j < pmerge.size(); j++){
            //     std::cout << pmerge[j] << " | ";
            // }
            // std::cout  << std::endl;
        }
        std::vector<int*> ptrs;
        for (size_t i = 0; i < pmerge.size(); i++) {
            ptrs.push_back(&pmerge[i]);
        }
        sorting_ptrs(ptrs);
    // }
    std::cout << "vector pmerge after:" << std::endl;
    for (unsigned long i = 0; i < pmerge.size(); i++) {
        std::cout << pmerge[i] << " | ";
    }
    std::cout << std::endl;
    // build_final()
}


// int main(int argc, char *argv[]){
//     if(argc < 2)
//         return 0;
//     PmergeMe pmerge;
//     parse_input(argc, argv, pmerge.pmerge);
//     sorting(pmerge.pmerge);
//     std::cout << "lOWEST afterRRRRRRR" << std::endl;
//         for (unsigned long i = 0; i < pmerge.pmerge.size(); i++) {
//             std::cout << pmerge.pmerge[i] << " | ";
//         }
//     std::cout << std::endl;
// }

int main() {
    generate_jacobsthal(18);
}
