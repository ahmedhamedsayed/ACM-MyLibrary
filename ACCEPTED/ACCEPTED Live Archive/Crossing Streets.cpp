#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

struct sgm {
	int x1, y1, x2, y2;
};

const int OO = 1e9;
set<int> xs, ys;
map<int, int> nx, ny;
int n, x, y;
sgm sgms[510];

void init() {
	x = 0, y = 0;
	xs.clear(), ys.clear();
	nx.clear(), ny.clear();
}

void mp() {
	for (auto curX : xs)
		nx[curX] = x++;
	for (auto curY : ys)
		ny[curY] = y++;
}

void update() {
	for (int i = 0; i < n; ++i) {
		sgms[i].x1 = nx[sgms[i].x1];
		sgms[i].y1 = ny[sgms[i].y1];
		sgms[i].x2 = nx[sgms[i].x2];
		sgms[i].y2 = ny[sgms[i].y2];
	}
}

bool onLine(int x, int y) {
	for (int i = 0; i < n; ++i) {
		sgm& cur = sgms[i];
		if (cur.x1 == cur.x2 && cur.x1 == x && y >= cur.y1 && y <= cur.y2)
			return 1;
		if (cur.y1 == cur.y2 && cur.y1 == y && x >= cur.x1 && x <= cur.x2)
			return 1;
	}
	return 0;
}

bool check(int i, int j) {
	return (i >= -5 && i <= x + 5 && j >= -5 && j <= y + 5);
}

int d1[] = { 0, 0, -1, 1 };
int d2[] = { -1, 1, 0, 0 };
int dijkstra(int sx, int sy, int tx, int ty) {
	int dist[500][500];
	for (int i = 0; i < 500; ++i)
		for (int j = 0; j < 500; ++j)
			dist[i][j] = OO;
	priority_queue<pair<int, pair<int, int> > > Q;
	Q.push(make_pair(0, make_pair(sx, sy)));
	dist[sx][sy] = 0;
	while (Q.size()) {
		int cst = -Q.top().first;
		int curX = Q.top().second.first, curY = Q.top().second.second;
		Q.pop();
		if (curX == tx && curY == ty)
			return cst;
		for (int k = 0; k < 4; ++k) {
			int newX = curX + d1[k], newY = curY + d2[k];
			int newCst = cst + onLine(newX, newY);
			if (check(newX, newY) && dist[newX][newY] > newCst) {
				Q.push(make_pair(-newCst, make_pair(newX, newY)));
				dist[newX][newY] = newCst;
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
	while (cin >> n && n != 0) {
		++n;
		for (int i = 0; i < n; ++i) {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			if (x1 > x2)
				swap(x1, x2);
			if (y1 > y2)
				swap(y1, y2);
			sgms[i]= {x1,y1,x2,y2};
			xs.insert(x1), xs.insert(x2);
			ys.insert(y1), ys.insert(y2);
		}
		mp();
		update();
		--n;
		int ret = dijkstra(sgms[n].x1, sgms[n].y1, sgms[n].x2, sgms[n].y2);
		cout << "City " << ++tst << "\n";
		cout << "Peter has to cross " << ret << " streets\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
