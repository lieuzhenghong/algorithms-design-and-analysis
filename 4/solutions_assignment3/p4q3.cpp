/*
The first line indicates the number of cities. Each city is a point in the
plane, and each subsequent line indicates the _x_ and _y_-coordinates of a
single city.

The distance between two cities is defined as the Euclidean distance --- that
is, two cities at locations (_x_,_y_) and (_z_,_w_) have distance
_sqrt((x−z)<sup>2</sup>+(y−w)<sup>2</sup>_) between them. You should
implement the _nearest neighbor_ heuristic:

1. Start the tour at the first city. 2. Repeatedly visit the closest city
that the tour hasn't visited yet. _In case of a tie, go to the closest city
with the lowest index_. For example, if both the third and fifth cities have
the same distance from the first city (and are closer than any other city),
then the tour should begin by going from the first city to the third city. 3.
Once every city has been visited exactly once, return to the first city to
complete the tour.

Submit the cost of the traveling salesman tour computed by the nearest
neighbor heuristic for this instance, _rounded down to the nearest integer_.

[Hint: when constructing the tour, you might find it simpler to work with
squared Euclidean distances (i.e., the formula above but without the square
root) than Euclidean distances. But don't forget to report the length of the
tour in terms of standard Euclidean distance.]

*/

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <limits>
#include <chrono>

const long double _INFINITY = std::numeric_limits<long double>::infinity();
const int MAX_CITIES = 100000;
std::array<bool, MAX_CITIES> visited = {0};
std::vector<long double> squared_distances;
std::vector<int> path;

struct city
{
    int id;
    long double x;
    long double y;
};

std::vector<city> cities;

auto ed_2(city &a, city &b)
{
    return std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    auto time_started = std::chrono::steady_clock::now();
    int id;
    long double x, y;
    int num_cities;

    std::cin >> num_cities;
    // First push a dummy city into cities to 1-index it
    cities.push_back({0, _INFINITY, _INFINITY});

    while (std::cin >> id >> x >> y)
    {
        city c;
        c.id = id;
        c.x = x;
        c.y = y;
        cities.push_back(c);
    }
    // we start with the first city
    path.push_back(1);
    squared_distances.push_back(0);
    visited[1] = true;
    visited[0] = true;

    // Calculate distances to all unvisited cities
    int best_city;
    long double best_distance;
    long double curr_distance;
    // Double for loop
    for (int city = 1; city <= num_cities; city++)
    {
        best_city = 0;
        best_distance = _INFINITY;
        for (int i = 1; i <= num_cities; i++)
        {
            if (!visited[i] && i != path.back())
            {
                curr_distance = ed_2(cities[path.back()], cities[i]);
                //std::cout << "Distance between " << path.back() << " and " << i << ": " << curr_distance << std::endl;
                if (curr_distance <= best_distance)
                {
                    best_distance = curr_distance;
                    best_city = i;
                }
            }
        }
        // Add best_city into the visited list
        // If we have no more cities left, add back distance for city 1
        if (best_city == 0)
        {
            squared_distances.push_back(ed_2(cities[path.back()], cities[1]));
            path.push_back(1);
            break;
        }
        else
        {
            path.push_back(best_city);
            squared_distances.push_back(best_distance);
            visited[best_city] = true;
        }
    }

    /*
    for (auto &city : path)
    {
        std::cout << city << " ";
    }
    std::cout << std::endl;
    for (auto &city : squared_distances)
    {
        std::cout << city << ", ";
    }
    std::cout << std::endl;
    */
    long double total_distance = 0;
    for (auto &dist : squared_distances)
    {
        total_distance += std::sqrt(dist);
    }
    std::cout.precision(17);
    std::cout << "Total distance: " << total_distance << std::endl;
    auto time_ended = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(time_ended - time_started).count() << std::endl;

    return 0;
}