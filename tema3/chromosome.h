#ifndef CHROMOSOME_H__
#define CHROMOSOME_H__
#include <bits/stdc++.h>
using namespace std;

struct Chromosome {
  Chromosome(int n = 0, bool genRand = false);
  Chromosome operator^(const Chromosome& other);
  void doMutation(double prob);
  typename vector<bool>::reference operator[](int i) { return data[i]; }
  vector<bool> data;
};

#endif //  CHROMOSOME_H__
