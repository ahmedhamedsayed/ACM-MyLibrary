#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n = 3;
double x[3], y[3], ret[3];

double ED(int i, int j) {
	return hypot(x[i] - x[j], y[i] - y[j]);
}

int main() {
	freopen("bomb.in", "r", stdin);
	freopen("bomb.out", "w", stdout);
	fastInOut();
	for (int i = 0; i < n; ++i)
		cin >> x[i] >> y[i];
	double dis[] = { ED(0, 1), ED(0, 2), ED(1, 2) };
	ret[1] = ((dis[0] - dis[1]) + dis[2]) / 2.0;
	ret[0] = dis[0] - ret[1];
	ret[2] = dis[2] - ret[1];
	cout << fixed << setprecision(9);
	for (int i = 0; i < 3; ++i)
		cout << ret[i] << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
