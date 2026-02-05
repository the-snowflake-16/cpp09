

#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <cstdlib>
#include <climits>

struct Group {
    int larger;         
    std::vector<int> smaller_elements; 
};

class PmergeMe
{
private:
    std::vector<Group> groups;

public:
    // PmergeMe(/* args */);
    // ~PmergeMe();
    bool isNumber(const std::string &s);
    int safeAtoi(const std::string &s);
    void parseInput(int argc, char **argv,
                std::vector<int> &vec,
                std::deque<int> &deq);
    void makePairs(const std::vector<int>& input);
    void getPairs() const;
    void sortGroups();
};

void PmergeMe::getPairs() const
{
    for (size_t i = 0; i < groups.size(); ++i)
    {
        std::cout << "Group " << i << ": ";
        for (size_t j = 0; j < groups[i].smaller_elements.size(); ++j)
        {
            std::cout << groups[i].smaller_elements[j] << " ";
        }
        std::cout << "(larger=" << groups[i].larger << ")";
        std::cout << std::endl;
    }
}

bool PmergeMe::isNumber(const std::string &s)
{
    if (s.empty())
        return false;
    for (size_t i = 0; i < s.length(); i++)
    {
        if (!std::isdigit(s[i]))
            return false;
    }
    return true;
}

int PmergeMe::safeAtoi(const std::string &s)
{
    long long n = std::atoll(s.c_str());
    if (n > INT_MAX)
        throw std::runtime_error("Error");
    return static_cast<int>(n);
}

void PmergeMe::parseInput(int argc, char **argv,
                std::vector<int> &vec,
                std::deque<int> &deq)
{
    if (argc < 2)
        throw std::runtime_error("Error");

    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);

        if (!isNumber(arg))
            throw std::runtime_error("Error");

        int value = safeAtoi(arg);
        vec.push_back(value);
        deq.push_back(value);
    }
}



void PmergeMe::makePairs(const std::vector<int>& input) {
    groups.clear();
    for (size_t i = 0; i + 1 < input.size(); i += 2) {
        Group g;
        if (input[i] > input[i + 1]) {
            g.larger = input[i];
            g.smaller_elements.push_back(input[i + 1]);
        } else {
            g.larger = input[i + 1];
            g.smaller_elements.push_back(input[i]);
        }
        groups.push_back(g);
    }
    if (input.size() % 2 == 1) {
        Group g;
        g.larger = input.back();
        groups.push_back(g);
    }
}

void PmergeMe::sortGroups() {
    if (groups.size() <= 1) return;

    std::vector<Group> next_level;
    Group* straggler = NULL;
    
    // If odd number of groups, save the last one to re-add later
    if (groups.size() % 2 != 0) {
        straggler = new Group(groups.back());
        groups.pop_back();
    }

    for (size_t i = 0; i < groups.size(); i += 2) {
        // Compare the 'larger' elements
        if (groups[i].larger < groups[i + 1].larger) {
            std::swap(groups[i], groups[i+1]);
        }
        // Winner (groups[i]) keeps its larger, 
        // Loser (groups[i+1])'s 'larger' moves into Winner's 'smaller_elements'
        groups[i].smaller_elements.push_back(groups[i+1].larger);
        // Move loser's previous smaller elements too
        groups[i].smaller_elements.insert(groups[i].smaller_elements.end(), 
                                        groups[i+1].smaller_elements.begin(), 
                                        groups[i+1].smaller_elements.end());
        next_level.push_back(groups[i]);
    }

    groups = next_level;
    sortGroups();

    // Re-insert straggler if it existed
    if (straggler) {
        // Logic to insert straggler back into the groups vector
        delete straggler;
    }
}


int main(int argc, char **argv)
{
    try
    {
        std::vector<int> vec;
        std::deque<int> deq;
        PmergeMe pmerge;
        pmerge.parseInput(argc, argv, vec, deq);

        // Call Ford–Johnson 
        // fordJohnsonSort(vec);
        // fordJohnsonSort(deq);
        std::cout << "\n";
        std::cout << "----------vector--------" << std::endl;
        for (size_t i = 0; i < vec.size(); i++)
            std::cout << vec[i] << " ";
        std::cout << std::endl;
        std::cout << "\n";
        std::cout << "----------deque--------" << std::endl;
        for (size_t i = 0; i < vec.size(); i++)
            std::cout << deq[i] << " ";
        std::cout << std::endl;

        pmerge.makePairs(vec);
        pmerge.getPairs();
        pmerge.sortGroups();
                std::cout << "----------second--------" << std::endl;

        pmerge.getPairs();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}