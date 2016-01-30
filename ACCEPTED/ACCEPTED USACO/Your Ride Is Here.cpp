/*
 ID: ahmedha4
 PROG: ride
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

int cnt(string z) {
	int cnt = 1;
	for (int i = 0; i < int(z.size()); ++i)
		cnt = (cnt * (z[i] - 'A' + 1)) % 47;
	return cnt;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("ride.in", "rt", stdin);
	freopen("ride.out", "wt", stdout);
#endif
	fastInOut();
	string x, y;
	cin >> x >> y;
	int cntx = cnt(x), cnty = cnt(y);
	cout << ((cntx == cnty) ? "GO\n" : "STAY\n");
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
