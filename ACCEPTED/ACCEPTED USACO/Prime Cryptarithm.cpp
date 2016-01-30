/*
 ID: ahmedha4
 PROG: crypt1
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

int n, a[10];

bool check(int num, int sz) {
	int cnt = 0;
	while (num != 0) {
		bool found = 0;
		int cur = num % 10;
		for (int j = 0; j < n; ++j)
			if (cur == a[j]) {
				found = 1;
				break;
			}
		if (!found)
			return 0;
		++cnt, num /= 10;
	}
	return (cnt == sz);
}

bool getRet(int num1, int num2) {
	bool ret1 = check(num1, 3);
	bool ret2 = check(num2, 2);
	bool ret3 = check(num1 * (num2 % 10), 3);
	bool ret4 = check(num1 * (num2 / 10), 3);
	bool ret5 = check(num1 * num2, 4);
	return ret1 & ret2 & ret3 & ret4 & ret5;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("crypt1.in", "rt", stdin);
	freopen("crypt1.out", "wt", stdout);
#endif
	fastInOut();
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	int tot = 0;
	for (int i = 100; i <= 999; ++i)
		for (int j = 10; j <= 99; ++j)
			if (getRet(i, j))
				tot++;
	cout << tot << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
