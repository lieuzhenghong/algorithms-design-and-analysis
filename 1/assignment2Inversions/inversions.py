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
    # The array is either of length 3 or 2 
    for i in range(len(a)-1):
        for j in range(i, len(a)):
            if a[i] > a[j]:
                inversions +=1
    for i in range(len(a)):
        mini = min(a[i:]) #find minimum element
        min_index = a[i:].index(mini) #find index of minimum element
        if (min_index is not 0):
            #inversions +=1
            pass
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
        #print(result_a, result_b)
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
test_1 = [1,3,5,2,4,6]
test_2 = [1,5,3,2,4]
test_3 = [5,4,3,2,1]
test_4 = [1,6,3,2,4,5]
test_15 = [ 9, 12, 3, 1, 6, 8, 2, 5, 14, 13, 11, 7, 10, 4, 0 ]
test_50 = [37, 7, 2, 14, 35, 47, 10, 24, 44, 17, 34, 11, 16, 48, 1, 39, 6, 33,
43, 26, 40, 4, 28, 5, 38, 41, 42, 12, 13, 21, 29, 18, 3, 19, 0, 32, 46, 27, 31,
25, 15, 36, 20, 8, 9, 49, 22, 23, 30, 45 ]
test_100 = [ 4, 80, 70, 23, 9, 60, 68, 27, 66, 78, 12, 40, 52, 53, 44, 8, 49, 28, 18, 46, 21, 39, 51, 7, 87, 99, 69, 62, 84, 6, 79, 67, 14, 98, 83, 0, 96, 5, 82, 10, 26, 48, 3, 2, 15, 92, 11, 55, 63, 97, 43, 45, 81, 42, 95, 20, 25, 74, 24, 72, 91, 35, 86, 19, 75, 58, 71, 47, 76, 59, 64, 93, 17, 50, 56, 94, 90, 89, 32, 37, 34, 65, 1, 73, 41, 36, 57, 77, 30, 22, 13, 29, 38, 16, 88, 61, 31, 85, 33, 54 ]
start = timeit.default_timer()
print(count_inversions(read_file())[1], 'inversions')
#print(count_inversions(test_1)[1], 'inversions; expecting 3')
#print(count_inversions(test_2)[1], 'inversions; expecting 4')
#print(count_inversions(test_3)[1], 'inversions; expecting 10')
#print(count_inversions(test_4)[1], 'inversions; expecting 5')
#print(count_inversions(test_15)[1], 'inversions; expecting 56')
#print(count_inversions(test_50)[1], 'inversions; expecting 590')
#print(count_inversions(test_100)[1], 'inversions; expecting 2372')
stop = timeit.default_timer()
print ('Time taken: {0} seconds'.format(stop-start))

