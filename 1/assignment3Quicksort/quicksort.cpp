// Quicksort algorithm
// Takes in a list and a pivot index and returns a partitioned list
//
/*
The file contains all of the integers between 1 and 10,000 (inclusive, with
no repeats) in unsorted order. The integer in the _i<sup>th</sup>_ row of the
file gives you the _i<sup>th</sup>_ entry of an input array.
Your task is to compute the total number of comparisons used to sort the
given input file by QuickSort. As you know, the number of comparisons depends
on which elements are chosen as pivots, so we'll ask you to explore three
different pivoting rules.

You should not count comparisons one-by-one. Rather, when there is a
recursive call on a subarray of length _`m`_, you should simply add <span
style="white-space:nowrap">_m-1_</span> to your running total of comparisons.
(This is because the pivot element is compared to each of the other <span
style="white-space:nowrap">_m-1_</span> elements in the subarray in this
recursive call.)

WARNING: The Partition subroutine can be implemented in several different
ways, and different implementations can give you differing numbers of
comparisons. For this problem, you should implement the Partition subroutine
_exactly_ as it is described in the video lectures (otherwise you might get
the wrong answer).

1. For the first part of the programming assignment, you should always use
the first element of the array as the pivot element.

2. Compute the number of comparisons (as in Problem 1), always using the
final element of the given array as the pivot element. Again, be sure to
implement the Partition subroutine _exactly_ as it is described in the video
lectures.

Recall from the lectures that, just before the main Partition subroutine, you
should exchange the pivot element (i.e., the last element) with the first
element.

3. Compute the number of comparisons (as in Problem 1), using the
"median-of-three" pivot rule. [The primary motivation behind this rule is to
do a little bit of extra work to get much better performance on input arrays
that are nearly sorted or reverse sorted.] In more detail, you should choose
the pivot as follows. Consider the first, middle, and final elements of the
given array. (If the array has odd length it should be clear what the
"middle" element is; for an array with even length _2k_, use the
_k<sup>th</sup>_ element as the "middle" element. So for the array 4 5 6 7,
the "middle" element is the second one ---- 5 and not 6!) Identify which of
these three elements is the median (i.e., the one whose value is in between
the other two), and use this as your pivot. As discussed in the first and
second parts of this programming assignment, be sure to implement Partition
exactly as described in the video lectures (including exchanging the pivot
element with the first element just before the main Partition subroutine).

EXAMPLE: For the input array 8 2 4 5 7 1 you would consider the first (8),
middle (4), and last (1) elements; since 4 is the median of the set {1,4,8},
you would use 4 as your pivot element.

SUBTLE POINT: A careful analysis would keep track of the comparisons made in
identifying the median of the three candidate elements. You should NOT do
this. That is, as in the previous two problems, you should simply add _m−1_
to your running total of comparisons every time you recurse on a subarray
with length _m_.
*/

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using std::array;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int comparisons;
const int ARR_SIZE = 10000;
typedef array<int, ARR_SIZE> list;
list xs = {0};
list ys = {0};

void read_input()
{
  int n;
  int counter = 0;
  while (cin >> n)
  {
    xs[counter] = n;
    ys[counter] = n;
    counter++;
  }
}

void swap(int a, int b)
{
  int tmp;
  tmp = xs[a];
  xs[a] = xs[b];
  xs[b] = tmp;
}

void swap_pivot(int start, int end, int p)
{
  if (p == 0)
  {
  }
  else if (p == 1)
  {
    swap(start, end - 1);
  }
  else
  {
    // choose median of 3
    array<int, 3> a;
    int first = xs[start];
    int med = ((end - start) % 2) ? start + (end - start) / 2 : start + (end - start) / 2 - 1;
    int last = xs[end - 1];
    /*
    cout << first << " "
         << "(med: " << med << " ) " << xs[med] << " " << last << endl;
         */
    // then we swap
    if (first < xs[med] && first < last)
    {
      if (xs[med] < last)
        swap(start, med);
      else
        swap(start, end - 1);
    }
    else if (first > xs[med] && first > last)
    {
      if (xs[med] > last)
        swap(start, med);
      else
        swap(start, end - 1);
    }
  }
}

// Returns the pivot element. Guaranteed that elements from start to pivot are smaller than pivot, elements
// from pivot+1 to end are larger than pivot
int partition(int start, int end, int p)
{
  swap_pivot(start, end, p);
  int i = start;
  for (int j = start + 1; j < end; ++j)
  {
    if (xs[j] > xs[start])
    {
      continue;
    }
    else // No duplicates
    {
      // Swap this smaller element with the leftmost element after the pivot
      // Then increment pivot
      swap(i + 1, j);
      ++i;
    }
  }
  // Finally, put the pivot where it's supposed to be
  swap(start, i);
  return i;
}

auto qs(int start, int end, int p)
{
  /*
  cout << "Currently sorting the following array: [ ";
  for (int i = start; i < end; i++)
  {
    cout << xs[i] << ", ";
  }
  cout << "]" << endl;

  //cout << "My start: " << start << " My end: " << end << endl;
  */

  if (end - start <= 1)
  {
    return 0;
  }
  else
  {
    comparisons += end - start - 1;
    //cout << "Comparisons: " << comparisons << endl;
    int pivot = partition(start, end, p);
    /*
    cout << "Array is now: [ ";
    for (int i = start; i < end; i++)
    {
      cout << xs[i] << ", ";
    }
    cout << "]" << endl;
    */
    qs(start, pivot, p);
    qs(pivot + 1, end, p);
  }
  return 0;
}

int main()
{
  read_input();
  // Run quicksort once with first pivot, once with last pivot, one with median of three pivot
  qs(0, ARR_SIZE, 0);
  std::cout << "Comparisons: " << comparisons << std::endl
            << endl;
  comparisons = 0;
  // Reset the list
  xs = ys;
  qs(0, ARR_SIZE, 1);
  std::cout << "Comparisons: " << comparisons << std::endl
            << endl;
  comparisons = 0;
  xs = ys;
  qs(0, ARR_SIZE, 2);
  std::cout << "Comparisons: " << comparisons << std::endl
            << endl;
  return 0;
}
