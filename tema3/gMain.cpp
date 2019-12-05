#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include "chromosome.h"
#include "graph.h"
using namespace std;

constexpr int kPopSize = 40;
constexpr int kGenNumber = 20;
constexpr int kElitePop = 8;
constexpr int kNewBorns = 2 * kPopSize;
constexpr double kMutProb = 0.1;
constexpr const char* kTest[] = {"mic.txt", "p2p-Gnutella08.txt", "email-Eu-core.txt", "facebook_combined.txt"};

vector<Chromosome> pop;
double bestVal = 1e9;
Chromosome bestChrom;

void clearPopulation(bool resetAll = false) {
  if (resetAll) {
    bestVal = 1e9;
    bestChrom.data.clear();
  }
  pop.clear();
}

void processChrom(Chromosome& x) {
  int n = Graph::n;
  vector<set<int>> lda(n);
  for (int i = 0; i < n; ++i) lda[i] = Graph::lda[i];

  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    if (cnt >= n * 0.1) x[i] = 0;
    if (!x[i]) continue;
    for (int to : lda[i]) if (i != to) lda[to].erase(i);
    lda[i].clear();
    ++cnt;
  }
  
  auto checkGraph = [&]() -> bool {
    for (int i = 0; i < n; ++i)
      if (lda[i].size()) return true;
    return false;
  };

  auto getDegree = [&](int x) -> int { return lda[x].size(); };
  
  auto getNodeVal = [&](int x) -> int {
    int ans = 0;
    for (int to : lda[x]) ans += getDegree(to);
    return ans;
  };

  auto getFitness = [&](int x) -> pair<int, int> { return make_pair(getNodeVal(x), getDegree(x)); };

  while (checkGraph()) {
    auto mx = make_pair(-1, -1);
    int t = -1;
    for (int i = 0; i < n; ++i) {
      if (x[i]) continue;
      auto currFit = getFitness(i);
      if (currFit < mx) continue;
      mx = currFit;
      t = i;
    }
    x[t] = 1;
    for (int to : lda[t]) if (t != to) lda[to].erase(t);
    lda[t].clear();
  }
}

double eval(Chromosome& x) {
  double ans = 0;
  for (int i = 0; i < static_cast<int>(x.data.size()); ++i)
    if (x[i]) ++ans;
  return ans;
}

bool updateBest(Chromosome& x) {
  double val = eval(x);
  if (val >= bestVal) return false;
  bestVal = val;
  bestChrom = x;
  return true;
}

void genPopulation() {
  clearPopulation();
  for (int i = 0; i < kPopSize; ++i) {
    pop.emplace_back(Chromosome(Graph::n, true));
    processChrom(pop.back());
    updateBest(pop.back());
  }
}

void multiplicationStep() {
  for (int newBorn = 0; newBorn < kNewBorns; ++newBorn) {
    int x = rand() % pop.size();
    int y = rand() % pop.size();
    pop.push_back(pop[x] ^ pop[y]);
    pop.back().doMutation(kMutProb);
    processChrom(pop.back());
    if (updateBest(pop.back())) cerr << "new best: " << bestVal << '\n';
  }
}

void selectionStep() {
  vector<pair<double, int>> pp;
  int index = 0;
  for (auto& it : pop) pp.emplace_back(eval(it), index++);
  sort(pp.begin(), pp.end());

  double sum = 0;
  vector<Chromosome> selected;
  for (int i = 0; i < static_cast<int>(pop.size()); ++i) {
    if (i < kElitePop) selected.push_back(pop[pp[i].second]);
    else sum += pp[i].first;
  }
  while (static_cast<int>(selected.size()) < kPopSize) {
    double randVal = (rand() / RAND_MAX) * sum;
    for (int i = kElitePop; i < static_cast<int>(pop.size()); ++i) {
      randVal -= pp[i].first;
      if (randVal <= 0) {
        selected.push_back(pop[pp[i].second]);
      }
    }
  }
  pop = selected;
}

int main(int argc, char* argv[]) {
  srand(time(0));
  if (argc != 2) return 0 * puts("argc != 2");
  cerr << "Dataset: " << kTest[argv[1][0] - '0'] << '\n';
  cerr << "Reading the graph\n";
  Graph::readGraph(string("../data/") + kTest[argv[1][0] - '0']);
  cerr << "The graph has " << Graph::n << " verices\n";
  cerr << "Started the Solver\n";
  while (static_cast<double>(clock()) / CLOCKS_PER_SEC <= 10) {
    cerr << "First Pop Gen\n";
    genPopulation();
    cerr << "Finished with First Pop\n";
    for (int gen = 0; gen < kGenNumber; ++gen) {
      cerr << "Gen: " << gen << " / " << kGenNumber << '\n';
      multiplicationStep();
      cerr << "Between Multiplication Step and Selection Step\n";
      selectionStep();
    }
  }
  cout << "Max Independent Set: " << static_cast<int>(Graph::n - bestVal) << '\n';
  return 0;
}