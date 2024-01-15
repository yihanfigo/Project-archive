// stats.cpp
#include "stats.hpp"
#include "p1_library.hpp"
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

vector<pair<double, int> > summarize(vector<double> v) {
    sort(v);
    int count = 0;
    double temp = v[0];
    vector<pair<double, int>> vp;
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == temp) {
            count ++;
        } else {
            vp.push_back({temp,count});
            temp = v[i];
            count = 1;
        }
    }
    vp.push_back({temp, count});
    return vp;
}

int count(vector<double> v) {
  return v.size();
}

double sum(vector<double> v) {
  double sum = 0;
  for (size_t i = 0; i < v.size(); i++) {
    sum = sum + v[i];
  }
  return sum;
}

double mean(vector<double> v) {
  double mean = sum(v)/v.size();
  return mean;
}

double median(vector<double> v) {
  sort(v);
  double median = 0;
  int index = 0;
  if (v.size()%2 == 0) {
    index = v.size()/2;
    median = (v[index] + v[index-1])/2;
  } else {
    index = v.size()/2;
    median = v[index];
  }
  return median;
}

double mode(vector<double> v) {
  sort(v);
  double mode = v[0];
  int count = 0;
  int maxcount = 0;
  double temp = v[0];
  for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == temp) {
            count ++;
        } else {
            if (count > maxcount) {
                maxcount = count;
                mode = temp;
            }
            count = 1;
            temp = v[i];
        }
    }
  if (count > maxcount) {
    maxcount = count;
    mode = temp;
   }
   return mode;
}

double min(vector<double> v) {
  sort(v);
  return v[0];
}

double max(vector<double> v) {
  sort(v);
  return v[v.size()-1];
}

double stdev(vector<double> v) {
  double m = mean(v);
  double var = 0;
  for (size_t i = 0; i < v.size(); i++) {
    var = var + (v[i]-m)*(v[i]-m);
  }
  double sd = sqrt(var/(v.size()-1));
  return sd;
}

double percentile(vector<double> v, double p) {
  sort(v);
  if (p == 1) {
    return max(v);
  }
  double n = p * (v.size()-1) + 1;
  double fractpart = 0;
  double intpart = 0;
  fractpart = modf(n , &intpart);
  double per = v[intpart-1] + fractpart*(v[intpart]-v[intpart-1]);
  return per;
}
