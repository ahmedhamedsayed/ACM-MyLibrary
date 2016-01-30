#include<iostream>
#include<vector>
#include<queue>
#include<stdio.h>

using namespace std;

#define OO 1e9

typedef long long ll;
typedef unsigned long long ull;

vector<int> head;
vector<pair<int, int> > edge;
vector<int> len;
int lst, T, N;

void setAll() {
	lst = 0;
	head.resize(N);
	for (int i = 0; i < N; ++i)
		head[i] = -1;
	edge.resize(2 * T);
	len.resize(2 * T);
}

void addEdge(int f, int t, int d) {
	edge[lst].second = head[f];
	head[f] = lst;
	edge[lst].first = t;
	len[lst++] = d;
}

int dijkstra(int src, int tar) {
	vector<int> dist(N);
	for (int i = 0; i < N; ++i)
		dist[i] = OO;
	priority_queue<pair<int, int> > Q;
	dist[src] = 0;
	Q.push(make_pair(0, src));
	while (Q.size()) {
		int cur = Q.top().second, dis = -Q.top().first;
		Q.pop();
		if (cur == tar)
			return dis;
		for (int i = head[cur]; i != -1; i = edge[i].second) {
			int nxt = edge[i].first, newDis = dis + len[i];
			if (newDis < dist[nxt]) {
				dist[nxt] = newDis;
				Q.push(make_pair(-newDis, nxt));
			}
		}
	}
	return OO;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	int f, t, d;
	cin >> T >> N;
	setAll();
	for (int i = 0; i < T; ++i) {
		cin >> f >> t >> d, --f, --t;
		addEdge(f, t, d), addEdge(t, f, d);
	}
	cout << dijkstra(0, N - 1) << "\n";
	return 0;
}
