#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

struct hole {
	double x, y, z, r;
};

int n, tst;
hole holes[102];

double getDist(int i, int j) {
	double dif1 = holes[i].x - holes[j].x;
	double dif2 = holes[i].y - holes[j].y;
	double dif3 = holes[i].z - holes[j].z;
	double prt = (dif1 * dif1) + (dif2 * dif2) + (dif3 * dif3);
	double ret = sqrt(prt) - (holes[i].r + holes[j].r);
	return ret;
}

int floyd() {
	double dist[102][102];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == j)
				dist[i][j] = 0;
			else
				dist[i][j] = max(0.0, getDist(i, j));
		}
	}
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
	return round(dist[0][n - 1] * 10.0);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	double x, y, z, r;
	while (cin >> n && n != -1) {
		for (int i = 1; i <= n; ++i) {
			cin >> x >> y >> z >> r;
			holes[i]= {x,y,z,r};
		}
		cin >> x >> y >> z;
		holes[0] = {x,y,z,0};
		cin >> x >> y >> z;
		holes[n+1] = {x,y,z,0};
		n += 2;
		cout << "Cheese " << ++tst << ": Travel time = " << floyd() << " sec\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
