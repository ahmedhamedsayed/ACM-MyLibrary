#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int convert(string cur, int base) {
	while (int(cur.size()) > 0 && cur[0] == '0')
		cur.erase(0, 1);
	if (int(cur.size()) == 0)
		return 0;
	int ret = 0, pw = 1;
	for (int i = int(cur.size()) - 1; i >= 0; --i) {
		int nxt = -1;
		if (cur[i] >= '0' && cur[i] <= '9')
			nxt = (cur[i] - '0');
		else
			nxt = (cur[i] - 'a' + 10);
		if (pw > 16)
			return -1;
		ret += (nxt * pw);
		pw *= base;
		if (ret > 16)
			return -1;
	}
	return ((ret < 2) ? -1 : ret);
}

bool okAsBase(int base, string cur) {
	if (int(cur.size()) == 0)
		return 0;
	for (int i = 0; i < int(cur.size()); ++i) {
		if (cur[i] >= '0' && cur[i] <= '9') {
			if (cur[i] - '0' >= base)
				return 0;
		} else if (cur[i] >= 'a' && cur[i] <= 'f') {
			if (cur[i] - 'a' + 10 >= base)
				return 0;
		} else
			return 0;
	}
	return 1;
}

bool check(string &n) {
	int sz = n.size(), i = 0, base = 10;
	string cur = "";
	while (i < sz && n[i] != '#')
		cur += n[i++];
	if (!okAsBase(base, cur))
		return 0;
	while (i < sz) {
		if (n[i] != '#')
			return 0;
		base = convert(cur, base);
		if (base == -1)
			return 0;
		++i, cur = "";
		while (i < sz && n[i] != '#')
			cur += n[i++];
		if (i == sz)
			return 0;
		++i;
		if (!okAsBase(base, cur))
			return 0;
	}
	return 1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	fastInOut();
	int t;
	string n;
	cin >> t;
	while (t--) {
		cin >> n;
		cout << (check(n) ? "yes\n" : "no\n");
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
