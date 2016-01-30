#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef complex<double> point;

#define EPS 1e-9
#define X real()
#define Y imag()
#define cross(a,b) ((conj(a)*(b)).imag())
#define vec(a,b) ((b)-(a))
#define length(v) ((double)hypot((v).Y,(v).X))

void fastInOut();

const double FT = 2.0 * M_PI;
const double CA[] = { 0.0, M_PI / 2.0, M_PI, (3.0 * M_PI) / 2.0 };

int n;
point cn[100];
pair<point, point> walls[4];
vector<pair<double, double> > sweep;
double r[100], h[100];
bool vis[100];

void init() {
	memset(vis, 0, sizeof vis);
}

int dcomp(const double &a, const double &b) {
	if (fabs(a - b) <= EPS)
		return 0;
	return (a < b) ? -1 : 1;
}

double pointLineDist(const point &a, const point &b, const point &p) {
	return fabs(cross(vec(a,b),vec(a,p)) / length(vec(a, b)));
}

double repair(const double &angle) {
	return fmod(fmod(angle, FT) + FT, FT);
}

void add(point range) {
	range = point(repair(range.X), repair(range.Y));
	if (dcomp(range.X, range.Y) > 0) {
		sweep.push_back(make_pair(range.X, FT));
		sweep.push_back(make_pair(0.0, range.Y));
	} else
		sweep.push_back(make_pair(range.X, range.Y));
}

void checkWall(int idx, int wall) {
	double angle = 0.0;
	double l = length(point(r[idx], h[idx]));
	double d = pointLineDist(walls[wall].first, walls[wall].second, cn[idx]);
	if (dcomp(l, d) <= 0)
		return;
	angle = M_PI - (2.0 * (asin(d / l) - asin(r[idx] / l)));
	double st = (M_PI - angle) / 2.0 + CA[wall];
	add(point(st, st + angle));
}

void checkTree(int cur, int oth) {
	if (cur == oth || vis[oth])
		return;
	double angle = 0.0, d = length(point(vec(cn[cur],cn[oth])));
	if (dcomp(d - r[oth], h[cur]) > 0)
		return;
	angle = asin((r[cur] + r[oth]) / d);
	point cnOth = vec(cn[cur], cn[oth]);
	double st = atan2(cnOth.Y, cnOth.X) - angle;
	add(point(st, st + (2.0 * angle)));
}

bool cut(int idx) {
	for (int i = 0; i < 4; ++i)
		checkWall(idx, i);
	for (int i = 0; i < n; ++i)
		checkTree(idx, i);
	int size = sweep.size();
	double prv = 0.0;
	sort(sweep.begin(), sweep.end());
	for (int i = 0; i < size; ++i) {
		if (dcomp(prv, sweep[i].first) < 0)
			return 1;
		if (dcomp(prv, sweep[i].second) < 0)
			prv = sweep[i].second;
	}
	return (dcomp(prv, FT) < 0);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	double mnx, mny, mxx, mxy;
	int tst = 0;
	while (cin >> mnx >> mny >> mxx >> mxy >> n) {
		if (mnx == 0 && mny == 0 && mxx == 0 && mxy == 0 && n == 0)
			break;
		init();
		walls[0] = make_pair(point(mnx, mxy), point(mxx, mxy));
		walls[1] = make_pair(point(mnx, mny), point(mnx, mxy));
		walls[2] = make_pair(point(mnx, mny), point(mxx, mny));
		walls[3] = make_pair(point(mxx, mny), point(mxx, mxy));
		for (int i = 0; i < n; ++i) {
			double x, y, d;
			cin >> x >> y >> d >> h[i];
			r[i] = d / 2.0;
			cn[i] = point(x, y);
		}
		int ret = 0;
		bool out = 0;
		while (!out) {
			out = 1;
			for (int i = 0; i < n; ++i) {
				sweep.clear();
				if (!vis[i] && cut(i))
					++ret, vis[i] = 1, out = 0;
			}
		}
		cout << "Forest " << ++tst << "\n" << ret << " tree(s) can be cut\n\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
