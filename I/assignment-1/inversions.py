import timeit
'''
Divide the array into two and sort it
Every time we sort a subarray, we know it's an inversion, so add 1 to the
inversion count
Every time we merge two subarrays together, we add the inversions as follows
Whenever we add an element from a, do nothing
Whenever we add an element from b, it's an inversion. Count the number of
elements left in a and add it to the inversion count
'''
def read_file():
    with open("IntegerArray.txt") as text_file:
        numbers = text_file.read().splitlines()
        num_array = []
        for number in numbers:
            number = int(number)
            num_array.append(number)
        text_file.close()
        return num_array

def sort_array(a):
    inversions = 0
    for i in range(len(a)):
        mini = min(a[i:]) #find minimum element
        min_index = a[i:].index(mini) #find index of minimum element
        if (min_index is not 0):
            inversions += 1
        a[i + min_index] = a[i] #replace element at min_index with first element
        a[i] = mini                  #replace first element with min element
    return (a, inversions)

def count_inversions(array):
    inversions = 0;
    sorted_array = []
    # Base case
    if len(array) <= 3: #For small arrays, we simply sort
        inversions += sort_array(array)[1]
        sorted_array = sort_array(array)[0]
    #Split the array in two and call count_inversions on each, then merge and count again
    else:
        a = array[:len(array)//2]
        b = array[len(array)//2:]
        result_a = count_inversions(a)
        result_b = count_inversions(b)
        s_a = result_a[0]
        s_b = result_b[0]
        inversions += result_a[1]
        inversions += result_b[1]
        pointer_a = 0
        pointer_b = 0
        for i in range(len(s_a) + len(s_b)):
            if (pointer_a >= len(s_a)):
                if (pointer_b >= len(s_b)):
                    break
                else:
                    sorted_array.append(s_b[pointer_b]);
                    pointer_b += 1
                    continue
            if (pointer_b >= len(s_b)):
                if (pointer_a >= len(s_a)):
                    break
                else:
                    sorted_array.append(s_a[pointer_a]);
                    pointer_a += 1
                    continue
            if s_a[pointer_a] < s_b[pointer_b]:
                sorted_array.append(s_a[pointer_a])
                pointer_a += 1
            else: # The numbers are distinct so there are no ties
                sorted_array.append(s_b[pointer_b]);
                pointer_b += 1
                inversions += len(s_a[pointer_a:]) # Remaining elements in s_a
    return (sorted_array, inversions)

start = timeit.default_timer()
print(count_inversions(read_file())[1], 'inversions')
stop = timeit.default_timer()
print ('Time taken: {0} seconds'.format(stop-start))
