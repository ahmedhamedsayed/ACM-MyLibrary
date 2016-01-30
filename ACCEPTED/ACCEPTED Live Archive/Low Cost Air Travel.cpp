#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

#define F first
#define S second

const int OO = 1e9;
int n, cnt;
vector<pair<pair<int, int>, vector<int> > > edge[200];
map<int, int> ID;

void init() {
	cnt = 0, ID.clear();
	for (int i = 0; i < 200; ++i)
		edge[i].clear();
}

int maping(int cur) {
	if (ID.find(cur) == ID.end())
		ID[cur] = cnt++;
	return ID[cur];
}

pair<int, vector<int> > dijkstra(int src, vector<int> trg) {
	int sz = trg.size();
	int dist[200][200];
	for (int i = 0; i < 200; ++i)
		for (int j = 0; j < 200; ++j)
			dist[i][j] = OO;
	dist[src][0] = 0;
	priority_queue<pair<pair<int, int>, pair<int, vector<int>> > > Q;
	Q.push(make_pair(make_pair(0, 0), make_pair(src, vector<int>())));
	while (Q.size()) {
		int cst = -Q.top().F.F, nxt = -Q.top().F.S, cur = Q.top().S.F;
		vector<int> curPath = Q.top().S.S;
		Q.pop();
		if (nxt == sz)
			return make_pair(cst, curPath);
		for (int i = 0; i < int(edge[cur].size()); ++i) {
			int nxtCst = cst + edge[cur][i].F.F, nxtIdx = nxt;
			vector<int> &to = edge[cur][i].S;
			for (int j = 0; j < int(to.size()); ++j) {
				nxtIdx += (trg[nxtIdx] == to[j]);
				if (dist[to[j]][nxtIdx] > nxtCst) {
					dist[to[j]][nxtIdx] = nxtCst;
					curPath.push_back(edge[cur][i].F.S);
					pair<int, int> nxt1 = make_pair(-nxtCst, -nxtIdx);
					pair<int, vector<int> > nxt2 = make_pair(to[j], curPath);
					Q.push(make_pair(nxt1, nxt2));
					curPath.pop_back();
				}
			}
		}
	}
	return make_pair(-1, vector<int>());
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("LCAT.txt", "rt", stdin);
#endif
	fastInOut();
	int cse = 1;
	while (cin >> n, n != 0) {
		init();
		for (int i = 0; i < n; ++i) {
			int cst, cty, s, d;
			vector<int> nxt;
			cin >> cst >> cty >> s, s = maping(s);
			for (int j = 1; j < cty; ++j)
				cin >> d, d = maping(d), nxt.push_back(d);
			edge[s].push_back(make_pair(make_pair(cst, i + 1), nxt));
		}
		int q;
		cin >> q;
		for (int trp = 1; trp <= q; ++trp) {
			int cty, s, d;
			cin >> cty >> s, s = ID[s];
			vector<int> nxt;
			for (int j = 1; j < cty; ++j)
				cin >> d, d = ID[d], nxt.push_back(d);
			pair<int, vector<int> > ret = dijkstra(s, nxt);
			cout << "Case " << cse << ", Trip " << trp << ": Cost = ";
			cout << ret.F << "\n  Tickets used:";
			for (int j = 0; j < int(ret.S.size()); ++j)
				cout << " " << ret.S[j];
			cout << endl;
		}
		++cse;
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
