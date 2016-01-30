/*
 ID: ahmedha4
 PROG: gift1
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
	freopen("gift1.in", "rt", stdin);
	freopen("gift1.out", "wt", stdout);
#endif
	fastInOut();
	int np, amnt, num;
	string names[11], from, to;
	map<string, int> account;
	cin >> np;
	for (int i = 0; i < np; ++i)
		cin >> names[i];
	for (int i = 0; i < np; ++i) {
		cin >> from >> amnt >> num;
		if (num == 0) {
			account[from] += amnt;
			continue;
		}
		account[from] -= (amnt - (amnt % num)), amnt /= num;
		for (int j = 0; j < num; ++j)
			cin >> to, account[to] += amnt;
	}
	for (int i = 0; i < np; ++i)
		cout << names[i] << " " << account[names[i]] << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
