/*
 ID: ahmedha4
 PROG: friday
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
	freopen("friday.in", "rt", stdin);
	freopen("friday.out", "wt", stdout);
#endif
	fastInOut();
	int n, cur = 2, ret[7];
	int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	cin >> n, memset(ret, 0, sizeof(ret));
	for (int i = 1900; i < 1900 + n; ++i) {
		bool isLeap = (!(i % 100) && !(i % 400)) || ((i % 100) && !(i % 4));
		month[1] += isLeap;
		for (int j = 0; j < 12; ++j) {
			for (int k = 1; k <= month[j]; ++k) {
				if (k == 13)
					++ret[cur];
				cur = (cur + 1) % 7;
			}
		}
		month[1] -= isLeap;
	}
	for (int i = 0; i < 7; ++i)
		cout << ret[i] << ((i == 6) ? "\n" : " ");
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
