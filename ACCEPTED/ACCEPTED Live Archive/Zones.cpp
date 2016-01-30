#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n, m, srv[20], mx, seq;
vector<vector<int> > common;
vector<int> val;

void init() {
	mx = -1, seq = 0;
}

int calc(int msk) {
	int ret = 0;
	for (int i = 0; i < int(common.size()); ++i) {
		int cnt = 0;
		for (int j = 0; j < int(common[i].size()); ++j)
			cnt += ((msk >> common[i][j]) & 1);
		ret += (val[i] * (cnt - 1) * (cnt > 1));
	}
	return ret;
}

void BT(int idx, int msk, int tot, int rem) {
	if (idx == n || rem == 0) {
		if (rem > 0)
			return;
		int ret = tot - calc(msk);
		if (mx < ret)
			mx = ret, seq = msk;
		return;
	}
	BT(idx + 1, (1 << idx) | msk, tot + srv[idx], rem - 1);
	BT(idx + 1, msk, tot, rem);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int tst = 0;
	while (cin >> n >> m && (n != 0 || m != 0)) {
		init();
		for (int i = 0; i < n; ++i)
			cin >> srv[i];
		int t, k;
		cin >> t;
		common.resize(t);
		val.resize(t);
		for (int i = 0; i < t; ++i) {
			cin >> k;
			common[i].resize(k);
			for (int j = 0; j < k; ++j)
				cin >> common[i][j], --common[i][j];
			cin >> val[i];
		}
		BT(0, 0, 0, m);
		cout << "Case Number  " << ++tst << "\n";
		cout << "Number of Customers: " << mx << "\n";
		cout << "Locations recommended:";
		for (int i = 0; i < n; ++i) {
			if ((1 << i) & seq)
				cout << " " << i + 1;
		}
		cout << "\n\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
