#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

const int OO = 1e9;
int n, m, p, trg, cst[20][20], src[10], mn, mnCity;
pair<int, vector<int> > cstPath[20][20];
pair<int, int> save[10], ret[10];

void init() {
	mn = 1e9, mnCity = 1e9;
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			cst[i][j] = OO;
			cstPath[i][j].first = OO;
			cstPath[i][j].second.clear();
		}
	}
}

void dijkstra(int u) {
	int dist[20], par[20];
	for (int v = 0; v < n; ++v)
		dist[v] = OO, par[v] = OO;
	priority_queue<pair<int, int> > Q;
	Q.push(make_pair(0, u));
	dist[u] = 0;
	while (Q.size()) {
		int cost = -Q.top().first, cur = Q.top().second;
		Q.pop();
		for (int v = 0; v < n; ++v) {
			int newCost = cost + cst[cur][v];
			if (dist[v] > newCost || (dist[v] == newCost && par[v] > cur)) {
				dist[v] = newCost;
				Q.push(make_pair(-newCost, v));
				par[v] = cur;
			}
		}
	}
	for (int v = 0; v < n; ++v) {
		if (u == v)
			continue;
		vector<int> tmp;
		int vv = v;
		tmp.push_back(vv);
		while (par[vv] != OO) {
			tmp.push_back(par[vv]);
			vv = par[vv];
		}
		cstPath[u][v].first = dist[v];
		for (int i = int(tmp.size()) - 1; i >= 0; --i)
			cstPath[u][v].second.push_back(tmp[i]);
	}
}

int Count(int msk) {
	int cnt = 0;
	for (int i = 0; i < n; ++i)
		cnt += ((msk >> i) & 1);
	return cnt;
}

void BT(int mskJ, int mskC, int tot) {
	if (mskJ == (1 << p) - 1) {
		if (mn > tot) {
			mn = tot;
			for (int i = 0; i < p; ++i)
				ret[i] = save[i];
		} else if (mn == tot) {
			int cnt = Count(mskC);
			if (mnCity > cnt) {
				mnCity = cnt;
				for (int i = 0; i < p; ++i)
					ret[i] = save[i];
			}
		}
		return;
	}
	for (int i = 0; i < p; ++i) {
		if ((mskJ >> i) & 1)
			continue;
		pair<int, int> cpy = save[i];
		for (int j = 0; j < n; ++j) {
			if ((mskC >> j) & 1) {
				if (save[i].first > cstPath[src[i]][j].first) {
					save[i].first = cstPath[src[i]][j].first;
					save[i].second = j;
				}
			}
		}
		int nxtMskC = mskC;
		vector<int>& cur = cstPath[src[i]][save[i].second].second;
		for (int j = 0; j < int(cur.size()); ++j)
			nxtMskC |= (1 << cur[j]);
		BT((1 << i) | mskJ, nxtMskC, tot + save[i].first);
		save[i] = cpy;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int tst = 0;
	while (cin >> n && n != -1) {
		init();
		cin >> trg >> m, --trg;
		for (int i = 0; i < m; ++i) {
			int u, v, d;
			cin >> u >> v >> d, --u, --v;
			cst[u][v] = cst[v][u] = d;
		}
		for (int u = 0; u < n; ++u)
			dijkstra(u);
		cin >> p;
		for (int i = 0; i < p; ++i) {
			cin >> src[i], --src[i];
			save[i].first = cstPath[src[i]][trg].first;
			save[i].second = trg;
		}
		BT(0, 0, 0);
		int nxt[20];
		for (int i = 0; i < p; ++i) {
			vector<int> cur = cstPath[src[i]][ret[i].second].second;
			int prv = src[i];
			for (int j = 0; j < int(cur.size()); ++j)
				nxt[prv] = cur[j], prv = cur[j];
		}
		nxt[trg] = -1;
		cout << "Case " << ++tst << ": distance = " << mn << "\n";
		for (int i = 0; i < p; ++i) {
			cout << "   ";
			int cur = src[i];
			cout << (cur + 1);
			while (nxt[cur] != -1)
				cout << "-" << (nxt[cur] + 1), cur = nxt[cur];
			cout << "\n";
		}
		cout << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
