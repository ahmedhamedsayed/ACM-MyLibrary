#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

string m[10][4];

void init() {
	m[0][0] = " ", m[0][1] = " ", m[0][2] = " ", m[0][3] = " ";
	m[1][0] = ".", m[1][1] = ",", m[1][2] = "?", m[1][3] = "\"";
	m[2][0] = "a", m[2][1] = "b", m[2][2] = "c", m[2][3] = "a";
	m[3][0] = "d", m[3][1] = "e", m[3][2] = "f", m[3][3] = "d";
	m[4][0] = "g", m[4][1] = "h", m[4][2] = "i", m[4][3] = "g";
	m[5][0] = "j", m[5][1] = "k", m[5][2] = "l", m[5][3] = "j";
	m[6][0] = "m", m[6][1] = "n", m[6][2] = "o", m[6][3] = "m";
	m[7][0] = "p", m[7][1] = "q", m[7][2] = "r", m[7][3] = "s";
	m[8][0] = "t", m[8][1] = "u", m[8][2] = "v", m[8][3] = "t";
	m[9][0] = "w", m[9][1] = "x", m[9][2] = "y", m[9][3] = "z";
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	init();
	int t, l, n[100], p;
	cin >> t;
	while (t--) {
		cin >> l;
		string ret = "";
		for (int i = 0; i < l; ++i)
			cin >> n[i];
		for (int i = 0; i < l; ++i)
			cin >> p, ret += m[n[i]][p - 1];
		cout << ret << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
