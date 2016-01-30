#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

pair<int, int> arr[3003];
int n, a[3003];
int memo[3003][3003];

int bs(int idx1, int idx2) {
	int val = a[idx1] + a[idx2];
	int st = 0, ed = n - 1;
	while (st < ed) {
		int md = (st + ed) / 2;
		if (arr[md].first == val) {
			if (arr[md].second <= idx2)
				st = md + 1;
			else
				ed = md;
		} else if (arr[md].first > val)
			ed = md - 1;
		else
			st = md + 1;
	}
	if (st == ed && arr[st].first == val && arr[st].second > idx2)
		return arr[st].second;
	return -1;
}

int solve(int idx1, int idx2) {
	if (idx2 == n)
		return 0;
	int& ret = memo[idx1][idx2];
	if (ret != -1)
		return ret;
	ret = 0;
	int nxt = bs(idx1, idx2);
	if (nxt != -1)
		ret = 1 + solve(idx2, nxt);
	return ret;
}

void buildPath(int idx1, int idx2) {
	while (1) {
		if (idx2 == n)
			break;
		int nxt = bs(idx1, idx2);
		if (nxt != -1) {
			cout << " " << a[nxt];
			idx1 = idx2, idx2 = nxt;
		} else
			break;
	}
	cout << "\n";
}

int main() {
	freopen("fibsubseq.in", "r", stdin);
	freopen("fibsubseq.out", "w", stdout);
	fastInOut();
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		arr[i] = make_pair(a[i], i);
	}
	if (n == 1) {
		cout << "1\n" << a[0] << "\n";
		return 0;
	}
	sort(arr, arr + n);
	memset(memo, -1, sizeof memo);
	int ret = -2e9, idx1 = -1, idx2 = -1;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			int cur = solve(i, j);
			if (ret < cur) {
				ret = cur;
				idx1 = i, idx2 = j;
			}
		}
	}
	ret = max(0, ret) + 2;
	cout << ret << "\n" << a[idx1] << " " << a[idx2];
	buildPath(idx1, idx2);
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
