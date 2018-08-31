/*
## Programming Assignment #2

In this assignment you will implement one or more algorithms for the traveling salesman problem, such as the dynamic programming algorithm covered in the video lectures.

The first line indicates the number of cities. Each city is a point in the plane, and each subsequent line indicates the x- and y-coordinates of a single city.

The distance between two cities is defined as the Euclidean distance --- that is, two cities at locations (_x_,_y_) and (_z_,_w_) have distance _sqrt((x−z)<sup>2</sup>+(y−w)<sup>2</sup>_) between them.

Submit the minimum cost of a traveling salesman tour for this instance, _rounded down to the nearest integer_.

OPTIONAL: If you want bigger data sets to play with, check out the TSP instances from around the world [here](http://www.math.uwaterloo.ca/tsp/world/countries.html). The smallest data set (Western Sahara) has 29 cities, and most of the data sets are much bigger than that. What's the largest of these data sets that you're able to solve --- using dynamic programming or, if you like, a completely different method?

HINT: You might experiment with ways to reduce the data set size. For example, trying plotting the points. Can you infer any structure of the optimal solution? Can you use that structure to speed up your algorithm?
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <chrono>
#include <map>

struct city
{
    int node;
    double x;
    double y;
};

typedef std::vector<int> tuple;
typedef std::vector<tuple> tuples;

// Takes
auto slice = [](tuple s, int end_slice) {
    tuple s_2 = s;
    s_2.erase(s_2.begin(), s_2.begin() + end_slice);
    return s_2;
};

auto rmv = [](tuple s, int index) {
    tuple s_2 = s;
    s_2.erase(s_2.begin() + index);
    return s_2;
};

auto euclidean_distance(city a, city b)
{
    return std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
}

tuples n_choose_m(std::vector<int> s, int m)
{
    tuples all_tuples = {};

    if (m == 0)
    {
        return {{}};
    }
    else
    {
        int end_slice = 0;
        for (auto &city : s)
        {
            end_slice++;
            tuples subset = n_choose_m(rmv(s, end_slice - 1), m - 1);
            // Add in the first element
            for (auto &tuple : subset)
            {
                tuple.insert(tuple.begin(), s[end_slice - 1]);
            }
            all_tuples.insert(all_tuples.end(),
                              subset.begin(),
                              subset.end());
        }
    }

    return all_tuples;
}

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    std::ios_base::sync_with_stdio(false);
    auto time_started = std::chrono::steady_clock::now();

    int num_cities;
    int node = 1;
    double x;
    double y;
    std::map<int, std::vector<std::pair<tuple, double>>> min_costs;
    std::vector<city> all_cities = {{0, 0, 0}};
    std::vector<int> all_nodes;
    double min_cycle_cost = std::numeric_limits<double>::infinity();

    cin >> num_cities;

    while (cin >> x >> y)
    {
        all_cities.push_back({node, x, y});
        all_nodes.push_back(node);
        node++;
    }

    // Populate all n * 2^n subcases
    for (int i = 1; i < num_cities; i++)
    {
        tuples subset = n_choose_m((slice(all_nodes, 1)), i);

        for (auto &t : subset)
        {
            t.insert(t.begin(), 1);

            if (i == 1)
            {
                min_costs[1].push_back({t, euclidean_distance(all_cities[t[0]],
                                                              all_cities[t[1]])});
            }
            else
            {
                // From all the n possible i-1s, pick the min distance
                double prev_cost = std::numeric_limits<double>::infinity();
                tuple previous = rmv(t, i);
                int last_hop = t.back();
                // Grab the previous cost to get from 1 to the penultimate node
                for (auto &c : min_costs[i - 1])
                {
                    if (c.first == previous)
                    {
                        prev_cost = c.second;
                    }
                }

                // For each non-source node in the previous tuple, get
                //cout << "Previous cost: " << prev_cost << endl;
                double current_cost = euclidean_distance(all_cities[previous.back()],
                                                         all_cities[last_hop]);
                min_costs[i].push_back({t, current_cost + prev_cost});
            }
        }
    }

    /* ============ LAST HOP ============================= */

    // Iterate through all the tours less the last hop -> 1
    for (auto &tour : min_costs[num_cities - 1])
    {
        double final_hop_cost = euclidean_distance(all_cities[tour.first.back()], all_cities[1]);
        //cout << "Final hop cost: " << final_hop_cost << endl;
        if (min_cycle_cost > (tour.second + final_hop_cost))
        {
            min_cycle_cost = tour.second + final_hop_cost;
        }
    }

    std::cout << "Final best cost: " << min_cycle_cost;
    auto time_ended = std::chrono::steady_clock::now();
    std::cout << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(time_ended - time_started).count() << std::endl;

    return 0;
}