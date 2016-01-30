#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int X1, Y1, X2, Y2, cx, cy, r;
bool check() {
	int w = X2 - X1, h = Y2 - Y1;
	cx -= X1, cy -= Y1;
	if (w % 5 != 0 || w / 5 != r)
		return 0;
	if (h % 2 != 0 || h / 2 != cy)
		return 0;
	if ((w * 9) % 20 != 0 || (w * 9) / 20 != cx)
		return 0;
	int g = __gcd(w, h);
	w /= g, h /= g;
	if (w != 5 || h != 3)
		return 0;
	return 1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int t;
	cin >> t;
	while (t--) {
		cin >> X1 >> Y1 >> X2 >> Y2 >> cx >> cy >> r;
		cout << (check() ? "YES\n" : "NO\n");
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
