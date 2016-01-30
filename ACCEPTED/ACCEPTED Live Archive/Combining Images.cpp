#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

string c[2];
map<char, string> HexToBin;
int sz[2], isOne[2][500], RSZ, isRetOne[500];
vector<int> G[2][500], ret[500];

void init() {
	HexToBin.clear();
	HexToBin['0'] = "0000", HexToBin['1'] = "0001";
	HexToBin['2'] = "0010", HexToBin['3'] = "0011";
	HexToBin['4'] = "0100", HexToBin['5'] = "0101";
	HexToBin['6'] = "0110", HexToBin['7'] = "0111";
	HexToBin['8'] = "1000", HexToBin['9'] = "1001";
	HexToBin['A'] = "1010", HexToBin['B'] = "1011";
	HexToBin['C'] = "1100", HexToBin['D'] = "1101";
	HexToBin['E'] = "1110", HexToBin['F'] = "1111";
	RSZ = 0;
	memset(isOne, -1, sizeof isOne);
	memset(isRetOne, -1, sizeof isRetOne);
	for (int i = 0; i < 500; ++i)
		ret[i].clear();
	for (int i = 0; i < 2; ++i) {
		sz[i] = 0;
		for (int j = 0; j < 500; ++j)
			G[i][j].clear();
	}
}

char Find(string bin) {
	for (auto it : HexToBin) {
		if (it.second == bin)
			return it.first;
	}
	return '?';
}

string convertToBin(string hex) {
	string ret = "";
	for (int i = 0; i < int(hex.size()); ++i)
		ret += HexToBin[hex[i]];
	while (int(ret.size()) != 0 && ret[0] == '0')
		ret = ret.substr(1);
	return ret.substr(1);
}

int buildGraph(int idx, int num) {
	if (c[num][idx] == '1') {
		isOne[num][sz[num]] = (c[num][idx + 1] == '1');
		return idx + 2;
	} else {
		int cur = sz[num], prv = idx + 1;
		for (int i = 0; i < 4; ++i) {
			G[num][cur].push_back(++sz[num]);
			prv = buildGraph(prv, num);
		}
		return prv;
	}
}

void copy(int cur, int num) {
	if (isOne[num][cur] != -1) {
		isRetOne[RSZ] = isOne[num][cur];
		return;
	}
	int c = RSZ;
	for (int i = 0; i < 4; ++i) {
		ret[c].push_back(++RSZ);
		copy(G[num][cur][i], num);
	}
}

void traverse(int cur1, int cur2) {
	if (isOne[0][cur1] != -1 && isOne[1][cur2] != -1) {
		isRetOne[RSZ] = isOne[0][cur1] & isOne[1][cur2];
	} else if (isOne[0][cur1] != -1) {
		if (isOne[0][cur1] == 0)
			isRetOne[RSZ] = 0;
		else
			copy(cur2, 1);
	} else if (isOne[1][cur2] != -1) {
		if (isOne[1][cur2] == 0)
			isRetOne[RSZ] = 0;
		else
			copy(cur1, 0);
	} else {
		int cur = RSZ;
		for (int i = 0; i < 4; ++i) {
			ret[cur].push_back(++RSZ);
			traverse(G[0][cur1][i], G[1][cur2][i]);
		}
	}
}

void updateRet(int cur) {
	if (isRetOne[cur] != -1)
		return;
	for (int i = 0; i < 4; ++i)
		updateRet(ret[cur][i]);
	bool findOne = 0, findZro = 0, findNll = 0;
	for (int i = 0; i < 4; ++i) {
		findOne |= (isRetOne[ret[cur][i]] == 1);
		findZro |= (isRetOne[ret[cur][i]] == 0);
		findNll |= (isRetOne[ret[cur][i]] == -1);
	}
	if (findOne && !findZro && !findNll)
		isRetOne[cur] = 1;
	else if (!findOne && findZro && !findNll)
		isRetOne[cur] = 0;
}

string getRet(int cur) {
	if (isRetOne[cur] != -1)
		return ((!isRetOne[cur]) ? "10" : "11");
	string finalRet = "0";
	for (int i = 0; i < 4; ++i)
		finalRet += getRet(ret[cur][i]);
	return finalRet;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	string a, b;
	int tst = 0;
	bool enter = 0;
	while (cin >> a >> b && a != "0" && b != "0") {
		if (enter)
			cout << "\n";
		enter = 1;
		init();
		c[0] = convertToBin(a), buildGraph(0, 0);
		c[1] = convertToBin(b), buildGraph(0, 1);
		traverse(0, 0);
		updateRet(0);
		string finalRet = "1" + getRet(0);
		while (int(finalRet.size()) % 4 != 0)
			finalRet = "0" + finalRet;
		string out = "";
		while (int(finalRet.size()) != 0) {
			out += Find(finalRet.substr(0, 4));
			finalRet = finalRet.substr(4);
		}
		cout << "Image " << ++tst << ":\n" << out << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
