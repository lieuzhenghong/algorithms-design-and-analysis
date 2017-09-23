'''
The goal of this problem is to implement a variant of the 2-SUM algorithm
(covered in the Week 6 lecture on hash table applications).

The file contains 1 million integers, both positive and negative (there might
be some repetitions!).This is your array of integers, with the ith row of the
file specifying the ith entry of the array.

Your task is to compute the number of target values t in the interval
[-10000,10000] (inclusive) such that there are distinct numbers x,y in the
input file that satisfy x+y=t. (NOTE: ensuring distinctness requires a one-line
addition to the algorithm from lecture.)

Write your numeric answer (an integer between 0 and 20001) in the space
provided.

OPTIONAL CHALLENGE: If this problem is too easy for you, try implementing your
own hash table for it. For example, you could compare performance under the
chaining and open addressing approaches to resolving collisions.
'''
'''
Algorithm as follows:

Put in all the 1 million integers into a hashtable

To find the 2-SUM of a number [-10000, 10000]:

Iterate through all the integers in the hashtable one by one.
Find its complement (if its complement is itself, reject)

If found, break and return True.
If not found, return False.
'''
import argparse
import time

numbers = []
ht = {}

def read_file(file_name):
    with open(file_name, 'r') as f:
        for line in f:
            numbers.append(int(line.strip()))
            ht[line.strip()] = int(line.strip())
    numbers.sort()
    #print(numbers)
    #print(ht)


def is_there_sum(target, number):
    if (target-number == number):
        print(number, target-number, "Number is target")
        return False
    if str(target-number) in ht:
        print(number, target-number, "Found a match: ", target)
        return True
    else:
        #print(number, target-number, "No match for: ", target)
        return False

parser = argparse.ArgumentParser(description="Computes 2SUM for [-10000,10000] given a file of integers")
parser.add_argument('filename', help='filename of list of integers')
args = parser.parse_args()

'''
if __name__ == "__main__":
    read_file(args.filename)
    matches = 0
    matches_list = []
    
    t0 = time.time()
    for target in range(-10000, 10001):
        t1 = time.time()
        for number in numbers:
            if (is_there_sum(target, number)):
                matches += 1
                matches_list.append((target, target-number, number))
                break
            else:
                pass
        t2 = time.time()
        print("time taken for this iteration of", target, t2-t1)
    t3 = time.time()
    print("Number of matches: {}".format(matches))
    print(matches_list)
    print("total time taken:", t3-t0)
'''


if __name__ == "__main__":
    read_file(args.filename)
    MIN = -10000
    MAX = 10000
    left = 0
    right = -1
    sums = [False] * 20001
    s = numbers[left] + numbers[right]

    t0 = time.time()
    for i in range(len(numbers)):
        t1 = time.time()
        l = left
        r = right
        if (s < MIN):
            while (s < MAX):
                l += 1
                if (l == r):
                    break
                s = numbers[l] + numbers[r]
                if (s >= MIN and s <= MAX):
                    sums[s+10000] = True
            # While loop finishes; reset left pointer 
            left = left+1
        elif (s > MAX):
            while (s > MIN):
                r -= 1
                if (l == r):
                    break
                s = numbers[l] + numbers[r]
                if (s > MIN and s < MAX):
                    sums[s+10000] = True
            right = right - 1
        else:
            while ((s >= MIN) and (s <= MAX)):
                l += 1
                if (l == r):
                    break
                s = numbers[l] + numbers[r]
                sums[s+10000] = True
        t2 = time.time()
        print("time taken for this iteration of", i+1, t2-t1)
    t3 = time.time()
    print("Number of matches: {}".format(sum(sums)))
    print("total time taken:", t3-t0)
