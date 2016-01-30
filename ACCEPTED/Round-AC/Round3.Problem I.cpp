#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n, sz;
vector<int> factors;
vector<vector<int> > ret;

void BT(int idx, int sign) {
	if (idx == sz) {
		if (sign == (n / abs(n))) {
			ret.push_back(factors);
			int nw = ret.size() - 1;
			sort(ret[nw].begin(), ret[nw].end());
		}
		return;
	}
	int lst = idx;
	while (lst < sz && factors[idx] == factors[lst])
		++lst;
	BT(lst, sign);
	int dif = lst - idx, nxt = sign;
	for (int i = 0; i < dif; ++i) {
		factors[idx + i] *= -1;
		nxt *= -1;
		BT(lst, nxt);
	}
	for (int i = 0; i < dif; ++i)
		factors[idx + i] *= -1;
}

int main() {
	freopen("product.in", "r", stdin);
	freopen("product.out", "w", stdout);
	fastInOut();
	cin >> n;
	for (int i = 2; i <= sqrt(abs(n)); ++i) {
		while (abs(n) % i == 0) {
			n /= i;
			factors.push_back(i);
		}
	}
	if (abs(n) != 1)
		factors.push_back(abs(n));
	sz = factors.size();
	BT(0, 1);
	sort(ret.begin(), ret.end());
	cout << int(ret.size()) << "\n";
	for (int i = 0; i < int(ret.size()); ++i) {
		for (int j = 0; j < sz; ++j)
			cout << ((j == 0) ? "" : " ") << ret[i][j];
		cout << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
