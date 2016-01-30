#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n, R[101], C[101];
char Dir[101], G[11][11];
pair<int, string> words[101];
set<int> ret;

void init() {
	ret.clear();
	for (int i = 1; i <= 10; ++i)
		for (int j = 1; j <= 10; ++j)
			G[i][j] = '-';
}

bool Find(string &word) {
	int st = 0, ed = n, sz = word.size();
	while (st <= ed) {
		int md = (st + ed) / 2;
		pair<int, string> &cur = words[md];
		if (cur.first < sz)
			st = md + 1;
		else if (cur.first > sz)
			ed = md - 1;
		else if (cur.second == word)
			return 1;
		else if (cur.second < word)
			st = md + 1;
		else
			ed = md - 1;
	}
	return 0;
}

bool check(int &idxPlc, int &idxWrd) {
	int &sz = words[idxWrd].first;
	int &r = R[idxPlc], &c = C[idxPlc];
	string cur = words[idxWrd].second;
	if (Dir[idxPlc] == 'D') {
		if (10 - r + 1 < sz)
			return 0;
		int rr, i;
		for (rr = r, i = 0; i < sz; ++rr, ++i) {
			if (G[rr][c] != '-' && G[rr][c] != cur[i])
				return 0;
		}
	} else if (Dir[idxPlc] == 'A') {
		if (10 - c + 1 < sz)
			return 0;
		int cc, i;
		for (cc = c, i = 0; cc <= 10 && i < sz; ++cc, ++i) {
			if (G[r][cc] != '-' && G[r][cc] != cur[i])
				return 0;
		}
	}
	return 1;
}

string put(int &idxPlc, int &idxWrd) {
	int &sz = words[idxWrd].first;
	int &r = R[idxPlc], &c = C[idxPlc];
	string old;
	old.resize(sz);
	if (Dir[idxPlc] == 'D')
		for (int rr = r, i = 0; rr <= 10 && i < sz; ++rr, ++i) {
			old[i] = G[rr][c];
			G[rr][c] = words[idxWrd].second[i];
		}
	else if (Dir[idxPlc] == 'A')
		for (int cc = c, i = 0; cc <= 10 && i < sz; ++cc, ++i) {
			old[i] = G[r][cc];
			G[r][cc] = words[idxWrd].second[i];
		}
	return old;
}

void unDo(int &idxPlc, int &idxWrd, string &old) {
	int &sz = words[idxWrd].first;
	int &r = R[idxPlc], &c = C[idxPlc];
	if (Dir[idxPlc] == 'D')
		for (int rr = r, i = 0; rr <= 10 && i < sz; ++rr, ++i)
			G[rr][c] = old[i];
	else if (Dir[idxPlc] == 'A')
		for (int cc = c, i = 0; cc <= 10 && i < sz; ++cc, ++i)
			G[r][cc] = old[i];
}

bool valid(int &msk, int &idxPlc) {
	for (int i = 0; i < n; ++i) {
		if (i != idxPlc && !((msk >> i) & 1))
			continue;
		int rr = R[i], cc = C[i];
		char &ddir = Dir[i];
		string cur = "";
		if (ddir == 'D')
			while (rr <= 10 && G[rr][cc] != '-')
				cur += G[rr++][cc];
		else
			while (cc <= 10 && G[rr][cc] != '-')
				cur += G[rr][cc++];
		if (!Find(cur))
			return 0;
	}
	return 1;
}

void bt(int mskPlc, int mskWrd) {
	if (mskPlc == (1 << n) - 1) {
		for (int i = 0; i <= n; ++i)
			if (!((mskWrd >> i) & 1))
				ret.insert(i);
		return;
	}
	int idx = -1, mn = 1e9;
	vector<int> mnFrom;
	for (int i = 0; i < n; ++i) {
		vector<int> from;
		if ((mskPlc >> i) & 1)
			continue;
		for (int j = 0; j <= n; ++j) {
			if ((mskWrd >> j) & 1)
				continue;
			if (check(i, j))
				from.push_back(j);
		}
		int sz = from.size();
		if (mn > sz)
			idx = i, mn = sz, mnFrom = from;
	}
	if (idx == -1)
		return;
	for (int i = 0; i < mn; ++i) {
		int &to = mnFrom[i];
		string old = put(idx, to);
		if (valid(mskPlc, idx))
			bt((1 << idx) | mskPlc, (1 << to) | mskWrd);
		unDo(idx, to, old);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int tst = 0;
	while (cin >> n, n != 0) {
		init();
		for (int i = 0; i < n; ++i) {
			cin >> R[i] >> C[i] >> Dir[i];
		}
		for (int i = 0; i <= n; ++i) {
			cin >> words[i].second;
			words[i].first = words[i].second.size();
		}
		sort(words, words + n + 1);
		bt(0, 0);
		cout << "Trial " << ++tst << ":";
		if (int(ret.size()) == 0)
			cout << " Impossible";
		else
			for (auto i : ret)
				cout << " " << words[i].second;
		cout << "\n\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
