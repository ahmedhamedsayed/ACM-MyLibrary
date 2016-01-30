/*
 ID: ahmedha4
 PROG: transform
 LANG: C++
 */
#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n;

vector<string> rotate90(vector<string> b) {
	vector<string> ret(n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			ret[i] = b[j][i] + ret[i];
	return ret;
}

vector<string> reflact(vector<string> b) {
	for (int i = 0; i < n; ++i)
		for (int j = 0; 2 * j < n; ++j)
			swap(b[i][j], b[i][n - j - 1]);
	return b;
}

bool comp(vector<string> b, vector<string> a) {
	for (int i = 0; i < n; ++i)
		if (b[i] != a[i])
			return 0;
	return 1;
}

bool print(vector<string> ret, vector<string> a, int inc) {
	for (int i = 0; i < 3; ++i) {
		ret = rotate90(ret);
		if (comp(ret, a)) {
			cout << min(5, i + inc) << "\n";
			return 1;
		}
	}
	return 0;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("transform.in", "rt", stdin);
	freopen("transform.out", "wt", stdout);
#endif
	fastInOut();
	cin >> n;
	vector<string> b(n), a(n), ret(n);
	for (int i = 0; i < n; ++i)
		cin >> b[i];
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	ret = b;
	if (print(ret, a, 1))
		return 0;
	ret = reflact(b);
	if (comp(ret, a)) {
		cout << 4 << "\n";
		return 0;
	}
	if (print(ret, a, 5))
		return 0;
	if (comp(b, a)) {
		cout << 6 << "\n";
		return 0;
	}
	cout << 7 << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
