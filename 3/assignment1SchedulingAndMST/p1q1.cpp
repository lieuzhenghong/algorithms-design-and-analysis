/**
This file describes a set of jobs with positive and integral weights and
lengths. It has the format

[number_of_jobs]

[job_1_weight] [job_1_length]

[job_2_weight] [job_2_length]

...

For example, the third line of the file is "74 59", indicating that the second
job has weight 74 and length 59.

You should NOT assume that edge weights or lengths are distinct.

Your task in this problem is to run the greedy algorithm that schedules jobs in
decreasing order of the difference (weight - length).

Recall from lecture that this algorithm is not always optimal. IMPORTANT: if
two jobs have equal difference (weight - length), you should schedule the job
with higher weight first. Beware: if you break ties in a different way, you are
likely to get the wrong answer. You should report the sum of weighted
completion times of the resulting schedule --- a positive integer --- in the
box below.
*/

// For IO function
#include <iostream>
// For sorting function
#include <algorithm>

// For converting string into array
#include <sstream>
#include <string>
#include <array>

using namespace std;

// For easier sorting, I create a struct
struct Job
{
  double score;
  int weight;
  int length;
};

int num_jobs;
int counter = 0;
// these should probably be dynamically resizable as well
// But in a CP context, where input size is known, we can probably
// get away with just using the upper bound for fixed array
int weights[20000];
int lengths[20000];
string input_line;
int input_array[2];
array<Job, 20000> jobs;

// Sum function to determine weighted completion time
long long int weighted_completion_time(const array<Job, 20000> &jobs) {
  Job job;
  long long int completion_time = 0;
  int time_elapsed = 0;

  for (int i = 0; i < num_jobs; i++) {
    job = jobs[i];
    time_elapsed += job.length;
    completion_time = (completion_time + (job.weight * time_elapsed));
  }

  return completion_time;
}

int main() {
  cin >> num_jobs;
 
  for (int i = 0; i < num_jobs; i++) {

    cin >> weights[counter] >> lengths[counter];
    double score = double(weights[i])/lengths[i]; // cast to double
    //int score = weights[i] - lengths[i];
    int weight = weights[i];
    int length = lengths[i];
    Job job;

    job.score = score;
    job.weight = weight;
    job.length = length;

    jobs[i] = job;
    //cout << jobs[i].score << " " << jobs[i].weight << " " << jobs[i].length << endl;
    counter++;
  }

  cout << "Weighted completion time before sorting: " <<
    weighted_completion_time(jobs) << endl;

  sort(begin(jobs), (begin(jobs)+num_jobs), [](const Job &a, const Job &b) {
    if (a.score == b.score) return a.weight > b.weight;
    return a.score > b.score;
  });


  // Display again
  for (int i = 0; i < num_jobs; i++) {
    cout << jobs[i].score << " " << jobs[i].weight << " " << jobs[i].length << endl; 
  }

  cout << "Weighted completion time: " <<  weighted_completion_time(jobs) << endl;
  
  return weighted_completion_time(jobs);
}
