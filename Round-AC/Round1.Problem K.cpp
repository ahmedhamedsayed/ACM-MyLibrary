#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

const int sz = 50000;
int n, s;
map<pair<int, int>, int> arr;
int saveSz[sz];
int parent[sz], rnk[sz];
int d1[][6] = { { 0, 1, 1, 0, -1, -1 }, { 0, 1, 1, 0, -1, -1 } };
int d2[][6] = { { 1, 0, -1, -1, -1, 0 }, { 1, 1, 0, -1, 0, 1 } };
int vis[sz], ID;

void init() {
	for (int i = 0; i < n; ++i)
		parent[i] = i;
}

int find(int c) {
	if (parent[c] == c)
		return c;
	return find(parent[c]);
}

void merge(int c1, int c2) {
	int root1 = find(c1);
	int root2 = find(c2);
	if (root1 == root2)
		return;
	if (rnk[root1] == rnk[root2])
		rnk[root1]++;
	if (rnk[root2] > rnk[root1]) {
		parent[root1] = root2;
		saveSz[root2] += saveSz[root1];
		saveSz[root1] = 0;
	} else {
		parent[root2] = root1;
		saveSz[root1] += saveSz[root2];
		saveSz[root2] = 0;
	}
}

int main() {
	freopen("islands.in", "r", stdin);
	freopen("islands.out", "w", stdout);
	fastInOut();
	cin >> n >> s;
	init();
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		if (arr.find(make_pair(x, y)) != arr.end())
			continue;
		int curParent = parent[i];
		if (curParent == i)
			saveSz[i] = 1;
		vector<int> pars;
		for (int j = 0; j < 6; ++j) {
			int odd = abs(x) % 2;
			int nx = x + d1[odd][j];
			int ny = y + d2[odd][j];
			if (arr.find(make_pair(nx, ny)) != arr.end())
				pars.push_back(arr[make_pair(nx, ny)]);
		}
		int tot = saveSz[curParent];
		++ID;
		for (int j = 0; j < int(pars.size()); ++j) {
			int cur = find(pars[j]);
			if (vis[cur] != ID) {
				tot += saveSz[cur];
				vis[cur] = ID;
			}
		}
		if (tot > s) {
			saveSz[i] = 0;
			continue;
		}
		arr[make_pair(x, y)] = i;
		for (int j = 0; j < int(pars.size()); ++j)
			merge(i, pars[j]);
	}
	sort(saveSz, saveSz + n);
	int totRet = 0;
	for (int i = 0; i < n; ++i)
		totRet += (saveSz[i] != 0);
	cout << totRet << endl;
	for (int i = 0; i < n; ++i) {
		if (saveSz[i] != 0) {
			cout << saveSz[i];
			totRet--;
			cout << ((totRet == 0) ? "\n" : " ");
		}
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
