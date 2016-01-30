#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

const int mod = 1000000007;
char a[52], b[52];
int sz, st1, st2, lim;
int memo[2][2][17][17][17][52];
int vs[2][2][17][17][17][52], ID;

int solve(bool prvA, bool prvB, int cnt1, int cnt2, int cnt3, int idx) {
	if (cnt1 > 16 || cnt2 > 16 || cnt3 > 16)
		return 0;
	int mx = max(cnt1, max(cnt2, cnt3));
	int rem = (3 * mx) - (cnt1 + cnt2 + cnt3);
	if (sz - idx < rem)
		return 0;
	if (idx == sz)
		return (cnt1 >= 1 && cnt1 == cnt2 && cnt2 == cnt3);
	int& ret = memo[prvA][prvB][cnt1][cnt2][cnt3][idx];
	int& check = vs[prvA][prvB][cnt1][cnt2][cnt3][idx];
	if ((prvA && prvB && check) || check == ID)
		return ret;
	check = ID;
	ret = 0;
	int cur1 = (idx - st1 >= 0) ? (a[idx - st1] - '0') : 0;
	int cur2 = (idx - st2 >= 0) ? (b[idx - st2] - '0') : 0;
	for (int i = 0; i <= 9; ++i) {
		if (i < cur1 && !prvA)
			continue;
		if (i > cur2 && !prvB)
			continue;
		bool curA = !(i == cur1 && !prvA);
		bool curB = !(i == cur2 && !prvB);
		int nxt1 = cnt1 + (i == 3);
		int nxt2 = cnt2 + (i == 6);
		int nxt3 = cnt3 + (i == 9);
		ret = (ret + solve(curA, curB, nxt1, nxt2, nxt3, idx + 1)) % mod;
	}
	return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int t;
	cin >> t;
	while (t--) {
		cin >> a >> b;
		sz = 51;
		st1 = sz - strlen(a);
		st2 = sz - strlen(b);
		++ID;
		cout << solve(0, 0, 0, 0, 0, 0) << endl;
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
