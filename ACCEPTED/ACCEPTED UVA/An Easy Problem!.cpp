#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

map<char, int> val;

void init() {
	int ID = 0;
	for (char i = '0'; i <= '9'; ++i)
		val[i] = ID++;
	for (char i = 'A'; i <= 'Z'; ++i)
		val[i] = ID++;
	for (char i = 'a'; i <= 'z'; ++i)
		val[i] = ID++;
}

bool can(string num, int base) {
	int mod = base - 1;
	int basePower = 1, ret = 0;
	for (int i = int(num.size()) - 1; i >= 0; --i) {
		ret = (ret + (val[num[i]] * basePower) % mod) % mod;
		basePower = (basePower * base) % mod;
	}
	return (ret == 0);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	string n;
	init();
	while (cin >> n) {
		int st = 2;
		for (int i = 0; i < int(n.size()); ++i)
			st = max(st, val[n[i]] + 1);
		int ret = -1;
		for (int i = st; i <= 62; ++i) {
			if (can(n, i)) {
				ret = i;
				break;
			}
		}
		if (ret == -1)
			cout << "such number is impossible!\n";
		else
			cout << ret << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
