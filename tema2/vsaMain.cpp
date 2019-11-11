#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include "graph.h"
using namespace std;

constexpr const char* kTest[] = {"mic.txt", "p2p-Gnutella08.txt", "email-Eu-core.txt", "facebook_combined.txt"};

set<int> notSelected;

int getDegree(int x) { return Graph::lda[x].size(); }

int getNodeVal(int x) {
  int ans = 0;
  for (int to : Graph::lda[x]) ans += getDegree(to);
  return ans;
}

pair<int, int> getFitness(int x) { return make_pair(getNodeVal(x), getDegree(x)); }

bool checkGraph() {
  for (int i = 0; i < Graph::n; ++i)
    if (Graph::lda[i].size()) return true;
  return false;
}

int main(int argc, char* argv[]) {
  if (argc != 2) return 0 * puts("argc != 2");
  cerr << "Dataset: " << kTest[argv[1][0] - '0'] << '\n';
  cerr << "Reading the graph\n";
  Graph::readGraph(string("../data/") + kTest[argv[1][0] - '0']);
  cerr << "The graph has " << Graph::n << " verices\n";

  while (checkGraph()) {
    auto mx = make_pair(-1, -1);
    int t = -1;
    for (int i = 0; i < Graph::n; ++i) {
      if (notSelected.count(i)) continue;
      auto currFit = getFitness(i);
      if (currFit < mx) continue;
      mx = currFit;
      t = i;
    }
    notSelected.insert(t);
    for (int to : Graph::lda[t]) if (t != to) Graph::lda[to].erase(t);
    Graph::lda[t].clear();
  }

  cerr << "Max independent set: " << Graph::n - notSelected.size() << '\n';
  
  return 0;
}