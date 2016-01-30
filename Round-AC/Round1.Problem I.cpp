#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

struct Problem {
	int I, A, L, O;
};

struct Team {
	int T, Z, V, C;
};

struct Rank {
	int tmNum, num, penalty;

	bool operator<(const Rank r) const {
		if (num == r.num)
			return penalty <= r.penalty;
		return num > r.num;
	}
};

const int probSz = 50, teamSz = 50;
int m, n, t, l, mnRank, ret;
Problem Pb[probSz];
Team Tm[teamSz];

int Ceil(int x, int y) {
	return (x + y - 1) / y;
}

vector<Rank> Sort(vector<Rank> cur) {
	int sz = cur.size();
	for (int i = 0; i < sz - 1; ++i) {
		int mn = i;
		for (int j = i + 1; j < sz; ++j) {
			if (cur[mn] < cur[j])
				continue;
			mn = j;
		}
		swap(cur[i], cur[mn]);
	}
	return cur;
}

void check(int selProb) {
	vector<Rank> finRank(t);
	for (int j = 0; j < t; ++j) {
		vector<pair<int, int> > solve;
		for (int i = 0; i < m; ++i) {
			if ((selProb >> i) & 1) {
				int prt1, prt2, prt3;
				if (Tm[j].T + Tm[j].C > Pb[i].I - Pb[i].O) {
					prt1 = Ceil(Pb[i].I, Pb[i].O);
					prt2 = max(Ceil(Pb[i].A, Tm[j].C), 5);
					int E = prt1 + prt2;

					prt1 = max(Pb[i].I - Tm[j].T, 0);
					prt2 = Ceil(Pb[i].A, Tm[j].Z + Tm[j].C);
					prt3 = Ceil(Pb[i].L, Tm[j].V);
					int A = prt1 + prt2 + prt3;
					solve.push_back(make_pair(E, A));
				}
			}
		}
		sort(solve.begin(), solve.end());
		int tot = 0, pen = 0, curTm = 0;
		for (int i = 0; i < int(solve.size()); ++i) {
			int nxt = curTm + solve[i].second;
			if (nxt <= l) {
				curTm += solve[i].second;
				pen += curTm;
				++tot;
			} else
				break;
		}
		finRank[j].tmNum = j + 1;
		finRank[j].num = tot;
		finRank[j].penalty = pen;
	}
	finRank = Sort(finRank);
	int curRank = 1, actRank = 1;
	for (int i = 0; i < t; ++i) {
		if (i != 0) {
			bool cond1 = (finRank[i].num != finRank[i - 1].num);
			bool cond2 = (finRank[i].penalty != finRank[i - 1].penalty);
			if (cond1 || cond2)
				curRank = actRank;
		}
		if (finRank[i].tmNum == 1) {
			if (mnRank > curRank) {
				mnRank = curRank;
				ret = selProb;
			}
			break;
		}
		++actRank;
	}
}

void rec(int idx, int msk, int sz) {
	if (idx == m) {
		if (sz == n)
			check(msk);
		return;
	}
	rec(idx + 1, msk, sz);
	rec(idx + 1, (1 << idx) | msk, sz + 1);
}

int main() {
	freopen("unfair.in", "r", stdin);
	freopen("unfair.out", "w", stdout);
	fastInOut();
	cin >> m >> n >> t >> l;
	for (int i = 0; i < m; ++i)
		cin >> Pb[i].I >> Pb[i].A >> Pb[i].L >> Pb[i].O;
	for (int i = 0; i < t; ++i)
		cin >> Tm[i].T >> Tm[i].Z >> Tm[i].V >> Tm[i].C;
	mnRank = 1e9, ret = 0;
	rec(0, 0, 0);
	bool enter = 0;
	for (int i = 0; i < m; ++i) {
		if ((ret >> i) & 1) {
			cout << ((enter) ? " " : "") << i + 1;
			enter = 1;
		}
	}
	cout << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
