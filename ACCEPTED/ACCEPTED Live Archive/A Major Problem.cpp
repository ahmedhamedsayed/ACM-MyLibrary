#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

vector<string> notes[12];
vector<pair<string, string> > ret;
int d[] = { 2, 2, 1, 2, 2, 2, 1 };

void init() {
	notes[0]= {"C", "B#"};
	notes[1]= {"C#", "Db"};
	notes[2]= {"D"};
	notes[3]= {"D#", "Eb"};
	notes[4]= {"E", "Fb"};
	notes[5]= {"F", "E#"};
	notes[6]= {"F#", "Gb"};
	notes[7]= {"G"};
	notes[8]= {"G#", "Ab"};
	notes[9]= {"A"};
	notes[10]= {"A#", "Bb"};
	notes[11]= {"B", "Cb"};
}

int Find(string cur) {
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < int(notes[i].size()); ++j) {
			if (cur == notes[i][j])
				return i;
		}
	}
	return -1;
}

bool check(string cur, char other) {
	int sz = cur.size();
	return (sz == 2 && cur[sz - 1] == other);
}

map<char, bool> vis;
int ID;
vector<vector<string> > seq[2];
vector<string> path;
bool isValid(int idxD, string src, string trg, bool s, bool f) {
	if (idxD == 7) {
		if (src == trg) {
			seq[ID].push_back(path);
			return 1;
		}
		return 0;
	}
	int idx = Find(src);
	if (idx == -1)
		return 0;
	int lim = (idx + d[idxD]) % 12;
	bool ret = 0;
	for (int i = 0; i < int(notes[lim].size()); ++i) {
		bool S = check(notes[lim][i], '#');
		bool F = check(notes[lim][i], 'b');
		if (!vis[notes[lim][i][0]] && !((s | S) & (f | F))) {
			vis[notes[lim][i][0]] = 1;
			path.push_back(notes[lim][i]);
			ret |= isValid(idxD + 1, notes[lim][i], trg, (s | S), (f | F));
			path.pop_back();
			vis[notes[lim][i][0]] = 0;
		}
	}
	return ret;
}

bool exe(string cur) {
	vis.clear();
	path.clear();
	seq[ID].clear();
	bool s1 = check(cur, '#');
	bool f1 = check(cur, 'b');
	bool ret = isValid(0, cur, cur, s1, f1);
	++ID;
	return ret;
}

string getRet(string cur) {
	for (int i = 0; i < int(seq[0].size()); ++i) {
		for (int j = 0; j < int(seq[0][i].size()); ++j) {
			if (seq[0][i][j] == cur) {
				return seq[1][0][j];
			}
		}
	}
	return "null";
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	string src, trg, cur;
	init();
	bool enter = 0;
	while (cin >> src && src != "*") {
		if (enter)
			cout << "\n";
		enter = 1;
		cin >> trg;
		ret.clear(), ID = 0;
		bool v1 = exe(src), v2 = exe(trg);
		while (cin >> cur && cur != "*") {
			if (v1 && v2) {
				ret.push_back(make_pair(cur, getRet(cur)));
			}
		}
		if (!v1) {
			cout << "Key of " << src << " is not a valid major key\n";
		} else if (!v2) {
			cout << "Key of " << trg << " is not a valid major key\n";
		} else {
			cout << "Transposing from " << src << " to " << trg << ":\n";
			for (int i = 0; i < int(ret.size()); ++i) {
				cout << "  ";
				if (ret[i].second == "null") {
					cout << ret[i].first << " is not a valid note in the "
							<< src << " major scale\n";
				} else {
					cout << ret[i].first << " transposes to " << ret[i].second
							<< "\n";
				}
			}
		}
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
