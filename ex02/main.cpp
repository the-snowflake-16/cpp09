#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <ctime>

struct Group {
    int larger;
    std::vector<int> smaller_elements;
};

class PmergeMe {
private:
    std::vector<Group> _groups;
    int _straggler;
    bool _hasStraggler;
    long _comparisons; // счетчик сравнений

public:
    PmergeMe() : _straggler(-1), _hasStraggler(false), _comparisons(0) {}

    bool isNumber(const std::string &s);
    int safeAtoi(const std::string &s);
    void parseInput(int argc, char **argv, std::vector<int> &vec);

    void sortVector(std::vector<int>& input);

    long getComparisons() const { return _comparisons; }

private:
    void recursiveSort(std::vector<Group>& groups);
    std::vector<size_t> generateJacobsthalIndices(size_t n);
};

bool PmergeMe::isNumber(const std::string &s) {
    if (s.empty()) return false;
    for (size_t i = 0; i < s.length(); ++i) {
        if (!std::isdigit(s[i])) return false;
    }
    return true;
}

int PmergeMe::safeAtoi(const std::string &s) {
    long long n = std::atoll(s.c_str());
    if (n > INT_MAX || n < 0) throw std::runtime_error("Error: invalid number");
    return static_cast<int>(n);
}

void PmergeMe::parseInput(int argc, char **argv, std::vector<int> &vec) {
    for (int i = 1; i < argc; i++) {
        if (!isNumber(argv[i])) throw std::runtime_error("Error: invalid input");
        vec.push_back(safeAtoi(argv[i]));
    }
}

std::vector<size_t> PmergeMe::generateJacobsthalIndices(size_t n) {
    std::vector<size_t> indices;
    if (n == 0) return indices;

    std::vector<size_t> jacob;
    jacob.push_back(1);
    jacob.push_back(3);
    while (jacob.back() < n) {
        jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);
    }

    size_t last_pos = 0;
    for (size_t i = 0; i < jacob.size(); ++i) {
        size_t pos = jacob[i];
        if (pos > n) pos = n;
        for (size_t j = last_pos; j < pos; ++j) {
            indices.push_back(j);
        }
        last_pos = pos;
    }
    return indices;
}

void PmergeMe::recursiveSort(std::vector<Group>& groups) {
    if (groups.size() <= 1) return;

    std::vector<Group> next_level;
    bool has_odd = (groups.size() % 2 != 0);
    Group odd_group;
    if (has_odd) {
        odd_group = groups.back();
        groups.pop_back();
    }

    for (size_t i = 0; i < groups.size(); i += 2) {
        _comparisons++;
        if (groups[i].larger < groups[i + 1].larger) {
            std::swap(groups[i], groups[i + 1]);
        }
        groups[i].smaller_elements.push_back(groups[i + 1].larger);
        groups[i].smaller_elements.insert(groups[i].smaller_elements.end(),
                                         groups[i + 1].smaller_elements.begin(),
                                         groups[i + 1].smaller_elements.end());
        next_level.push_back(groups[i]);
    }

    recursiveSort(next_level);

    if (has_odd) next_level.push_back(odd_group);
    groups = next_level;
}

void PmergeMe::sortVector(std::vector<int>& input) {
    // _comparisons = 0;
    if (input.size() <= 1) return;

    _hasStraggler = (input.size() % 2 != 0);
    if (_hasStraggler) {
        _straggler = input.back();
        input.pop_back();
    }

    std::vector<Group> current_groups;
    for (size_t i = 0; i < input.size(); i += 2) {
        _comparisons++; 
        Group g;
        if (input[i] > input[i + 1]) {
            g.larger = input[i];
            g.smaller_elements.push_back(input[i + 1]);
        } else {
            g.larger = input[i + 1];
            g.smaller_elements.push_back(input[i]);
        }
        current_groups.push_back(g);
    }

    _groups = current_groups;
    recursiveSort(_groups);

 
    std::vector<int> main_chain;
    std::vector<int> pend;

    for (size_t i = 0; i < _groups.size(); ++i) {
        main_chain.push_back(_groups[i].larger);
        for (size_t j = 0; j < _groups[i].smaller_elements.size(); ++j) {
            pend.push_back(_groups[i].smaller_elements[j]);
        }
    }

  
    std::vector<size_t> jacob_indices = generateJacobsthalIndices(pend.size());
    for (size_t i = 0; i < jacob_indices.size(); ++i) {
        size_t idx = jacob_indices[i];
        if (idx < pend.size()) {
            int target = pend[idx];

            size_t low = 0, high = main_chain.size();
            while (low < high) {
                size_t mid = low + (high - low) / 2;
                _comparisons++;
                if (main_chain[mid] < target)
                    low = mid + 1;
                else
                    high = mid;
            }
            main_chain.insert(main_chain.begin() + low, target);
        }
    }

    // Insert straggler
    if (_hasStraggler) {
        size_t low = 0, high = main_chain.size();
        while (low < high) {
            size_t mid = low + (high - low) / 2;
            // _comparisons++; // Count actual comparison
            if (main_chain[mid] < _straggler)
                low = mid + 1;
            else
                high = mid;
        }
        main_chain.insert(main_chain.begin() + low, _straggler);
        _hasStraggler = false;
    }

    input = main_chain;
}


int main(int argc, char **argv) {
    if (argc < 2) return 1;

    try {
        PmergeMe p;
        std::vector<int> vec;
        p.parseInput(argc, argv, vec);

        std::cout << "Before: ";
        for (size_t i = 0; i < vec.size(); ++i) std::cout << vec[i] << " ";
        std::cout << std::endl;

        clock_t start = clock();
        p.sortVector(vec);
        clock_t end = clock();

        std::cout << "After:  ";
        for (size_t i = 0; i < vec.size(); ++i) std::cout << vec[i] << " ";
        std::cout << std::endl;

        double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
        std::cout << "Time to process " << vec.size() << " elements: " << time << " us" << std::endl;
        std::cout << "Total comparisons: " << p.getComparisons() << std::endl;

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
