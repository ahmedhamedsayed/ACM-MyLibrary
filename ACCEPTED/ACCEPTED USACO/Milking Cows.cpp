/*
 ID: ahmedha4
 PROG: milk2
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
	// freopen("input.txt", "rt", stdin);
	freopen("milk2.in", "rt", stdin);
	freopen("milk2.out", "wt", stdout);
#endif
	fastInOut();
	int n, LTM = 0, LIM = 0, tot = 0, maxPrev = 0;
	pair<int, int> a[5001];
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i].first >> a[i].second;
	sort(a, a + n);
	for (int i = 0; i < n; ++i) {
		if (i != 0 && a[i].first > maxPrev) {
			tot = a[i].second - a[i].first;
			LIM = max(LIM, a[i].first - maxPrev);
		} else {
			if (i == 0)
				tot = a[i].second - a[i].first;
			else
				tot += max(0, a[i].second - maxPrev);
			LTM = max(LTM, tot);
		}
		maxPrev = max(maxPrev, a[i].second);
	}
	cout << LTM << " " << LIM << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
