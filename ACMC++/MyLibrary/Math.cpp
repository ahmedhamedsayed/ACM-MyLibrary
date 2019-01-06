#include <bits/stdc++.h>

using namespace std;

/**
 * Fermat's little theorem: (a ^ -1) % p = (a ^ (p - 2)) % p if p prime.
 */

int mod(int a, int b) {
	return a - (a / b) * b;
}

int gcd(int a, int b) {
	return (b == 0) ? a : gcd(b, mod(a, b));
}

int nCr(int n, int r) {
	if (n == r)
		return 1;
	int x, y, z, g;
	x = nCr(n - 1, r), y = n, z = (n - r);
	g = gcd(x, z), x /= g, z /= g;
	g = gcd(y, z), y /= g, z /= g;
	return (x * y) / z;
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
