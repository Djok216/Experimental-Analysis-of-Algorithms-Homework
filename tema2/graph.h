#ifndef GRAPH_H__
#define GRAPH_H__
#include <bits/stdc++.h>
using namespace std;

namespace Graph {
constexpr int N = 1e5;
int n;
set<int> lda[N];

void clearGraph() {
  n = 0;
  for (int i = 0; i < N; ++i) lda[i].clear();
}

void readGraph(const string& fileName) {
  clearGraph();
  ifstream cin(fileName);
  int x, y;
  while (cin >> x >> y) {
    lda[x].insert(y);
    lda[y].insert(x);
    n = max({n, x, y});
  }
  ++n;
}

bool hasEdge(int x, int y) {
  return lda[x].find(y) != lda[x].end();
}

}; //  namespace Gaph

#endif //  GRAPH_H__
