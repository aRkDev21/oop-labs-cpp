#include <iostream>
#include <algorithm> // for std::transform
#include <list>


class Solution {
private:
    std::list<double> numbers;
    int size;

public:
    Solution(int n) : size(n) { }

    void init() {
        for (int i = 0; i < size; i++) {
            double f = rand() % size + (rand()%10)/10.;
            numbers.push_back(f);
        }
    }

    static double square(double x) { return x * x; }

    void print() {
        std::list<double>::iterator it;
        for (it = numbers.begin(); it != numbers.end(); it++) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    void transform() {
        std::transform(numbers.begin(), numbers.end(), numbers.begin(), square);
    }

    auto GetValueByIndex(int i) {
        std::list<double>::iterator it = numbers.begin();
        while (i-- > 0) it++;
        return it;
    }

    void run() {
        init();
        std::cout << "Init list: " << std::endl;
        print();

        transform(); 
        std::cout << "Squared list: " << std::endl;
        print();

        int index = rand() % 10;
        auto it = GetValueByIndex(index);
        std::cout << "Get item with index = " << index << ": " << *it << std::endl;

        std::cout << "Insert -1 at index = " << index << std::endl;
        numbers.insert(it, -1);
        print();
    }
};

int main() {
    srand(time(0));
    
    Solution sol(10);
    sol.run();
    return 0;
}