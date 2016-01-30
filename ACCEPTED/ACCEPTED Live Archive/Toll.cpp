#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

const int OO = 1e9;
int n, cst, cnt;
map<char, int> ID;
vector<int> E[100];

void init() {
	cnt = 0;
	for (char i = 'a'; i <= 'z'; ++i)
		ID[i] = cnt++;
	for (char i = 'A'; i <= 'Z'; ++i)
		ID[i] = cnt++;
	for (int i = 0; i < cnt; ++i)
		E[i].clear();
}

int calc(int c) {
	int ret = c + (c / 20);
	while ((ret - (ret / 20) - (ret % 20 != 0)) < c) {
		++ret;
	}
	return ret;
}

int dijkstra(int src, int trg) {
	int dist[100];
	for (int i = 0; i < cnt; ++i)
		dist[i] = OO;
	priority_queue<pair<int, int> > Q;
	dist[src] = cst;
	Q.push(make_pair(-cst, src));
	while (Q.size()) {
		int c = -Q.top().first, f = Q.top().second;
		Q.pop();
		if (f == trg)
			return c;
		int nxt = ((f > 25) ? (calc(c)) : (c + 1));
		for (auto t : E[f]) {
			if (dist[t] > nxt) {
				dist[t] = nxt;
				Q.push(make_pair(-nxt, t));
			}
		}
	}
	return -1;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int tst = 0;
	while (cin >> n && n != -1) {
		init();
		for (int i = 0; i < n; ++i) {
			char a, b;
			cin >> a >> b;
			int f = ID[a], t = ID[b];
			E[f].push_back(t);
			E[t].push_back(f);
		}
		char src, trg;
		cin >> cst >> src >> trg;
		cout << "Case " << ++tst << ": " << dijkstra(ID[trg], ID[src]) << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
