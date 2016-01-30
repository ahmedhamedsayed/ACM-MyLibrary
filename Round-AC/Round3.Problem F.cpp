#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n, arr[50001], mx, dif;
map<int, int> cnt;

int main() {
	freopen("integer.in", "r", stdin);
	freopen("integer.out", "w", stdout);
	fastInOut();
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> arr[i];
	for (int i = 0; i < n; ++i) {
		++cnt[arr[i] - i];
		if (mx < cnt[arr[i] - i]) {
			dif = arr[i] - i;
			mx = cnt[arr[i] - i];
		}
	}
	cout << n - mx << "\n";
	for (int i = 0; i < n; ++i)
		cout << ((i == 0) ? "" : " ") << (i + dif);
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
