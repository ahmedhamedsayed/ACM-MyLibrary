#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int mth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool IsLeap(int year) {
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

struct data {
	int day, month, year;

	data prvData() {
		int inc = IsLeap(year) * (month == 3);
		if (day > 1)
			return data { day - 1, month, year };
		if (month > 1)
			return data { mth[month - 1] + inc, month - 1, year };
		return data { mth[12], 12, year - 1 };
	}

	data nxtData() {
		int inc = IsLeap(year) * (month == 2);
		if (day < mth[month] + inc)
			return data { day + 1, month, year };
		if (month < 12)
			return data { 1, month + 1, year };
		return data { 1, 1, year + 1 };
	}

	void print() {
		cout << month << "/" << day << "/" << year;
	}
};

bool operator<(const data& d1, const data& d2) {
	if (d1.year != d2.year)
		return (d1.year < d2.year);
	if (d1.month != d2.month)
		return (d1.month < d2.month);
	return (d1.day < d2.day);
}

bool operator<=(const data& d1, const data& d2) {
	if (d1.year != d2.year)
		return (d1.year < d2.year);
	if (d1.month != d2.month)
		return (d1.month < d2.month);
	return (d1.day <= d2.day);
}

bool operator==(const data& d1, const data& d2) {
	bool cond1 = (d1.day == d2.day);
	bool cond2 = (d1.month == d2.month);
	bool cond3 = (d1.year == d2.year);
	return (cond1 && cond2 && cond3);
}

data FetchData(string input) {
	int year = 0, month = 0, day = 0;
	for (int i = 0; i < 4; ++i)
		year *= 10, year += (input[i] - '0');
	for (int i = 4; i < 6; ++i)
		month *= 10, month += (input[i] - '0');
	for (int i = 6; i < 8; ++i)
		day *= 10, day += (input[i] - '0');
	return data { day, month, year };
}

int n, m;
pair<data, data> old[100];
vector<pair<data, data> > cur;

void Init() {
	cur.clear();
}

void Felter(data st, data ed) {
	if (ed < st)
		return;
	for (int i = 0; i < n; ++i) {
		if (old[i].second < st || ed < old[i].first)
			continue;
		if (old[i].first <= st && ed <= old[i].second) {
			return;
		} else if (st <= old[i].first && old[i].second <= ed) {
			Felter(st, old[i].first.prvData());
			Felter(old[i].second.nxtData(), ed);
			return;
		} else if (st <= old[i].first && ed <= old[i].second) {
			Felter(st, old[i].first.prvData());
			return;
		} else if (old[i].first <= st && old[i].second <= ed) {
			Felter(old[i].second.nxtData(), ed);
			return;
		}
	}
	cur.push_back(make_pair(st, ed));
}

vector<pair<data, data> > Merge() {
	vector<pair<data, data> > ret;
	if (int(cur.size()) == 0)
		return ret;
	sort(cur.begin(), cur.end());
	data prvSt = cur[0].first, prvEd = cur[0].second;
	for (int i = 1; i < int(cur.size()); ++i) {
		data curSt = cur[i].first, curEd = cur[i].second;
		if (curEd <= prvEd)
			continue;
		if (prvEd < curSt) {
			ret.push_back(make_pair(prvSt, prvEd));
			prvSt = curSt, prvEd = curEd;
		} else if (curSt <= prvEd)
			prvEd = curEd;
	}
	ret.push_back(make_pair(prvSt, prvEd));
	sort(ret.begin(), ret.end());
	for (int i = 0; i < int(ret.size()) - 1; ++i) {
		if (ret[i].second.nxtData() == ret[i + 1].first) {
			ret[i].second = ret[i + 1].second;
			ret.erase(ret.begin() + i + 1);
			--i;
		}
	}
	return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int tst = 1;
	while (cin >> n >> m && (n != 0 || m != 0)) {
		if (tst > 1)
			cout << "\n";
		Init();
		string in1, in2;
		for (int i = 0; i < n; ++i) {
			cin >> in1 >> in2;
			old[i] = make_pair(FetchData(in1), FetchData(in2));
		}
		for (int i = 0; i < m; ++i) {
			cin >> in1 >> in2;
			Felter(FetchData(in1), FetchData(in2));
		}
		vector<pair<data, data> > ret = Merge();
		cout << "Case " << tst++ << ":\n";
		for (int i = 0; i < int(ret.size()); ++i) {
			cout << "    ";
			if (ret[i].first == ret[i].second) {
				ret[i].first.print();
			} else {
				ret[i].first.print();
				cout << " to ";
				ret[i].second.print();
			}
			cout << "\n";
		}
		if (int(ret.size()) == 0)
			cout << "    No additional quotes are required.\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
