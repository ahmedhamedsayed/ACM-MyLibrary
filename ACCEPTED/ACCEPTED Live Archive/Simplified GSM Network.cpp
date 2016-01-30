#include <bits/stdc++.h>

using namespace std;

void fastInOut();

typedef long long ll;
typedef unsigned long long ull;
typedef complex<double> point;
#define EPS 1e-9
#define X real()
#define Y imag()
#define polar(r,t) ((r)*exp(point(0.0,(t))))
#define cross(a,b) ((conj(a)*(b)).imag())
#define dot(a,b) ((conj(a)*(b)).real())
#define vec(a,b) ((b)-(a))
#define lengthSqr(v) (dot(v,v))
#define same(a,b) (lengthSqr(vec(a,b))<EPS)
#define mid(a,b) (((a)+(b))/point(2.0,0.0))
#define rotate(v,t) (polar(v,t))
#define rotateabout(v,t,a) (rotate(vec(a,v),t)+(a))

const int OOI = 1e9;
const double OOD = 1001;
int t, c, r, q, dist[50][50];
vector<point> twrs, ctys;
vector<vector<point> > twrsPolygon;

void init() {
	twrs.resize(t);
	twrsPolygon.resize(t);
	ctys.resize(c);
	for (int i = 0; i < t; ++i)
		twrsPolygon[i].clear();
	for (int i = 0; i < c; ++i)
		for (int j = 0; j < c; ++j)
			dist[i][j] = (i == j) ? 0 : OOI;
}

bool pointOnLine(point a, point b, point p) {
	return fabs(cross(vec(a,b), vec(a,p))) < EPS;
}

bool pointOnRay(point a, point b, point p) {
	return dot(vec(a,b),vec(a,p)) > -EPS && pointOnLine(a, b, p);
}

bool pointOnSegment(point a, point b, point p) {
	return pointOnRay(a, b, p) && pointOnRay(b, a, p);
}

bool intersect(const point &a, const point &b, point &p, point &q, point& r) {
	double d1 = cross(vec(a,p), vec(a,b));
	double d2 = cross(vec(a,q), vec(a,b));
	r = (d1 * q - d2 * p) / (d1 - d2);
	if (fabs(d1 - d2) > EPS)
		return 1;
	return 0;
}

bool segmentPolygonIntersect(vector<point> &pnts, point &pnt1, point& pnt2,
		point& cur) {
	for (int i = 0; i < int(pnts.size()); i++) {
		int j = (i + 1) % int(pnts.size());
		if (!intersect(pnts[i], pnts[j], pnt1, pnt2, cur))
			continue;
		bool cond1 = pointOnSegment(pnts[i], pnts[j], cur);
		bool cond2 = pointOnSegment(pnt1, pnt2, cur);
		if (cond1 && cond2)
			return 1;
	}
	return 0;
}

bool pointInPolygon(vector<point> &pnts, point &pnt) {
	point p = pnt + point(1, 0);
	int cnt = 0;
	for (int i = 0; i < int(pnts.size()); i++) {
		int j = (i + 1) % int(pnts.size());
		point r;
		intersect(pnt, p, pnts[i], pnts[j], r);
		if (!pointOnRay(pnt, p, r))
			continue;
		if (same(r, pnts[i]) || same(r, pnts[j]))
			if (fabs(r.Y - min(pnts[i].Y, pnts[j].Y)) < EPS)
				continue;
		if (!pointOnSegment(pnts[i], pnts[j], r))
			continue;
		cnt++;
	}
	return cnt & 1 ? 1 : 0;
}

vector<point> polygonCut(vector<point> &rect, const point &a, const point &b) {
	vector<point> ret;
	for (int i = 0; i < int(rect.size()); i++) {
		int j = (i + 1) % int(rect.size());
		bool in1 = cross(vec(a, b), vec(a, rect[i])) > EPS;
		bool in2 = cross(vec(a, b), vec(a, rect[j])) > EPS;
		if (in1)
			ret.push_back(rect[i]);
		if (in1 ^ in2) {
			point nxt;
			intersect(a, b, rect[i], rect[j], nxt);
			if (int(ret.size()) == 0 || !same(nxt, ret[ret.size() - 1]))
				ret.push_back(nxt);
		}
	}
	return ret;
}

void voronoi() {
	vector<point> ret;
	for (int i = 0; i < t; ++i) {
		vector<point>& cur = twrsPolygon[i];
		cur.push_back(point(-OOD, -OOD));
		cur.push_back(point(OOD, -OOD));
		cur.push_back(point(OOD, OOD));
		cur.push_back(point(-OOD, OOD));
		for (int j = 0; j < t; ++j) {
			if (i == j)
				continue;
			point m = mid(twrs[i], twrs[j]);
			point tmp = vec(twrs[i], twrs[j]);
			tmp = point(-tmp.Y, tmp.X);
			point e = m + tmp;
			ret = polygonCut(cur, m, e);
			if (pointInPolygon(ret, twrs[i]))
				cur = ret;
			else
				cur = polygonCut(cur, e, m);
		}
	}
}

int countTwrs(int c1, int c2) {
	point &pnt1 = ctys[c1], &pnt2 = ctys[c2];
	vector<point> ret;
	for (int i = 0; i < t; ++i) {
		point cur;
		bool in = segmentPolygonIntersect(twrsPolygon[i], pnt1, pnt2, cur);
		if (in) {
			for (int j = 0; j < int(ret.size()); ++j) {
				if (same(ret[j], cur))
					goto nxt;
			}
			ret.push_back(cur);
			nxt: ;
		}
	}
	return ret.size();
}

void floyd() {
	for (int k = 0; k < c; ++k)
		for (int i = 0; i < c; ++i)
			for (int j = 0; j < c; ++j)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int tst = 0;
	while (cin >> t >> c >> r >> q) {
		if (t == 0 && c == 0 && r == 0 && q == 0)
			break;
		init();
		for (int i = 0; i < t; ++i) {
			double x, y;
			cin >> x >> y;
			twrs[i] = point(x, y);
		}
		voronoi();
		for (int i = 0; i < c; ++i) {
			double x, y;
			cin >> x >> y;
			ctys[i] = point(x, y);
		}
		for (int i = 0; i < r; ++i) {
			int c1, c2;
			cin >> c1 >> c2, --c1, --c2;
			dist[c1][c2] = dist[c2][c1] = countTwrs(c1, c2);
		}
		floyd();
		cout << "Case " << ++tst << ":\n";
		for (int i = 0; i < q; ++i) {
			int c1, c2;
			cin >> c1 >> c2, --c1, --c2;
			if (dist[c1][c2] < OOI)
				cout << dist[c1][c2] << "\n";
			else
				cout << "Impossible\n";
		}
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
