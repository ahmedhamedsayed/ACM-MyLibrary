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
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int t;
	string N;
	cin >> t;
	while (t--) {
		cin >> N;
		ll n = N.size(), ret = 0;
		for (int i = 0; i < n; ++i)
			ret += power(int(N[i] - '0'), n);
		for (int i = n - 1; i >= 0; --i) {
			if (int(N[i] - '0') != (ret % 10)) {
				cout << "Not Armstrong\n";
				goto nxt;
			}
			ret /= 10;
		}
		cout << "Armstrong\n";
		nxt: ;
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
