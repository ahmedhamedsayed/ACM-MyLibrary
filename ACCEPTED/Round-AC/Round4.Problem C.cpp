#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

bool vis[1000001];
int ret[21], c;

void check(int msk1, int msk2) {
	int sz1 = 0, sz2 = 0, set1 = 0, set2 = 0;
	for (int i = 1; i <= c; ++i) {
		if ((msk1 >> i) & 1)
			++sz1, set1 += ret[i];
		else if ((msk2 >> i) & 1)
			++sz2, set2 += ret[i];
	}
	if (sz1 > 0 && abs(sz1 - sz2) == 1) {
		if (sz1 > sz2 && set1 > set2)
			vis[set1 - set2] = 1;
		if (sz1 < sz2 && set1 < set2)
			vis[set2 - set1] = 1;
	}
}

void rec(int idx, int msk1, int msk2) {
	if (idx == 0) {
		check(msk1, msk2);
		return;
	}
	rec(idx - 1, msk1, msk2);
	rec(idx - 1, (1 << idx) | msk1, msk2);
	rec(idx - 1, msk1, (1 << idx) | msk2);
}

int solve(int n) {
	int save[] = { 4485, 8808, 17306, 34302, 68009, 134853 };
	if (n > 14)
		return save[n - 15];
	ret[1] = 1, vis[1] = 1;
	for (int i = 2; i <= n; ++i) {
		c = i - 1, rec(i - 1, 0, 0);
		ret[i] = ret[i - 1] + 1;
		while (vis[ret[i]])
			++ret[i];
	}
	return ret[n];
}

int main() {
	freopen("chipmunks.in", "r", stdin);
	freopen("chipmunks.out", "w", stdout);
	fastInOut();
	int n;
	while (cin >> n)
		cout << solve(n) << endl;
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
