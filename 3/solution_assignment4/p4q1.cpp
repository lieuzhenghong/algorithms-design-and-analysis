#include <iostream>
#include <vector>
#include <array>
#include <memory>

#define ll long long

typedef std::vector<std::vector<ll>> grid;

struct item
{
    unsigned int value;
    unsigned int weight;
};

using std::array;
using std::cin;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;

void read_input(int &num_items, int &capacity, std::vector<item> &items)
{
    unsigned int w, v;
    cin >> capacity >> num_items;
    items.push_back({0, 0});
    while (cin >> v >> w)
    {
        items.push_back({v, w});
    }
}

auto max(ll a, ll b)
{
    return (a > b) ? a : b;
}

void solve_knapsack(int &num_items, int &capacity, std::vector<item> &items, grid &g)
{
    for (int i = 0; i <= num_items; i++)
    {
        g.push_back({});
    }

    for (int items_allowed = 0; items_allowed <= num_items; items_allowed++)
    {
        item i = items[items_allowed];
        cout << "item num: " << items_allowed << " value: " << i.value << " weight: " << i.weight << endl;
        for (int cap_allowed = 0; cap_allowed < capacity + 1; cap_allowed++)
        {
            if (items_allowed == 0)
                g[items_allowed].push_back(0);
            else if (cap_allowed < i.weight)
            {
                g[items_allowed].push_back(
                    max(0, g[items_allowed - 1][cap_allowed]));
            }
            else
            {
                g[items_allowed].push_back(
                    max(
                        g[items_allowed - 1][cap_allowed],
                        g[items_allowed - 1][cap_allowed - i.weight] + i.value));
            }
        }
    }
}

int main()
{
    int num_items;
    int capacity;
    vector<item> items;
    grid g;

    read_input(num_items, capacity, items);
    solve_knapsack(num_items, capacity, items, g);

    //cout << num_items << capacity;

    // Grab the last element of the array
    cout << g[num_items][capacity];

    cout << endl;

    /*
    for (int i = 0; i <= num_items; i++)
    {
        for (auto &e : g[i])
        {
            cout << e << " ";
        }
        cout << endl;
    }

    */

    return 0;
}