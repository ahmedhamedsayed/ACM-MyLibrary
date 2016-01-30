#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

struct node {
	int a1, a2, a3, a4;
	bool empty;

	node() {
		a1 = 0, a2 = 0;
		a3 = 0, a4 = 0;
		empty = 1;
	}
};

const int sz = 30001;
int n, m, r;
node arr[sz];
node nodes[4 * sz];

node mul(node x1, node x2) {
	if (x1.empty && x2.empty)
		return node();
	else if (x1.empty)
		return x2;
	else if (x2.empty)
		return x1;
	node ret;
	ret.a1 = ((x1.a1 * x2.a1) % r + (x1.a2 * x2.a3) % r) % r;
	ret.a2 = ((x1.a1 * x2.a2) % r + (x1.a2 * x2.a4) % r) % r;
	ret.a3 = ((x1.a3 * x2.a1) % r + (x1.a4 * x2.a3) % r) % r;
	ret.a4 = ((x1.a3 * x2.a2) % r + (x1.a4 * x2.a4) % r) % r;
	ret.empty = 0;
	return ret;
}

void build(int idx, int st, int ed) {
	if (st == ed) {
		nodes[idx] = arr[st];
		return;
	}
	int ch1 = 2 * idx + 1, ch2 = 2 * idx + 2;
	int md = (st + ed) / 2;
	build(ch1, st, md);
	build(ch2, md + 1, ed);
	nodes[idx] = mul(nodes[ch1], nodes[ch2]);
}

node query(int idx, int s, int e, int st, int ed) {
	if (e < st || s > ed)
		return node();
	if (st >= s && ed <= e)
		return nodes[idx];
	int ch1 = 2 * idx + 1, ch2 = 2 * idx + 2;
	int md = (st + ed) / 2;
	node ret1 = query(ch1, s, e, st, md);
	node ret2 = query(ch2, s, e, md + 1, ed);
	return mul(ret1, ret2);
}

int main() {
	freopen("crypto.in", "r", stdin);
	freopen("crypto.out", "w", stdout);
	fastInOut();
	cin >> r >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> arr[i].a1 >> arr[i].a2;
		cin >> arr[i].a3 >> arr[i].a4;
		arr[i].empty = 0;
	}
	build(0, 0, n - 1);
	int s, e;
	bool enter = 0;
	while (m--) {
		if (enter)
			cout << "\n";
		enter = 1;
		cin >> s >> e;
		--s, --e;
		node ret = query(0, s, e, 0, n - 1);
		cout << ret.a1 << " " << ret.a2 << "\n";
		cout << ret.a3 << " " << ret.a4 << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
