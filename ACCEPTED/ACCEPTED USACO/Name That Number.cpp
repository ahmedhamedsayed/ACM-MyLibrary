/*
 ID: ahmedha4
 PROG: namenum
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

string x;
map<string, bool> dic, part;
vector<char> num[10];

void readDic() {
	fstream file;
	string in;
	file.open("dict.txt");
	while (file >> in) {
		dic[in] = 1;
		string cur = "";
		for (int i = 0; i < int(in.size()); ++i)
			cur += in[i], part[cur] = 1;
	}
	file.close();
}

void setNum() {
	int cnt = 2;
	for (char i = 'A'; i < 'Z'; ++i) {
		if (i == 'Q')
			continue;
		num[cnt].push_back(i);
		cnt += (num[cnt].size() == 3);
	}
}

bool ret;
void rec(int idx, string name) {
	if (name != "" && !part[name])
		return;
	if (idx == int(x.size())) {
		if (dic[name])
			ret = 1, cout << name << "\n";
		return;
	}
	int cur = x[idx] - '0';
	for (int i = 0; i < 3; ++i)
		rec(idx + 1, name + num[cur][i]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("namenum.in", "rt", stdin);
	freopen("namenum.out", "wt", stdout);
#endif
	fastInOut();
	readDic(), setNum();
	ret = 0, cin >> x, rec(0, "");
	if (!ret)
		cout << "NONE\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
