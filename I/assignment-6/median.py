'''
The goal of this problem is to implement the "Median Maintenance" algorithm
(covered in the Week 5 lecture on heap applications). The text file contains
a list of the integers from 1 to 10000 in unsorted order; you should treat
this as a stream of numbers, arriving one by one. Letting xi denote the ith
number of the file, the kth median mk is defined as the median of the
numbers x1,…,xk. (So, if k is odd, then mk is ((k+1)/2)th smallest number
among x1,…,xk; if k is even, then mk is the (k/2)th smallest number among
x1,…,xk.)

In the box below you should type the sum of these 10000 medians, modulo
10000 (i.e., only the last 4 digits). That is, you should compute
(m1+m2+m3+⋯+m10000)mod10000.

OPTIONAL EXERCISE: Compare the performance achieved by heap-based and
search-tree-based implementations of the algorithm. 
'''

'''
Here's how we do median maintenance:

Keep two heaps, hiheap and loheap. hiheap supports Extract-Min and loheap
supports Extract-Max.

They also support insertion.

Heaps will be 1-indexed; the 0th value is not used.
'''
import argparse
import math

def read_file(file_name):
    istream = []
    with open(file_name, 'r') as f:
        for line in f:
            istream.append(int(line.strip()))
    return istream

def insert(heap, e, flag="min"):
    heap.append(e)
    # Bubble-up propagation
    heap = bubble_up(heap, flag)
    return heap


def bubble_up(heap, flag="min"):
    pos = len(heap) - 1

    while (pos > 1):
        swap_pos = pos // 2
        #print(heap, pos, swap_pos)
        if (flag == "min" and heap[swap_pos] > heap[pos]):
            (heap[swap_pos], heap[pos]) = (heap[pos], heap[swap_pos])
        elif (flag == "max" and heap[swap_pos] < heap[pos]):
            (heap[swap_pos], heap[pos]) = (heap[pos], heap[swap_pos])
        pos = swap_pos
    return heap

def bubble_down(heap, index, flag="min"):
    pos = index
    left = index * 2
    right = (index * 2) + 1

    if (flag == "max"):
        if (left < len(heap) and heap[left] > heap[pos]):
            pos = left 
        if (right < len(heap) and heap[right] > heap[pos]):
            pos = right 
    if (flag == "min"):
        if (left < len(heap) and heap[left] < heap[pos]):
            pos = left 
        if (right < len(heap) and heap[right] < heap[pos]):
            pos = right 

    if (index != pos):
        (heap[pos], heap[index]) = heap[index], heap[pos]
        bubble_down(heap, pos, flag)

    return heap

'''
def bubble_down(heap, flag="min"):
    pos = 1

    # Length of heap is +1, don't forget
    if (len(heap) == 3):
        if (flag == "max" and heap[pos] >= heap[pos*2]):
            return heap
        elif (flag == "min" and heap[pos] <= heap[pos*2]):
            return heap
        else:
            (self, child) = heap[pos], heap[pos*2]
            if (flag == "min" and self > child):
                (heap[pos], heap[pos*2]) = child, self
            elif (flag == "max" and self < child):
                (heap[pos], heap[pos*2]) = child, self
        return heap

    while ((pos * 2 + 1) <= len(heap)):
        a = pos * 2
        b = pos * 2 + 1
        if (b == len(heap)): #only one child
            (self, c) = heap[pos], heap[a]
            print(flag, self, c)
            if (flag == "min" and self <= c):
                return heap
            elif (flag == "max" and self >= c):
                return heap
            if (flag == "min" and self > c):
                heap[pos], heap[a] = c, self
                print(heap[pos], heap[a])
                pos = a
            if (flag == "max" and self < c):
                heap[pos], heap[a] = c, self
                print(heap[pos], heap[a])
                pos = a
        else:
            (self, l, r) = heap[pos], heap[a], heap[b]
            if (flag == "max" and self >= l and self >= r):
                return heap
            elif (flag == "min" and self <= l and self <= r):
                return heap
            else:
                if (flag == "min"):
                    if (l < r):
                        heap[pos], heap[a] = l, self
                        pos = a
                    else:
                        heap[pos], heap[b] = r, self
                        pos = b
                elif (flag == "max"):
                    if (l < r):
                        heap[pos], heap[b] = r, self
                        pos = b
                    else:
                        heap[pos], heap[a] = l, self
                        pos = a

    return heap
'''

    
def extract(heap, flag="min"):
    val = heap[1]
    heap[1] = heap[-1]
    heap = heap[:-1]
    heap[0] = 0
    heap = bubble_down(heap, 1, flag)
    return (heap, val)

def get_top(heap):
    return heap[1]

def rebalance(h1, h2):
    if (len(h1) > len(h2)+1):

        [h1, val] = extract(h1, "max")
        h2 = insert(h2, val)
    elif (len(h2) > len(h1)+1):
        [h2, val] = extract(h2)
        h1 = insert(h1, val, "max")
    else:
        pass
    return (h1, h2)

def maintain_median(istream):
    hiheap = [0]
    loheap = [0]
    mstream = []
    for idx, i in enumerate(istream):
        if len(hiheap) == 1:
            hiheap = insert(hiheap, i)
        elif i < get_top(hiheap):
            loheap = insert(loheap, i, "max")
        else:
            hiheap = insert(hiheap, i)

        #print(loheap, hiheap)
        (loheap, hiheap) = rebalance(loheap, hiheap)
        m = math.ceil((idx+1)/2)
        #print(loheap, hiheap, m)
        # Remember that the length of these arrays is 1 more than they
        # actually are. A heap with len 7 has only 6 elements
        if (m > len(loheap)-1):
            mstream.append(get_top(hiheap))
        else:
            mstream.append(get_top(loheap))
        #print(mstream[-1])
    return mstream    

parser = argparse.ArgumentParser(description="Computes sum of median given filename")
parser.add_argument('filename', help='file name of list of integers')
args = parser.parse_args()

if __name__ == "__main__":
    #print((maintain_median(read_file(args.filename))))
    print(sum(maintain_median(read_file(args.filename))))

