/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

void test_sum_small_data_set();

// Add prototypes for you test functions here.
void test_summarize();
void test_count();
void test_mean();
void test_median();
void test_mode();
void test_min();
void test_max();
void test_stdev();
void test_percentile();

int main() {
  test_sum_small_data_set();
  // Call your test functions here
  test_summarize();
  test_count();
  test_mean();
  test_median();
  test_mode();
  test_min();
  test_max();
  test_stdev();
  test_percentile();
  return 0;
}

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!" << endl;
}

// Add the test function implementations here.
void test_summarize() {
  cout << "test_summarize" << endl;
  vector<double> data = {1,2,3,3,3,2,1};
  vector<pair<double,int>> re = summarize(data);
  assert(re[0].first == 1);
  assert(re[0].second == 2);
  assert(re[1].first == 2);
  assert(re[1].second == 2);
  assert(re[2].first== 3);
  assert(re[2].second == 3);
  data = {0};
  assert(summarize(data)[0].first == 0);
  assert(summarize(data)[0].second == 1);
  cout << "PASS!" << endl;
}

void test_count() {
  cout << "test_count" << endl;
  vector<double> data = {1,2,3,3,3,2,1};
  assert(count(data) == 7);

  cout << "PASS!" << endl;
}

void test_mean() {
  cout << "test_mean" << endl;
  vector<double> data = {1,2,3,2,6};
  assert(mean(data) == 2.8);
  data = {1};
  assert(mean(data) == 1);
  cout << "PASS!" << endl;
}

void test_median() {
  cout << "test_median" << endl;
  vector<double> data = {1,2,3,2,6};
  assert(median(data) == 2);
  data = {1,2,4,3};
  assert(median(data) == 2.5);
  data = {1};
  assert(median(data) == 1);
  cout << "PASS!" << endl;
}

void test_mode() {
  cout << "test_mode" << endl;
  vector<double> data = {1,2,3,2,6};
  assert(mode(data) == 2);
  data = {1};
  assert(mode(data) == 1);
  data = {3,3,2,2,1,1};
  assert(mode(data) == 1);
  cout << "PASS!" << endl;
}

void test_min() {
  cout << "test_min" << endl;
  vector<double> data = {1,2,3,2,6,1};
  assert(min(data) == 1);
  cout << "PASS!" << endl;
}

void test_max() {
  cout << "test_max" << endl;
  vector<double> data = {1,2,3,2,6,1};
  assert(max(data) == 6);
  cout << "PASS!" << endl;
}

void test_stdev() {
  cout << "test_stdev" << endl;
  const double epsilon = 0.00001;
  vector<double> data = {1,2,3,2,6,1};
  assert((abs(stdev(data) - 1.87083) < epsilon));
  cout << "PASS!" << endl;
}

void test_percentile() {
  cout << "test_percentile" << endl;
  const double epsilon = 0.00001;
  vector<double> data = {1,2,3,2,6,1,5,10,11};
  assert(abs(percentile(data, 0.4) - 2.2) < epsilon);
  assert(percentile(data, 1) == 11);
  assert(percentile(data, 0) == 1);
  cout << "PASS!" << endl;
}





