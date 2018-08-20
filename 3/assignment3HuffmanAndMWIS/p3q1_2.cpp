/*
In this programming problem and the next you'll code up the greedy algorithm from the lectures on Huffman coding.

 The input file describes an instance of the problem. It has the following format:

 \[number_of_symbols\]
 \[weight of symbol #1\]
 \[weight of symbol #2\]
 ...

 For example, the third line of the file is "6852892," indicating that the weight of the second symbol of the alphabet is 6852892. (We're using weights instead of frequencies, like in the "A More Complex Example" video)

 Your task in this problem is to run the Huffman coding algorithm from lecture on this data set. What is the maximum length of a codeword in the resulting Huffman code?
 */

/*
Greedy algorithm:
1. Take the two smallest weights
2. Add them up
3. Get the sum
*/

#include <iostream>
#include <queue>
#include <string>
#define ll long long

struct tree
{
    int symbol;
    ll weight;
    tree *left_child = NULL;
    tree *right_child = NULL;
};

auto cmp = [](tree *t1, tree *t2) { return t1->weight > t2->weight; };
std::priority_queue<tree *, std::vector<tree *>, decltype(cmp)> q(cmp);
std::vector<tree *> trees;
int number_of_symbols;
ll total_weight;
unsigned int min_length = INT_MAX;
unsigned int max_length = 0;

void print_tree(tree *t, std::string s)
{
    if (t == NULL)
    {
        return;
    }
    else
    {
        //std::cout << s << ": " << t->symbol << ", " << t->weight << std::endl;
        if (t->symbol != 0 && (s.length() > max_length))
        {
            max_length = s.length();
        }
        if (t->symbol != 0 && (s.length() < min_length))
        {
            min_length = s.length();
        }
        //std::cout << "Left child: " << t->left_child->symbol << ", " << t->left_child->weight << std::endl;
        //std::cout << "Right child: " << t->right_child->symbol << ", " << t->right_child->weight << std::endl;
        print_tree(t->left_child, s + "0");
        print_tree(t->right_child, s + "1");
    }
}

int main()
{
    int symbol = 1;
    ll weight;

    std::cin >> number_of_symbols;

    while (std::cin >> weight)
    {
        tree *t = new tree();
        t->symbol = symbol;
        t->weight = weight;
        q.push(t);
        trees.push_back(t);
        symbol++;
        total_weight += weight;
    }

    while (q.size() > 1)
    {
        tree *t1 = q.top();
        q.pop();
        tree *t2 = q.top();
        q.pop();
        //std::cout << "Left child: " << t1->symbol << ": " << t1->weight << std::endl;
        //std::cout << "Right child: " << t2->symbol << ": " << t2->weight << std::endl;
        tree *t3 = new tree({0,
                             (t1->weight + t2->weight),
                             t1,
                             t2});
        //std::cout << "  " << t3->weight << std::endl;
        //std::cout << (t3->left_child)->weight << "    " << (t3->right_child)->weight << std::endl;
        q.push(t3);
    }

    // We now have a complete Huffman tree
    tree *final_tree = q.top();
    std::cout << "Printing final tree" << std::endl;
    print_tree(final_tree, "");

    std::cout << "Max length: " << max_length << std::endl;
    std::cout << "Min length: " << min_length << std::endl;
    std::cout << "Total weight: " << total_weight << std::endl;
    std::cout << "MAX WEIGHT: " << LLONG_MAX << std::endl;
    std::cout << "Ratio: " << (total_weight / LLONG_MAX) << std::endl;

    // Free memory
    for (auto t : trees)
    {
        //std::cout << "deleting memaddr " << t << std::endl;
        delete t;
    }
}