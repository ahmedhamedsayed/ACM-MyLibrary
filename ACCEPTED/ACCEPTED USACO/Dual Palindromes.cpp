/*
 ID: ahmedha4
 PROG: dualpal
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

bool isPalind(string num) {
	int sz = num.size();
	for (int i = 0; i < sz; ++i)
		if (num[i] != num[sz - i - 1])
			return 0;
	return 1;
}

string inCode(int code) {
	if (code <= 9)
		return string(1, code + '0');
	return string(1, code - 10 + 'A');
}

string convert(int num, int base) {
	if (num == 0)
		return "";
	return convert(num / base, base) + inCode(num % base);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("dualpal.in", "rt", stdin);
	freopen("dualpal.out", "wt", stdout);
#endif
	fastInOut();
	int n, s;
	cin >> n >> s;
	while (n != 0 && ++s) {
		int ret = 0;
		for (int i = 2; i <= 10; ++i)
			if (isPalind(convert(s, i))) {
				++ret;
				if (ret == 2)
					break;
			}
		if (ret == 2)
			cout << s << "\n", --n;
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
