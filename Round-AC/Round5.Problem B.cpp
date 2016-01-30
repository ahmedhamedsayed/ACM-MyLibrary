#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

const double OO = 1e9;
const double EPS = 1e-9;
int n, m, y, x[1000], k[1000];
map<pair<int, int>, double> memo;

int dcomp(double a, double b) {
	if (fabs(a - b) <= EPS)
		return 0;
	return (a < b) ? -1 : 1;
}

double solve(int idx, int rem) {
	if (idx == n)
		return ((rem == 0) ? 0.0 : OO);
	if (memo.find(make_pair(idx, rem)) != memo.end())
		return memo[make_pair(idx, rem)];
	double ratio1 = double(x[idx]) / double(y);
	double ratio2 = double(k[idx]) / double(m);
	double ret1 = fabs(ratio1 - ratio2) + solve(idx + 1, rem), ret2 = OO;
	if (rem > 0)
		ret2 = fabs(ratio1 - (1.0 / m + ratio2)) + solve(idx + 1, rem - 1);
	return memo[make_pair(idx, rem)] = min(ret1, ret2);
}

void buildPath(int idx, int rem) {
	if (idx == n)
		return;
	double ratio1 = double(x[idx]) / double(y);
	double ratio2 = double(k[idx]) / double(m);
	double ret1 = fabs(ratio1 - ratio2) + solve(idx + 1, rem), ret2 = OO;
	if (rem > 0)
		ret2 = fabs(ratio1 - (1.0 / m + ratio2)) + solve(idx + 1, rem - 1);
	if (dcomp(ret1, ret2) >= 0)
		++k[idx], buildPath(idx + 1, rem - 1);
	else
		buildPath(idx + 1, rem);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	fastInOut();
	cin >> n >> m >> y;
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		cin >> x[i];
		k[i] = (x[i] * m) / y;
		sum += k[i];
	}
	solve(0, m - sum);
	buildPath(0, m - sum);
	for (int i = 0; i < n; ++i)
		cout << ((i == 0) ? "" : " ") << k[i];
	cout << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
