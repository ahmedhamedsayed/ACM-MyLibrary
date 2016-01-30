#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int r, c, compNum[100][100], sz;
bool vis[100][100], is;
char grid[100][100];
vector<pair<int, pair<int, int> > > G;
int parent[5000], Rank[5000];

void init() {
	memset(compNum, -1, sizeof compNum);
	memset(vis, 0, sizeof vis);
	G.clear();
	is = 0, sz = 0;
	for (int i = 0; i < 5000; ++i)
		parent[i] = i;
	memset(Rank, 0, sizeof Rank);
}

bool check(int i, int j) {
	return (i >= 0 && i < r && j >= 0 && j < c);
}

int d1[] = { 0, 0, -1, 1, -1, -1, 1, 1 };
int d2[] = { -1, 1, 0, 0, -1, 1, -1, 1 };
void dfs(int i, int j) {
	if (vis[i][j])
		return;
	vis[i][j] = 1;
	compNum[i][j] = sz;
	for (int k = 0; k < 8; ++k) {
		int ni = i + d1[k];
		int nj = j + d2[k];
		if (check(ni, nj) && grid[ni][nj] == '#')
			dfs(ni, nj);
	}
}

void add(int c, int f, int t) {
	is = 1;
	G.push_back(make_pair(c, make_pair(f, t)));
}

int d[] = { -1, 0, 1 };

void buildGraphI() {
	for (int j = 0; j < c; ++j) {
		int lstI = -1, lstNum = -1;
		for (int i = 0; i < r; ++i) {
			for (int k = 0; k < 3; ++k) {
				int nj = j + d[k];
				if (check(i, nj) && lstNum != -1) {
					int cur = compNum[i][nj];
					if (cur != -1 && lstNum != cur) {
						add(i - lstI - 1, lstNum, cur);
					}
				}
			}
			if (compNum[i][j] != -1)
				lstI = i, lstNum = compNum[i][j];
		}
	}
}

void buildGraphJ() {
	for (int i = 0; i < r; ++i) {
		int lstJ = -1, lstNum = -1;
		for (int j = 0; j < c; ++j) {
			for (int k = 0; k < 3; ++k) {
				int ni = i + d[k];
				if (check(ni, j) && lstNum != -1) {
					int cur = compNum[ni][j];
					if (cur != -1 && lstNum != cur)
						add(j - lstJ - 1, lstNum, cur);
				}
			}
			if (compNum[i][j] != -1)
				lstJ = j, lstNum = compNum[i][j];
		}
	}
}

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

pair<int, pair<int, int> > kruskal() {
	int cnt = 0, cst = 0, num = sz;
	sort(G.begin(), G.end());
	for (int i = 0; i < int(G.size()); ++i) {
		int f = G[i].second.first, t = G[i].second.second;
		int root1 = Find(f), root2 = Find(t);
		if (root1 == root2)
			continue;
		++cnt, cst += G[i].first, --num;
		Union(f, t);
	}
	return make_pair(cnt, make_pair(cst, num));
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int tst = 0;
	bool enter = 0;
	while (cin >> r >> c && r != 0 && c != 0) {
		if (enter)
			cout << "\n";
		enter = 1;
		init();
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j)
				cin >> grid[i][j];
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				if (!vis[i][j] && grid[i][j] == '#') {
					dfs(i, j);
					++sz;
				}
			}
		}
		cout << "City " << ++tst << "\n";
		if (sz <= 1) {
			cout << "No bridges are needed.\n";
			continue;
		}
		buildGraphI();
		buildGraphJ();
		if (!is) {
			cout << "No bridges are possible.\n";
			cout << sz << " disconnected groups\n";
			continue;
		}
		pair<int, pair<int, int> > ret = kruskal();
		cout << ret.first;
		if (ret.first == 1)
			cout << " bridge of total length ";
		else
			cout << " bridges of total length ";
		cout << ret.second.first << "\n";
		if (ret.second.second > 1)
			cout << ret.second.second << " disconnected groups\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
