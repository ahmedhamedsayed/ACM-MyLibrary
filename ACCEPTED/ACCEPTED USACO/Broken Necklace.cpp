/*
 ID: ahmedha4
 PROG: beads
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

int n;
string x;

int dwnUp(int idx, int inc) {
	int cnt = 0, prev = -1;
	while (1) {
		if (idx < 0)
			idx = n - 1;
		else if (idx == n)
			idx = 0;
		if (x[idx] == 'b') {
			if (prev == 2)
				return cnt;
			prev = 1;
		} else if (x[idx] == 'r') {
			if (prev == 1)
				return cnt;
			prev = 2;
		}
		++cnt, idx += inc;
		if (cnt == n)
			return cnt;
	}
	return 0;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("beads.in", "rt", stdin);
	freopen("beads.out", "wt", stdout);
#endif
	fastInOut();
	int ret = 0;
	cin >> n >> x;
	for (int i = 0; i < n; ++i) {
		int cnt = dwnUp(i - 1, -1) + dwnUp(i, 1);
		cnt = min(cnt, n), ret = max(ret, cnt);
	}
	cout << ret << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
