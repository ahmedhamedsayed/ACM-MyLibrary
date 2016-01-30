#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n, cnt[10001];
vector<int> son[10001];

void init() {
	for (int i = 0; i <= n; ++i)
		son[i].clear();
	memset(cnt, 0, sizeof cnt);
}

int build(int u) {
	int sz = son[u].size();
	if (sz == 0)
		return 0;
	for (int v = 0; v < sz; ++v)
		cnt[u] += (1 + build(son[u][v]));
	return cnt[u];
}

ll solve(int u) {
	int idx = 0, sz = son[u].size();
	ll sv[10000];
	for (int v = 0; v < sz; ++v)
		sv[idx++] = 1 + cnt[son[u][v]];
	ll ret = 0;
	for (int i = 0; i < idx; ++i) {
		ret += sv[i];
		for (int j = i + 1; j < idx; ++j)
			ret += (sv[i] * sv[j]);
	}
	return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int t, p;
	cin >> t;
	for (int tst = 1; tst <= t; ++tst) {
		cin >> n, init();
		for (int i = 1; i <= n; ++i)
			cin >> p, son[p].push_back(i);
		build(0);
		cout << "Forest#" << tst << ":";
		for (int i = 1; i <= n; ++i)
			cout << " " << solve(i);
		cout << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
