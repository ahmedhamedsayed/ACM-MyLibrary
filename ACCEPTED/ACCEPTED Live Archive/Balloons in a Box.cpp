#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

#define mp(x,y) make_pair((x),(y))

void fastInOut();

struct point {
	double x, y, z;

	double dist(point p) {
		double dx = x - p.x;
		double dy = y - p.y;
		double dz = z - p.z;
		return sqrt((dx * dx) + (dy * dy) + (dz * dz));
	}

	bool operator<(const point& p) const {
		return mp(x, mp(y, x)) < mp(p.x, mp(p.y, p.z));
	}
};

const double eps = 1e-9;
int n, sz;
point st, ed, cn[6];

int comp(double a, double b) {
	if (fabs(a - b) < eps)
		return 0;
	return (a > b) ? 1 : -1;
}

bool inRange(point p) {
	bool cond1 = (p.x >= st.x && p.x <= ed.x);
	bool cond2 = (p.y >= st.y && p.y <= ed.y);
	bool cond3 = (p.z >= st.z && p.z <= ed.z);
	return (cond1 && cond2 && cond3);
}

double getVol(int msk) {
	double ret = 0.0, r[6];
	for (int i = 0; i < sz; ++i) {
		if ((msk >> i) & 1) {
			double dx = min(cn[i].x - st.x, ed.x - cn[i].x);
			double dy = min(cn[i].y - st.y, ed.y - cn[i].y);
			double dz = min(cn[i].z - st.z, ed.z - cn[i].z);
			r[i] = min(dx, min(dy, dz));
			for (int j = 0; j < i; ++j) {
				if ((msk >> j) & 1) {
					double dist = cn[i].dist(cn[j]) - r[j];
					r[i] = min(r[i], dist);
				}
			}
			if (comp(r[i], 0.0) >= 0)
				ret += ((4.0 / 3.0) * M_PI * (r[i] * r[i] * r[i]));
		}
	}
	return ret;
}

double getComp(int msk, int idx) {
	if (idx == sz)
		return getVol(msk);
	double ret1 = getComp(msk, idx + 1);
	double ret2 = getComp((1 << idx) | msk, idx + 1);
	return max(ret1, ret2);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int tst = 0;
	while (cin >> n && n != 0) {
		double x[2], y[2], z[2];
		cin >> x[0] >> y[0] >> z[0];
		cin >> x[1] >> y[1] >> z[1];
		st = {min(x[0], x[1]), min(y[0], y[1]), min(z[0], z[1])};
		ed = {max(x[0], x[1]), max(y[0], y[1]), max(z[0], z[1])};
		sz = 0;
		for (int i = 0; i < n; ++i) {
			double X, Y, Z;
			cin >> X >> Y >> Z;
			point p = { X, Y, Z };
			if (inRange(p))
				cn[sz++] = p;
		}
		sort(cn, cn + sz);
		double ret = 0.0;
		do {
			ret = max(ret, getComp(0, 0));
		} while (next_permutation(cn, cn + sz));
		double ans = ((ed.x - st.x) * (ed.y - st.y) * (ed.z - st.z)) - ret;
		cout << "Box " << ++tst << ": " << int(ans + 0.5) << "\n\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
