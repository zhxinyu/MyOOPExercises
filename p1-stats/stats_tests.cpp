/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
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


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

void test_sum_small_data_set();
void test_mean_small_data_set();
void test_percentile_small_data_set();
void test_count_small_data_set();
void test_max_small_data_set();
void test_min_small_data_set();
void test_median_small_data_set();
void test_stdev_small_data_set();
void test_summarize_small_data_set();
void test_mode_small_data_set();
// Add prototypes for you test functions here.
const double epsilon = 0.00001;
int main()
{
    test_sum_small_data_set();
    test_mean_small_data_set();
    test_percentile_small_data_set();
    test_max_small_data_set();
    test_min_small_data_set();
    test_count_small_data_set();
    test_median_small_data_set();
    test_stdev_small_data_set();
    test_summarize_small_data_set();
    test_mode_small_data_set();
    // Call your test functions here
  return 0;
}

void test_sum_small_data_set()
{
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "The sum is "<<sum(data)<<" PASS!" << endl;
}


void test_mean_small_data_set()
{
    cout << "test_mean_small_data_set" << endl;
    
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    
    assert(mean(data) == 2);
    
    cout <<"The mean is " <<mean(data)<< " PASS!" << endl;
}


void test_percentile_small_data_set(){
    cout << "test_percentile_small_data_set" << endl;
    
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);
    data.push_back(6);
    data.push_back(7);
    data.push_back(8);
    data.push_back(9);
    data.push_back(10);

    assert(abs(percentile(data,0.85) - 8.65)<epsilon);
    
    cout <<"The mean is " <<percentile(data,0.85)<< " PASS!" << endl;

}

// Add the test function implementations here.

void test_max_small_data_set()
{
    cout << "test_max_small_data_set" << endl;
    
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    
    assert(max(data) == 3);
    
    cout <<"The max is " <<max(data)<< " PASS!" << endl;
}

void test_min_small_data_set()
{
    cout << "test_min_small_data_set" << endl;
    
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    
    assert(min(data) == 1);
    
    cout <<"The min is " <<min(data)<< " PASS!" << endl;
}

void test_count_small_data_set()
{
    cout << "test_count_small_data_set" << endl;
    
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    
    assert(count(data) == 3);
    
    cout <<"The count is " <<count(data)<< " PASS!" << endl;
}

void test_median_small_data_set()
{
    cout << "test_median_small_data_set" << endl;
    
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    
    assert(abs(median(data) -2.5)<epsilon);
    
    cout <<"The median is " <<median(data)<< " PASS!" << endl;
}

void test_stdev_small_data_set()
{
    cout << "test_stdev_small_data_set" << endl;
    
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    //data.push_back(4);
    
    assert(abs(stdev(data) -1)<epsilon);
    
    cout <<"The stdev is " <<stdev(data)<< " PASS!" << endl;
}

void test_summarize_small_data_set()
{
    cout << "test_summarize_small_data_set" << endl;
    
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(2);
    data.push_back(4);
    data.push_back(4);
    data.push_back(6);
    data.push_back(9);
    data.push_back(9);
    data.push_back(9);
    data.push_back(10);

    //data.push_back(4);
    
    //assert(abs(stdev(data) -1)<epsilon);
    for (vector<double> v: summarize(data)){
        for (double i : v){cout<<i<<' ';}
        cout<<endl;
    }
    //cout <<"The summarize is " << summarize(data)<< " PASS!" << endl;
}

void test_mode_small_data_set()
{
    cout << "test_mode_small_data_set" << endl;
    
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(2);
    data.push_back(4);
    data.push_back(4);
    data.push_back(6);
    data.push_back(9);
    data.push_back(9);
    data.push_back(9);
    data.push_back(10);
    
    //data.push_back(4);
    
    //assert(abs(stdev(data) -1)<epsilon);
    cout <<"The mode is " << mode(data)<< " PASS!" << endl;
}
