#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> subset;

subset n_choose_m(std::vector<int> set, int m)
{

    // Pick a pair
    for (int i = 0; i < m; i++)
    {
        for (auto &e : set)
        {
        }
    }

    // guaranteed that
    for (auto &a : set)
    {
        for (auto &b : set)
        {
            if (a != = b)
            {
                std::cout << a << " " << b << " " << std::endl;
            }
        }
    }

    return all_tuples;
}

int main()
{
    return 0;
}