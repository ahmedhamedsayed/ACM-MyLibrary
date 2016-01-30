#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

const int sz = 100000;
int n, til[sz], prv[sz];
pair<pair<int, int>, int> a[sz];

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
	if (a.first.first == b.first.first)
		return a.first.second > b.first.second;
	return a.first.first < b.first.first;
}

int bs(int st, int ed, int i) {
	while (st < ed) {
		int md = (st + ed) / 2;
		if (a[til[md]].first.second < a[i].first.second)
			st = md + 1;
		else if (a[til[md]].first.second > a[i].first.second)
			ed = md;
		else
			return -1;
	}
	return (a[til[st]].first.second == a[i].first.second) ? -1 : st;
}

vector<int> getRet() {
	int l = 1;
	memset(prv, -1, sizeof prv);
	for (int i = 1; i < n; ++i) {
		int sc = a[i].first.second;
		if (sc < a[til[0]].first.second) {
			til[0] = i;
			continue;
		}
		int sc1 = a[til[l - 1]].first.second;
		if (sc > sc1) {
			prv[i] = til[l - 1];
			til[l++] = i;
			continue;
		}
		int pos = bs(0, l - 1, i);
		if (pos == -1)
			continue;
		prv[i] = til[pos - 1];
		til[pos] = i;
	}
	vector<int> ret;
	for (int i = til[l - 1]; i >= 0; i = prv[i])
		ret.push_back(a[i].second);
	sort(ret.begin(), ret.end());
	return ret;
}

int main() {
	freopen("people.in", "r", stdin);
	freopen("people.out", "w", stdout);
	fastInOut();
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i].first.first >> a[i].first.second;
		a[i].second = i + 1;
	}
	sort(a, a + n, comp);
	vector<int> ret = getRet();
	cout << int(ret.size()) << "\n";
	for (int i = 0; i < int(ret.size()); ++i)
		cout << ((i == 0) ? "" : " ") << ret[i];
	cout << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
