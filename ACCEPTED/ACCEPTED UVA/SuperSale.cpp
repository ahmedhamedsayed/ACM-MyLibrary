#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n, g, fm[100];
pair<int, int> obj[1000];

int memo[1000][30];
int solve(int idx, int rem) {
	if (idx == n || rem < obj[idx].first)
		return 0;
	if (rem < obj[idx].first)
		return 0;
	int &ret = memo[idx][rem];
	if (ret != -1)
		return ret;
	int ret1 = solve(idx + 1, rem);
	int ret2 = obj[idx].second + solve(idx + 1, rem - obj[idx].first);
	return ret = max(ret1, ret2);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int t;
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> obj[i].second >> obj[i].first;
		sort(obj, obj + n);
		cin >> g;
		for (int i = 0; i < g; ++i)
			cin >> fm[i];
		sort(fm, fm + g);
		int ret = 0;
		memset(memo, -1, sizeof memo);
		for (int i = 0; i < g; ++i)
			ret += solve(0, fm[i]);
		cout << ret << endl;
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
