/*
 ID: ahmedha4
 PROG: barn1
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
	freopen("barn1.in", "rt", stdin);
	freopen("barn1.out", "wt", stdout);
#endif
	fastInOut();
	int m, s, c, a[202], st;
	vector<pair<int, int> > intrvl;
	cin >> m >> s >> c;
	for (int i = 0; i < c; ++i)
		cin >> a[i];
	a[c++] = 1e9, sort(a, a + c);
	for (int i = 0; i < c; ++i) {
		if (i == 0)
			st = a[i];
		if (i == 0 || a[i] - 1 == a[i - 1])
			continue;
		intrvl.push_back(make_pair(st, a[i - 1]));
		st = a[i];
	}
	while (int(intrvl.size()) > m) {
		int idx = -1, mnVl = 1e9;
		for (int i = 1; i < int(intrvl.size()); ++i) {
			int diff = intrvl[i].first - intrvl[i - 1].second - 1;
			if (mnVl > diff)
				mnVl = diff, idx = i;
		}
		intrvl[idx].first = intrvl[idx - 1].first;
		intrvl.erase(intrvl.begin() + idx - 1);
	}
	int tot = 0;
	for (int i = 0; i < int(intrvl.size()); ++i)
		tot += intrvl[i].second - intrvl[i].first + 1;
	cout << tot << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
