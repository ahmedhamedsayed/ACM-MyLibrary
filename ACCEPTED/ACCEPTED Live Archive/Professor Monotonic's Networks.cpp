#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n, k, a[150], b[150], calc[12], mxTime;

void init() {
	memset(calc, 0, sizeof calc);
	mxTime = 0;
}

int runNetwork(int msk) {
	vector<int> mskIdx;
	int curState[12];
	memset(curState, 0, sizeof curState);
	mskIdx.push_back(msk);
	for (int i = 0; i < k; ++i) {
		int idx1 = curState[a[i]], idx2 = curState[b[i]];
		bool bt1 = ((mskIdx[idx1] >> a[i]) & 1);
		bool bt2 = ((mskIdx[idx2] >> b[i]) & 1);
		int nxt = max(idx1, idx2) + 1;
		if (nxt == int(mskIdx.size()))
			mskIdx.push_back(0);
		mskIdx[nxt] |= (min(bt1, bt2) << a[i]);
		mskIdx[nxt] |= (max(bt1, bt2) << b[i]);
		curState[a[i]] = curState[b[i]] = nxt;
	}
	mxTime = mskIdx.size() - 1;
	int ret = 0;
	for (int i = 0; i < n; ++i) {
		int idx = curState[i];
		ret |= (((mskIdx[idx] >> i) & 1) << i);
	}
	return ret;
}

bool isSorted(int msk) {
	for (int i = 0; i < n - 1; ++i)
		if (((msk >> i) & 1) && !((msk >> (i + 1)) & 1))
			return 0;
	return 1;
}

bool canSort(int msk, int idx) {
	if (idx == n)
		return isSorted(runNetwork(msk));
	return (canSort(msk, idx + 1) && canSort((1 << idx) | msk, idx + 1));
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int tst = 0;
	while (cin >> n >> k && n != 0) {
		init();
		for (int i = 0; i < k; ++i) {
			cin >> a[i] >> b[i], --a[i], --b[i];
			++calc[a[i]], ++calc[b[i]];
		}
		bool ret = canSort(0, 0);
		cout << "Case " << ++tst;
		if (ret)
			cout << " is a sorting network and operates in ";
		else
			cout << " is not a sorting network and operates in ";
		cout << mxTime << " time units.\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
