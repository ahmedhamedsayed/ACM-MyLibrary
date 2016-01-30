#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n, m;
int encode[20], ID;
ll memo[30][(1 << 9)][(1 << 9)];

int codeBuild(int idx, int msk) {
	for (int i = 0; i <= 2; ++i)
		msk = (1 << (idx + i)) | msk;
	return msk;
}

void build(int idx, int msk) {
	if (idx == n) {
		encode[ID++] = msk;
		return;
	}
	build(idx + 1, msk);
	if (idx + 3 <= n)
		build(idx + 3, codeBuild(idx, msk));
}

ll solve(int j, int mskL, int mskR) {
	if (j == m)
		return 1LL;
	ll& ret = memo[j][mskL][mskR];
	if (ret != -1)
		return ret;
	ret = 0;
	for (int i = 0; i < ID; ++i) {
		int curL = 0, curR = 0;
		int msk = encode[i];
		bool call = 1;
		for (int k = 0; k < n; ++k) {
			bool bit1 = (mskL >> k) & 1;
			bool bit2 = (mskR >> k) & 1;
			bool bit = (msk >> k) & 1;
			bool condition = (bit || (!bit && j + 3 <= m));
			if (!bit1 && !bit2 && !bit) {
				curR |= (1 << k);
				continue;
			}
			if (!bit1 && bit2 && !bit) {
				curL |= (1 << k);
				continue;
			}
			if (bit1 && !bit2 && condition) {
				curL |= (bit << k);
				curR |= (bit << k);
				continue;
			}
			if (bit1 && bit2 && condition) {
				curL |= (bit << k);
				curR |= (bit << k);
				continue;
			}
			call = 0;
			break;
		}
		if (call)
			ret += solve(j + 1, curL, curR);
	}
	return ret;
}

int main() {
	freopen("dominoes.in", "r", stdin);
	freopen("dominoes.out", "w", stdout);
	fastInOut();
	cin >> n >> m;
	if ((n * m) % 3 != 0) {
		cout << 0 << "\n";
		return 0;
	}
	if (n > m)
		swap(n, m);
	build(0, 0);
	memset(memo, -1, sizeof memo);
	int tot = (1 << n) - 1;
	ll ret = solve(0, tot, tot);
	cout << ret << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
