#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

vector<pair<int, int> > e[26];
vector<pair<int, int> > ret;
int n, inOut[2][26];

void init() {
	ret.clear();
	for (int i = 1; i <= 25; ++i)
		e[i].clear();
	memset(inOut, 0, sizeof inOut);
}

void buildGraph() {
	int from, k;
	for (int i = 0; i < n; ++i) {
		cin >> from >> k;
		for (int j = 0; j < k; ++j) {
			int to, num;
			cin >> to >> num;
			e[from].push_back(make_pair(to, num));
		}
	}
}

void setConfig() {
	int city;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> city;
			inOut[i][city] = j;
		}
	}
}

int calcLoad() {
	int totLoad = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < int(e[i].size()); ++j) {
			int to = e[i][j].first;
			int num = e[i][j].second;
			int dis = abs(inOut[0][i] - inOut[1][to]) + 1;
			totLoad += (num * dis);
		}
	}
	return totLoad;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	while (cin >> n && n != 0) {
		init();
		buildGraph();
		int c;
		while (cin >> c && c != 0) {
			setConfig();
			ret.push_back(make_pair(calcLoad(), c));
		}
		sort(ret.begin(), ret.end());
		printf("Configuration Load\n");
		for (int i = 0; i < int(ret.size()); ++i)
			printf("%5d         %d\n", ret[i].second, ret[i].first);
	}
	return 0;
}
