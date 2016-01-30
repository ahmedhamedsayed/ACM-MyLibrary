#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n, cntOne[(1 << 15)];
pair<int, int> pnts[15], cur[15];

void countOnes(int idx, int msk, int ones) {
	if (idx == 15) {
		cntOne[msk] = ones;
		return;
	}
	countOnes(idx + 1, msk, ones);
	countOnes(idx + 1, (1 << idx) | msk, ones + 1);
}

int dist(pair<int, int> p1, pair<int, int> p2) {
	return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int memo[(1 << 15)];
int solve(int msk) {
	int cellIdx = cntOne[msk];
	if (cellIdx == n)
		return 0;
	int& ret = memo[msk];
	if (ret != -1)
		return ret;
	ret = 1e9;
	for (int i = 0; i < n; ++i) {
		if ((msk >> i) & 1)
			continue;
		ret = min(ret, dist(pnts[i], cur[cellIdx]) + solve((1 << i) | msk));
	}
	return ret;
}

int runRows() {
	int ret = 1e9;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			cur[j] = make_pair(i, j);
		memset(memo, -1, sizeof memo);
		ret = min(ret, solve(0));
	}
	return ret;
}

int runCols() {
	int ret = 1e9;
	for (int j = 0; j < n; ++j) {
		for (int i = 0; i < n; ++i)
			cur[i] = make_pair(i, j);
		memset(memo, -1, sizeof memo);
		ret = min(ret, solve(0));
	}
	return ret;
}

int runDigs() {
	int ret = 1e9;
	for (int k = 0; k < n; ++k)
		cur[k] = make_pair(k, k);
	memset(memo, -1, sizeof memo);
	ret = min(ret, solve(0));
	for (int k = 0; k < n; ++k)
		cur[k] = make_pair(k, n - k - 1);
	memset(memo, -1, sizeof memo);
	ret = min(ret, solve(0));
	return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int tst = 0;
	countOnes(0, 0, 0);
	while (cin >> n && n != 0) {
		for (int i = 0; i < n; ++i) {
			int x, y;
			cin >> x >> y;
			pnts[i] = make_pair(x - 1, y - 1);
		}
		int ret = 1e9;
		ret = min(ret, runRows());
		ret = min(ret, runCols());
		ret = min(ret, runDigs());
		cout << "Board " << ++tst << ": " << ret << " moves required.\n\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
