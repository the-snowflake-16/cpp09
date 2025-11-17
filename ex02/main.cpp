#include "PmergeMe.cpp"

std::vector<int> GenerateJacobsthal(int n) {
    std::vector<int> jacob;
    if (n <= 0) return jacob;
    jacob.push_back(0);
    if (n == 1) return jacob;
    jacob.push_back(1);
    // Sequence: t_k = t_{k-1} + 2 * t_{k-2}
    for (int i = 2; i < n; ++i) {
        jacob.push_back(jacob[i-1] + 2 * jacob[i-2]);
    }
    return jacob;
}

template <typename Container>
void BinaryInsert(Container &vec, int value, int *counter) {
    int left = 0;
    int right = static_cast<int>(vec.size());

    while (left < right) {
        int mid = (left + right) / 2;
        if (value < vec[mid])
            right = mid;
        else
            left = mid + 1;
    }
    
    if (counter)
        (*counter)++; 
        
    typename Container::iterator it = vec.begin();
    std::advance(it, left);
    vec.insert(it, value);
}

template <typename Container>
void MergeInsertionPhase(Container& biggest,
                           const Container& lowest,
                           int* counter)
{
    if (lowest.empty()) return;

    BinaryInsert(biggest, lowest[0], counter);


    if (lowest.size() == 1) return;

    std::vector<int> J = GenerateJacobsthal(lowest.size() + 2);

    size_t prev = 1;

    for (size_t k = 2; k < J.size(); ++k)
    {
        size_t curr = J[k];
        if (curr >= lowest.size())
            curr = lowest.size() - 1;

        for (size_t i = curr; i >= prev; --i)
            BinaryInsert(biggest, lowest[i], counter);

        if (curr == lowest.size() - 1)
            return;

        prev = curr + 1;
    }
}

template <typename Container>
void GenerateVector(Container &pmerge, int *counter) {

    if(pmerge.size() <= 1)
        return;
    
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i + 1 < pmerge.size(); i += 2) {
        if(pmerge[i] > pmerge[i+1])
            pairs.push_back(std::make_pair(pmerge[i+1], pmerge[i]));
        else
            pairs.push_back(std::make_pair(pmerge[i], pmerge[i + 1]));
    }
    
    Container biggest;
    Container lowest;
    
    for(size_t j = 0 ; j < pairs.size(); j++) {
        biggest.push_back(pairs[j].second);
        lowest.push_back(pairs[j].first);
        (*counter)++;
    }
    
    if(pmerge.size() % 2 != 0) {
        lowest.push_back(pmerge[pmerge.size() - 1]);
    }
    
    GenerateVector(biggest, counter);
    
    MergeInsertionPhase(biggest, lowest, counter);
    
    pmerge = biggest;
}

void ParseInput(int argc, char *argv[], PmergeMe& pmerge){
    for(int i = 1; i < argc; i++){
        for (char *c = argv[i]; *c; ++c) {
            if (!std::isdigit(*c)) {
                std::cerr << "Error: Only positive integers are allowed." << std::endl;
                exit(1);
            }
        }
        int val = std::atoi(argv[i]);
        if (val < 0) {
            std::cerr << "Error: Only positive integers are allowed." << std::endl;
            exit(1);
        }
        
        pmerge.pmergeVec.push_back(val);
        pmerge.pmergeDeq.push_back(val);
    }
}

template <typename Container>
void RunAndDisplay(const char* name, Container& data, int& counter) {
    
    std::cout << "Before: ";
    for (size_t i = 0; i < data.size(); ++i)
        std::cout << data[i] << " ";

    std::cout << std::endl;

    clock_t start = clock();
    
    GenerateVector(data, &counter);
    
    double duration = static_cast<double>(clock() - start) / CLOCKS_PER_SEC * 1000;

    std::cout << "After (" << name << "): ";
    for (size_t i = 0; i < data.size(); ++i)
        std::cout << data[i] << " ";
    std::cout << std::endl;
    
    std::cout << "Time to process a range of " << data.size() 
              << " elements with " << name << ": " 
              << std::fixed << std::setprecision(5) << duration << " ms" << std::endl;
    // std::cout << "Comparisons (" << name << "): " << counter << std::endl;
}

int main(int argc, char *argv[]){
    if (argc < 2) {
        std::cerr << "Usage: ./PmergeMe <list of positive integers>" << std::endl;
        return 1;
    }
    
    PmergeMe pmerge;
    

    ParseInput(argc, argv, pmerge);


    int counterVec = 0;
    int counterDeq = 0;

    std::cout << "\n--- Vector Implementation (std::vector) ---" << std::endl;
    RunAndDisplay("std::vector", pmerge.pmergeVec, counterVec);

    std::cout << "\n--- Deque Implementation (std::deque) ---" << std::endl;
    RunAndDisplay("std::deque", pmerge.pmergeDeq, counterDeq);
    
    return 0;
}
