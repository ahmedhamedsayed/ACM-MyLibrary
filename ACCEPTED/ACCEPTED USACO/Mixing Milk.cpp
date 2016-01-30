/*
 ID: ahmedha4
 PROG: milk
 LANG: C++
 */
#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int main() {
#ifndef ONLINE_JUDGE
	freopen("milk.in", "rt", stdin);
	freopen("milk.out", "wt", stdout);
#endif
	fastInOut();
	int n, m, tot = 0;
	pair<int, int> a[5001];
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
		cin >> a[i].first >> a[i].second;
	sort(a, a + m);
	for (int i = 0; i < m; ++i) {
		int tkn = min(n, a[i].second);
		tot += tkn * a[i].first;
		n -= tkn;
	}
	cout << tot << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
