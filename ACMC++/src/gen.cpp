//#include "bits/stdc++.h"
//#include "testlib.h"
//
//using namespace std;
//
//void fastInOut();
//
//const int N = 200000, M = 300000, Q = 100000;
//int dfs_low[N], dfs_num[N], articulation_vertex[N], dfs_time;
//int rem[N], rr[N];
//vector<pair<int, int> > es;
//set<int> adj[N];
//
//void articulationPointAndBridge(int u, int p, int dfs_root) {
//  dfs_low[u] = dfs_num[u] = dfs_time++;
//  int root_children = 0;
//  for (int v : adj[u]) {
//    if (dfs_num[v] == -1) {
//      if (u == dfs_root)
//        root_children++;
//      articulationPointAndBridge(v, u, dfs_root);
//      if (u != dfs_root && dfs_low[v] >= dfs_num[u])
//        articulation_vertex[u] = 1;
//      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
//    } else if (v != p)
//      dfs_low[u] = min(dfs_low[u], dfs_num[v]);
//  }
//  if (u == dfs_root && root_children > 1)
//    articulation_vertex[u] = 1;
//}
//
//int main(int argc, char* argv[]) {
//  registerGen(argc, argv, 1);
//  freopen("input.txt", "wt", stdout);
//  fastInOut();
//  int n = N, m = M;
//  int mxR = n;
//  vector<int> all;
//  for (int i = 1; i <= mxR; ++i)
//    all.push_back(i);
//  shuffle(all.begin(), all.end());
//  for (int i = 0; i < n; ++i)
//    rr[i] = all[i];
//  for (int u = 1; u < n; ++u) {
//    int v;
//    do {
//      v = rnd.next(0, u - 1);
//    } while (rem[v] == 3);
//    adj[u].insert(v), adj[v].insert(u);
//    ++rem[u], ++rem[v], --m;
//    es.push_back(make_pair(u, v));
//  }
//  vector<int> as, bs;
//  int cnt = 0;
//  for (int u = 0; u < n; ++u) {
//    if (rem[u] < 3)
//      as.push_back(u), bs.push_back(u);
//    else
//      ++cnt;
//  }
//  shuffle(as.begin(), as.end());
//  shuffle(bs.begin(), bs.end());
//  for (int i = 0; i < int(as.size()) && m > 0; ++i)
//    for (int j = 0; j < int(bs.size()) && m > 0; ++j) {
//      if (cnt == n - 1)
//        goto ot;
//      int u = as[i], v = bs[j];
//      if (rem[u] >= 3)
//        break;
//      if (u == v || rem[u] >= 3 || rem[v] >= 3 || adj[u].find(v) != adj[u].end())
//        continue;
//      ++rem[u], ++rem[v], --m;
//      cnt += (rem[u] == 3), cnt += (rem[v] == 3);
//      es.push_back(make_pair(u, v));
//      adj[u].insert(v), adj[v].insert(u);
//    }
//  ot: ;
//  memset(dfs_num, -1, sizeof dfs_num);
//  articulationPointAndBridge(0, -1, 0);
//  vector<int> us, vs;
//  for (int u = 0; u < n; ++u) {
//    if (!articulation_vertex[u])
//      us.push_back(u), vs.push_back(u);
//  }
//  int sz = us.size();
//  int q = min(Q * 1LL, ((sz * 1LL * (sz - 1)) / 2LL) + sz);
//  cout << n << " " << es.size() << " " << q << endl;
//  for (int i = 0; i < n; ++i)
//    cout << rr[i] << " \n"[i == n - 1];
//  for (auto cur : es)
//    cout << cur.first << " " << cur.second << "\n";
//  cout << endl;
//  shuffle(us.begin(), us.end());
//  shuffle(vs.begin(), vs.end());
//  for (int i = 0; i < int(us.size()) && q > 0; ++i)
//    for (int j = 0; j < int(vs.size()) && q > 0; ++j)
//      if (us[i] <= vs[j])
//        cout << us[i] << " " << vs[j] << "\n", --q;
//  return 0;
//}
//
//void fastInOut() {
//  ios_base::sync_with_stdio(0);
//  cin.tie(NULL), cout.tie(NULL);
//}
