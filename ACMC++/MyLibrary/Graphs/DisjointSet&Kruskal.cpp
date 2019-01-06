#include <bits/stdc++.h>

using namespace std;

struct disjointSet {
    vector<int> par, size, rank;
    int numSet;
    disjointSet(int n) {
      par.resize(n), size.resize(n), rank.resize(n);
      for (int i = 0; i < n; ++i)
        par[i] = i, size[i] = 1;
      numSet = n;
    }

    int find(int node) {
      return par[node] = (par[node] == node) ? node : find(par[node]);
    }

    bool join(int x, int y) {
      x = find(x), y = find(y);
      if (x == y)
        return 0;
      if (rank[x] < rank[y])
        swap(x, y);
      if (rank[x] == rank[y])
        rank[x]++;
      size[x] += size[y], numSet--, par[y] = x;
      return 1;
    }
};

const int N = 10001;
int n, m;
vector<pair<int, pair<int, int> > > edges;
int kruskal() {
  double ret = 0;
  disjointSet ds(n);
  sort(edges.begin(), edges.end());
  for (int i = 0; i < m; ++i)
    if (ds.join(edges[i].second.first, edges[i].second.second))
      ret += edges[i].first;
  return ret;
}

void input() {
  int x, y, c;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    cin >> x >> y >> c, --x, --y;
    edges.push_back(make_pair(c, make_pair(x, y)));
  }
}
