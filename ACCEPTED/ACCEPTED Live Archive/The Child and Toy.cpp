#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n, m;
pair<ll, int> v[1000];
ll cpy[1000];
vector<int> e[1000];
bool vis[1000];

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> v[i].first, v[i].second = i;
		cpy[i] = v[i].first;
	}
	for (int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y, --x, --y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	sort(v, v + n);
	ll ret = 0;
	for (int i = n - 1; i >= 0; --i) {
		int idx = v[i].second;
		vis[idx] = 1;
		for (int j = 0; j < int(e[idx].size()); ++j) {
			if (vis[e[idx][j]])
				continue;
			ret += cpy[e[idx][j]];
		}
	}
	cout << ret << endl;
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
