#include "chromosome.h"

Chromosome::Chromosome(int len, bool genRand) {
  data.resize(len);
  if (genRand) {
    for (int i = 0; i < len; ++i) 
      data[i] = rand() & 4;
  }
}

void Chromosome::doMutation(double prob) {
  constexpr int kMxRand = 3e4;
  if (rand() % kMxRand > prob * kMxRand) return;
  int pos = rand() % data.size();
  data[pos] = 1 - data[pos];
}

Chromosome Chromosome::operator^(const Chromosome& other) {
  Chromosome ans = other;
  for (int i = 0; i < static_cast<int>(ans.data.size()); ++i) {
    if (rand() & 1) ans[i] = data[i];
  }
  return ans;
}