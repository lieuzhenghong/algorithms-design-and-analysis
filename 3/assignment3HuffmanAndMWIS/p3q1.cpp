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
    tree *left_child;
    tree *right_child;
};

auto cmp = [](tree t1, tree t2) { return t1.weight > t2.weight; };
std::priority_queue<tree, std::vector<tree>, decltype(cmp)> q(cmp);

void print_tree(tree *t, std::string s)
{
    if (t == NULL)
    {
        return;
    }
    else
    {
        std::cout << s << ": " << t->symbol << ", " << t->weight << std::endl;
        print_tree(t->left_child, s + "0");
        print_tree(t->right_child, s + "1");
    }
}

int main()
{
    int symbol = 1;
    ll weight;
    while (std::cin >> weight)
    {
        q.push({symbol, weight, NULL, NULL});
        symbol++;
    }

    while (q.size() > 1)
    {
        tree *t1;
        tree *t2;
        tree t3;
        std::cout << q.top().symbol << ": " << q.top().weight << std::endl;
        // How do I get the address of the top object ?
        t1 = &(q.top());
        q.pop();
        std::cout << q.top().symbol << ": " << q.top().weight << std::endl;
        t2 = &(q.top());
        t3 = { 0,
               (t1->weight + t2->weight),
               t1,
               t2
        }
    }

    // We now have a complete Huffman tree
    tree *final_tree = &(q.top());
    print_tree(final_tree, "");

    return 0;
}