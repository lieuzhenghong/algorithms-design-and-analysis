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

def quicksort(a, s="f"):
    if (len(a) <= 1):
        return a
    else:
        p = choose_pivot(a, s)
        e = a[p]
        partition(a, p, (len(a)-1))
        pivot = a.index(e)
        quicksort(a[:pivot], s)
        quicksort(a[pivot+1:], s)
        return a

def choose_pivot(a, s="f"):
    if (s == "m"):
        if (len(a) % 2 == 0):
            idx = len(a) / 2
        else:
            idx = (len(a) // 2) + 1
        idx = int(idx)
        mid_ele = a[idx]
        first_ele = a[0]
        last_ele = a[-1]
        temp_a = [first_ele, mid_ele, last_ele]
        temp_b = [0, idx, len(a)-1]
        temp_c = sorted(set(temp_a))
        pivot_idx = temp_b[temp_a.index(temp_c[1])]
        return pivot_idx
    elif (s == "f"):
        return 0
    else:
        return (len(a)-1)

def partition(a, left, right):
    global comparisons
    comparisons += right
    pivot = left
    i = left+1
    for j in range(left+1, right+1):
        if a[j] < a[pivot]:
            (a[i], a[j]) = (a[j], a[i])
            i += 1
        #print(a)
    a[i-1], a[pivot] = a[pivot], a[i-1] 
   # print(a)

a = [3,8,2,5,1,4,7,6]
partition(a, 0, len(a)-1)
print(a)
print(comparisons)
comparisons=0
print(quicksort(read_file('QuickSort.txt')[:10]))
print('comparisons: {}, expected {}'.format(comparisons, 25))
comparisons=0
print(quicksort(read_file('QuickSort.txt')[:10], "l"))
print('comparisons: {}, expected {}'.format(comparisons, 29))
comparisons=0
print(quicksort(read_file('QuickSort.txt')[:10], "m"))
print('comparisons: {}, expected {}'.format(comparisons, 21))
comparisons=0
quicksort(read_file('QuickSort.txt')[:100])
print('comparisons: {}, expected {}'.format(comparisons, 615))
comparisons=0
quicksort(read_file('QuickSort.txt')[:100], "l")
print('comparisons: {}, expected {}'.format(comparisons, 587))
comparisons=0
quicksort(read_file('QuickSort.txt')[:100], "m")
print('comparisons: {}, expected {}'.format(comparisons, 518))
comparisons=0
