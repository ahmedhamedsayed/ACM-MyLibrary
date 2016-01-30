#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

const int NegOO = -2147483648;
const int OO = 2147483647;
const int sz = 100000;
int n, m;
pair<int, pair<int, int> > q[sz];
int mx[4 * sz], mn[4 * sz];
int ret[sz];
bool updateChild[4 * sz];

void update(int idx, int s, int e, int st, int ed, int val) {
	if (e < st || s > ed)
		return;
	if (st >= s && ed <= e) {
		if (mx[idx] <= val) {
			mx[idx] = val;
			updateChild[idx] = 1;
		}
		return;
	}
	int ch1 = 2 * idx + 1, ch2 = 2 * idx + 2;
	int md = (st + ed) / 2;
	if (updateChild[idx]) {
		mx[ch1] = mx[idx];
		mx[ch2] = mx[idx];
		updateChild[ch1] = 1;
		updateChild[ch2] = 1;
		updateChild[idx] = 0;
	}
	update(ch1, s, e, st, md, val);
	update(ch2, s, e, md + 1, ed, val);
	mx[idx] = max(mx[ch1], mx[ch2]);
}

int query1(int idx, int cur, int st, int ed) {
	if (cur < st || cur > ed)
		return NegOO;
	if (st == ed)
		return mx[idx];
	int ch1 = 2 * idx + 1, ch2 = 2 * idx + 2;
	int md = (st + ed) / 2;
	if (updateChild[idx]) {
		mx[ch1] = mx[idx];
		mx[ch2] = mx[idx];
		updateChild[ch1] = 1;
		updateChild[ch2] = 1;
		updateChild[idx] = 0;
	}
	int ret1 = query1(ch1, cur, st, md);
	int ret2 = query1(ch2, cur, md + 1, ed);
	return max(ret1, ret2);
}

void build(int idx, int st, int ed) {
	if (st == ed) {
		mn[idx] = ret[st];
		return;
	}
	int ch1 = 2 * idx + 1, ch2 = 2 * idx + 2;
	int md = (st + ed) / 2;
	build(ch1, st, md);
	build(ch2, md + 1, ed);
	mn[idx] = min(mn[ch1], mn[ch2]);
}

int query2(int idx, int s, int e, int st, int ed) {
	if (e < st || s > ed)
		return OO;
	if (st >= s && ed <= e)
		return mn[idx];
	int ch1 = 2 * idx + 1, ch2 = 2 * idx + 2;
	int md = (st + ed) / 2;
	int ret1 = query2(ch1, s, e, st, md);
	int ret2 = query2(ch2, s, e, md + 1, ed);
	return min(ret1, ret2);
}

int main() {
	freopen("rmq.in", "r", stdin);
	freopen("rmq.out", "w", stdout);
	fastInOut();
	for (int i = 0; i < 4 * sz; ++i) {
		mx[i] = NegOO;
		mn[i] = OO;
	}
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int fm, to, cst;
		cin >> fm >> to >> cst;
		--fm, --to;
		q[i] = make_pair(cst, make_pair(fm, to));
	}
	sort(q, q + m);
	for (int i = 0; i < m; ++i) {
		int fm, to, cst;
		fm = q[i].second.first, to = q[i].second.second;
		cst = q[i].first;
		update(0, fm, to, 0, n - 1, cst);
	}
	for (int i = 0; i < n; ++i)
		ret[i] = query1(0, i, 0, n - 1);
	build(0, 0, n - 1);
	for (int i = 0; i < m; ++i) {
		int fm, to, cst;
		fm = q[i].second.first, to = q[i].second.second;
		cst = q[i].first;
		int cur = query2(0, fm, to, 0, n - 1);
		if (cur != cst) {
			cout << "inconsistent\n";
			return 0;
		}
	}
	cout << "consistent\n";
	for (int i = 0; i < n; ++i)
		cout << ret[i] << ((i == n - 1) ? "\n" : " ");
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
