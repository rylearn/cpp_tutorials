#include <vector>
#include <algorithm>
#include <iostream>
 
struct Income
{
public:
    Income(): average{0}, running_count{0} { }
    void operator()(int n) { 
        average = (running_count * average + n) / (running_count + 1); 
        running_count += 1;
    }
    double average;
    int running_count;
};
 
int main()
{
    std::vector<int> nums{40000, 50000, 140000, 150000};
 
    auto print = [](const int& n) { std::cout << " " << n; };

    std::for_each(nums.begin(), nums.end(), print);
    std::cout << '\n';
 
    // calls Income::operator() for each number
    Income s = std::for_each(nums.begin(), nums.end(), Income());

    std::cout << "Income average: " << s.average << '\n';
}