# Quicksort algorithm
# Takes in a list and a pivot index and returns a partitioned list
comparisons = 0

def read_file(filename):
    with open(filename) as text_file:
        numbers = text_file.read().splitlines()
        num_array = []
        for number in numbers:
            number = int(number)
            num_array.append(number)
        text_file.close()
        return num_array

def quicksort(a, pivot_idx, median=False):
    # Base case
    if len(a) <= 1:
        return a
    else:
        # This rather ugly code block basically implements the median
        # functionality
        # Compares three elements: first, middle and last, and gets the median
        # element of the three
        if median is True:
            if (len(a) % 2 == 0):
                idx = len(a) / 2
            else:
                idx = (len(a) // 2) + 1
            idx = int(idx)
            mid_ele = a[idx]
            first_ele = a[0]
            last_ele = a[-1]
            temp_a = [first_ele, mid_ele, last_ele]
            temp_b = [0, idx, -1]
            temp_c = sorted(set(temp_a))
            pivot_idx = temp_b[temp_a.index(temp_c[1])]

        p = partition(a, pivot_idx);
        # p[0] is the sorted array; we update its state 
        # p[1] is the pivot index; the element that was used as the pivot in
        # the partition function
        a = p[0]
        pivot = p[1]
        # Make recursive quicksort calls on two arrays, making sure not to
        # include the pivot element
        a[:pivot] = quicksort(a[:pivot], pivot_idx, median)
        a[pivot+1:] = quicksort(a[pivot+1:], pivot_idx, median)
    return a

def partition(a, pivot_idx):
    # Move the pivot to the first element
    temp = a[0]
    a[0] = a[pivot_idx]
    a[pivot_idx] = temp
    pivot_element = a[0]

    # Initialise the partition point at 1, to the right of the pivot
    partition_point = 1
    global comparisons
    comparisons+=max(len(a)-1, 0)
    #print(a, comparisons, max(len(a)-1,0))
    # Iterate over the list, swapping if necessary
    #print(a, pivot_idx)
    for seen_array in range(1,len(a)):
        if (a[seen_array] < pivot_element):
            # Swap positions of seen_array and partition_point element
            temp = a[partition_point]
            a[partition_point] = a[seen_array]
            a[seen_array] = temp
            # Increment partition_point
            partition_point+=1;
        else:
            pass
    # Swap the pivot element into the correct position
    #print(a, partition_point)
    temp = a[partition_point-1]
    a[partition_point-1] = pivot_element
    a[0] = temp
    #print('sorted:', a, partition_point-1, pivot_element)
    return (a, partition_point-1)
                
print(quicksort(read_file('QuickSort.txt')[:10], 0))
print('comparisons: {}, expected {}'.format(comparisons, 25))
comparisons=0
print(quicksort(read_file('QuickSort.txt')[:10], -1))
print('comparisons: {}, expected {}'.format(comparisons, 29))
comparisons=0
print(quicksort(read_file('QuickSort.txt')[:10], 1, True))
print('comparisons: {}, expected {}'.format(comparisons, 21))
comparisons=0
quicksort(read_file('QuickSort.txt')[:100], 0)
print('comparisons: {}, expected {}'.format(comparisons, 615))
comparisons=0
quicksort(read_file('QuickSort.txt')[:100], -1)
print('comparisons: {}, expected {}'.format(comparisons, 587))
comparisons=0
quicksort(read_file('QuickSort.txt')[:100], 1, True)
print('comparisons: {}, expected {}'.format(comparisons, 518))
comparisons=0

'''
> python3 quicksort.py 
    [504, 609, 2148, 3153, 5469, 6324, 7017, 7628, 7742, 9058]
    comparisons: 25, expected 25
    [504, 609, 2148, 3153, 5469, 6324, 7017, 7628, 7742, 9058]
    comparisons: 31, expected 29
    [504, 609, 2148, 3153, 5469, 6324, 7017, 7628, 7742, 9058]
    comparisons: 24, expected 21
    comparisons: 620, expected 615
    comparisons: 573, expected 587
    comparisons: 540, expected 518
'''
