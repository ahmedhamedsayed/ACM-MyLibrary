#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int main() {
	freopen("huffman.in", "r", stdin);
	freopen("huffman.out", "w", stdout);
	fastInOut();
	int n;
	priority_queue<ll> tree;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		ll a;
		cin >> a;
		tree.push(-a);
	}
	ll ret = 0;
	for (int i = 1; i < n; ++i) {
		ll mn1 = -tree.top();
		tree.pop();
		ll mn2 = -tree.top();
		tree.pop();
		ll mn = mn1 + mn2;
		ret += mn;
		tree.push(-mn);
	}
	cout << ret << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
