#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n, t, dis[50], cum[50];
int m1, m2, t1[50], t2[50];
int memo[50][200];

int solve(int idx, int time) {
	if (idx == n - 1 && t == time)
		return 0;
	if (time > t)
		return 1e9;
	int& ret = memo[idx][time];
	if (ret != -1)
		return ret;
	ret = ((idx == n - 1) ? (t - time) : 1e9);
	int ret1 = 1e9;
	if (idx < n - 1) {
		for (int i = 0; i < m1; ++i) {
			int tk = t1[i] + ((idx == 0) ? 0 : cum[idx - 1]);
			if (tk >= time) {
				int dif = tk - time;
				int nxt = tk + dis[idx];
				ret1 = min(ret1, dif + solve(idx + 1, nxt));
			}
		}
	}
	int ret2 = 1e9;
	if (idx > 0) {
		for (int i = 0; i < m2; ++i) {
			int tk = t2[i] + cum[n - 2] - cum[idx - 1];
			if (tk >= time) {
				int dif = tk - time;
				int nxt = tk + dis[idx - 1];
				ret2 = min(ret2, dif + solve(idx - 1, nxt));
			}
		}
	}
	return ret = min(ret, min(ret1, ret2));
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int tst = 0;
	while (cin >> n && n != 0) {
		cin >> t;
		for (int i = 0; i < n - 1; ++i) {
			cin >> dis[i];
			cum[i] = ((i == 0) ? 0 : cum[i - 1]) + dis[i];
		}
		cin >> m1;
		for (int i = 0; i < m1; ++i)
			cin >> t1[i];
		cin >> m2;
		for (int i = 0; i < m2; ++i)
			cin >> t2[i];
		memset(memo, -1, sizeof memo);
		int ret = solve(0, 0);
		cout << "Case Number " << ++tst << ": ";
		if (ret >= 1e9)
			cout << "impossible\n";
		else
			cout << ret << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
