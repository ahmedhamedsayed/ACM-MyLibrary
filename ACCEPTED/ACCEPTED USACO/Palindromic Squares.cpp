/*
 ID: ahmedha4
 PROG: palsquare
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
	freopen("palsquare.in", "rt", stdin);
	freopen("palsquare.out", "wt", stdout);
#endif
	fastInOut();
	int b;
	cin >> b;
	for (int i = 1; i <= 300; ++i) {
		string num = convert(i, b), sqr = convert(i * i, b);
		if (isPalind(sqr))
			cout << num << " " << sqr << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
