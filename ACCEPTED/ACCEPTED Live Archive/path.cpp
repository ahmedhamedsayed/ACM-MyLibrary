#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

double pi = 3.1415926535897932384626433832795;
const int N = 100000;
int n;
pair<int, int> pnts[2 * N];
map<pair<int, int>, double> dis;

double calcDis(pair<double, double> pnt1, pair<double, double> pnt2) {
	double prt1 = pnt1.first - pnt2.first, prt2 = pnt1.second - pnt2.second;
	return sqrt(prt1 * prt1 + prt2 * prt2);
}

double calcAng(pair<double, double> pnt1, pair<double, double> pnt2) {
	return atan2(pnt2.second - pnt1.second, pnt2.first - pnt1.first);
}

int solve(int u, double prvAng, double totDis) {
	int st = (u - 1 + n) % n;
	if (st == 0)
		return -1;
	double ang = pi;
	for (int v = st; v >= 0; --v) {
		double nxtAng = calcAng(pnts[u], pnts[v]);
		if (nxtAng <= prvAng)
			return v;
		else if (nxtAng <= ang)
			ang = nxtAng, dis[pnts[v]] = calcDis(pnts[u], pnts[v]) + totDis;
		else
			v = solve(v + 1, ang, totDis + calcDis(pnts[u], pnts[v + 1])) + 1;
	}
	return -1;
}

pair<int, int> calcPnt(pair<int, int> pnt1, pair<int, int> pnt2, int len) {
	pair<int, int> ret;
	if (pnt1.first == pnt2.first)
		ret = make_pair(pnt1.first, pnt1.second + (pnt1.second < pnt2.second ? 1 : -1) * len);
	else if (pnt1.second == pnt2.second)
		ret = make_pair(pnt1.first + (pnt1.first < pnt2.first ? 1 : -1) * len, pnt1.second);
	return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	fastInOut();
	int t, m, x, y;
	vector<pair<int, int> > tmp, fin;
	vector<int> edg[N];
	cin >> t;
	while (t--) {
		tmp.clear(), dis.clear();
		for (int i = 0; i < N; ++i)
			edg[i].clear();
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> x >> y, tmp.push_back(make_pair(x, y));
		cin >> m;
		for (int i = 0; i < m; ++i)
			cin >> x >> y, edg[x].push_back(y);
		int idx = 0;
		for (int i = 0; i < n; ++i) {
			int j = (i + 1) % n;
			pnts[idx++] = tmp[i], sort(edg[i].begin(), edg[i].end());
			for (int k = 0; k < int(edg[i].size()); ++k)
				pnts[idx] = calcPnt(tmp[i], tmp[j], edg[i][k]), fin.push_back(pnts[idx++]);
		}
		n = idx, solve(0, -1.0, 0.0);
		double ret = 0.0;
		for (int i = 0; i < int(fin.size()); ++i)
			ret += dis[fin[i]];
		cout << fixed << setprecision(1) << ret << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
