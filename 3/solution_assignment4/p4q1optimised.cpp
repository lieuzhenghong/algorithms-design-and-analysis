#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <algorithm>

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

vector<ll> prev_vec;
vector<ll> curr_vec;

void solve_knapsack(int &num_items, int &capacity, std::vector<item> &items, grid &g)
{

    for (int items_allowed = 0; items_allowed <= num_items; items_allowed++)
    {
        item i = items[items_allowed];

        prev_vec = curr_vec;
        curr_vec = {};

        //cout << "item num: " << items_allowed << " value: " << i.value << " weight: " << i.weight << endl;
        /*
        cout << "Previous vector: [";
        for (auto &v : prev_vec)
        {
            cout << v << " ";
        }
        cout << "] " << endl;
        */

        for (int cap_allowed = 0; cap_allowed < capacity + 1; cap_allowed++)
        {
            if (items_allowed == 0)
            {
                curr_vec.push_back(0);
            }
            else if (cap_allowed < i.weight)
            {
                curr_vec.push_back(max(0, prev_vec[cap_allowed]));
            }
            else
            {
                curr_vec.push_back(
                    max(
                        prev_vec[cap_allowed],
                        prev_vec[cap_allowed - i.weight] + i.value));
            }
            //cout << curr_vec.back() << " ";
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    int num_items;
    int capacity;
    vector<item> items;
    grid g;

    read_input(num_items, capacity, items);
    solve_knapsack(num_items, capacity, items, g);

    /*

    for (int i = 0; i < capacity + 1; i++)
    {
        cout << prev_vec[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < capacity + 1; i++)
    {
        cout << curr_vec[i] << " ";
    }
    cout << endl;
    */

    cout << curr_vec.back();
    cout << endl;

    return 0;
}