#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n, tst;
double x[51], y[51], m[51];

double ED(int i, int j) {
	double dif1 = x[i] - x[j];
	double dif2 = y[i] - y[j];
	return sqrt((dif1 * dif1) + (dif2 * dif2));
}

struct edge {
	int from, to;
	double cst;
	bool operator<(const edge& t) const {
		return cst < t.cst;
	}
};

edge edges[51 * 51];
int sz;
int parent[51 * 51], Rank[51 * 51];
vector<pair<int, double> > ret[51];

int Find(int cur) {
	if (parent[cur] == cur)
		return cur;
	return Find(parent[cur]);
}

void Union(int i, int j) {
	int root1 = Find(i);
	int root2 = Find(j);
	if (Rank[root1] < Rank[root2])
		parent[root1] = root2;
	else if (Rank[root1] > Rank[root2])
		parent[root2] = root1;
	else {
		parent[root2] = root1;
		++Rank[root1];
	}
}

void kruskal() {
	sort(edges, edges + sz);
	for (int i = 0; i < sz; ++i) {
		int root1 = Find(edges[i].from);
		int root2 = Find(edges[i].to);
		if (root1 == root2)
			continue;
		ret[edges[i].from].push_back(make_pair(edges[i].to, edges[i].cst));
		ret[edges[i].to].push_back(make_pair(edges[i].from, edges[i].cst));
		Union(edges[i].from, edges[i].to);
	}
}

void init() {
	sz = 0;
	for (int i = 0; i < 50; ++i)
		parent[i] = i;
	memset(Rank, 0, sizeof Rank);
	for (int i = 0; i < 50; ++i)
		ret[i].clear();
}

double getRet() {
	bool vis[51];
	memset(vis, 0, sizeof vis);
	queue<pair<int, double> > bfs;
	bfs.push(make_pair(0, 0));
	double r = 0;
	while (bfs.size()) {
		int cur = bfs.front().first;
		double cst = bfs.front().second;
		bfs.pop();
		int sz = ret[cur].size();
		r += (m[cur] * cst);
		vis[cur] = 1;
		for (int i = 0; i < sz; ++i) {
			int nxt = ret[cur][i].first;
			if (!vis[nxt]) {
				double nCst = max(ret[cur][i].second, cst);
				bfs.push(make_pair(nxt, nCst));
			}
		}
	}
	return r;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	while (cin >> n && n != 0) {
		init();
		double sm = 0.0;
		for (int i = 0; i < n; ++i) {
			cin >> x[i] >> y[i] >> m[i];
			sm += m[i];
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i != j) {
					edges[sz++] = {i,j,ED(i,j)};
				}
			}
		}
		kruskal();
		double ret = getRet() / sm;
		cout << fixed << setprecision(2);
		cout << "Island Group: " << ++tst << " Average " << ret << "\n\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
