#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<double> point;

const ll MOD = 1000000007;
const double EPS = 1e-9;

double fixZero(double num) {
	if (fabs(num) <= EPS)
		return 0.0;
	return num;
}

/**
 * Fermat's little theorem: (a ^ -1) % p = (a ^ (p - 2)) % p if p prime.
 */
ll fastPow(ll base, ll pwr) {
	ll cur = base, ret = 1;
	for (int i = 0; i < 64; ++i) {
		if ((pwr >> i) & 1)
			ret = (ret * cur) % MOD;
		cur = (cur * cur) % MOD;
	}
	return ret;
}

int mod(int a, int b) {
	return a - (a / b) * b;
}

int gcd(int a, int b) {
	return (b == 0) ? a : gcd(b, mod(a, b));
}

/**
 * res = q*d + m;
 * (res/d)*nn
 * (q*nn + nn*m/d)
 */
ll nCr(int n, int r) {
	ll ret = 1;
	for (int nn = r + 1; nn <= n; ++nn) {
		int d = nn - r;
		ll q = ret / d, m = ret % d;
		ret = (q * nn) + (nn * m / d);
	}
	return ret;
}

/**
 * find all values of x: x^n = m
 * proof x^n = 1:
 * 		Euler's formula: e^(ix) = cos(x) + i*sin(x)
 * 		e^(2*pi*i) = cos(2*pi) + i*sin(2*pi) = 1
 * 		e^(2*pi*i*k) = 1^k = 1, where k is positive integer
 * 		x^n = 1 = e^(2*pi*i*k), k = 1, 2, ..., n
 * 		x = e^(2*pi*i*k / n) = cos(2*pi*k / n) + i*sin(2*pi*k / n)
 * solve x^n = m:
 * 		x^n = m * 1 = m * e^(2*pi*i*k)
 * 		x = m^(1/n) * (cos(2*pi*k / n) + i*sin(2*pi*k / n))
 */
vector<point> findNthRootsOfUnity(int n, int m) {
	vector<point> rootsOfUnity(n);
	double fact = pow(m, 1.0 / n);
	for (int k = 1; k <= n; ++k) {
		double cur = (2.0 * M_PI * k) / n;
		rootsOfUnity[k - 1] = point(fixZero(fact * cos(cur)), fixZero(fact * sin(cur)));
	}
	return rootsOfUnity;
}

/**
 * ax + by = c -> linear Diophantine Equation.
 * It has solution if gcd(a, b) | c -> c = m * gcd(a, b).
 * I will solve simple version of equation when m = 0 -> ax + by = gcd(a, b).
 * r0 = a, r1 = b, ri = ri - 2 mod ri - 1 = ri - 2 - floor(ri - 2 / ri - 1) * ri - 2.
 * axi + byi = ri forALL i.
 * xi = xi - 2 - floor(ri - 2 / ri - 1) * xi - 1.
 * yi = yi - 2 - floor(ri - 2 / ri - 1) * yi - 1.
 */
void nxtMove(int& i0, int& i1, int flr) {
	int i2 = i0 - flr * i1;
	i0 = i1, i1 = i2;
}

int Egcd(int r0, int r1, int &x0, int &y0) {
	int y1 = x0 = 1, x1 = y0 = 0;
	while (r1) {
		int flr = r0 / r1;
		nxtMove(r0, r1, flr), nxtMove(x0, x1, flr), nxtMove(y0, y1, flr);
	}
	return (r0 < 0) ? (x0 *= -1, y0 *= -1, -r0) : r0;
}

bool solveLDE(int a, int b, int c, int &x, int &y, int &gcd) {
	gcd = Egcd(a, b, x, y);
	int m = c / gcd;
	x *= m, y *= m;
	return !(c % gcd);
}
