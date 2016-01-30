#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int arr[100000], nxt[100000], OO = 1e9;
map<int, int> lst;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int t, n;
	cin >> t;
	while (t--) {
		cin >> n;
		lst.clear();
		for (int i = 0; i < n; ++i)
			cin >> arr[i], lst[arr[i]] = n;
		for (int i = n - 1; i >= 0; --i) {
			nxt[i] = min((i == n - 1) ? OO : nxt[i + 1], lst[arr[i]]);
			lst[arr[i]] = i;
		}
		ll ret = 0;
		for (int i = 0; i < n; ++i)
			ret += (nxt[i] - i);
		cout << ret << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
