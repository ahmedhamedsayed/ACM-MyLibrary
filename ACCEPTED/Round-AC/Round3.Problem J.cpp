#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

const ll OO = 1e18;
int n, m;
vector<pair<int, ll> > e[301];

double floyd() {
	ll dist[301][301], cnt[301][301];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			dist[i][j] = OO;
			cnt[i][j] = OO;
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < int(e[i].size()); ++j) {
			int t = e[i][j].first;
			dist[i][t] = min(dist[i][t], e[i][j].second);
			cnt[i][t] = 1;
		}
	}
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					cnt[i][j] = cnt[i][k] + cnt[k][j];
				} else if (dist[i][j] == dist[i][k] + dist[k][j]) {
					if (cnt[i][j] > cnt[i][k] + cnt[k][j])
						cnt[i][j] = cnt[i][k] + cnt[k][j];
				}
			}
		}
	}
	double num = 0.0, dum = 0.0;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			num += cnt[i][j];
			++dum;
		}
	}
	return (num / dum);
}

int main() {
	freopen("trip.in", "r", stdin);
	freopen("trip.out", "w", stdout);
	fastInOut();
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int f, t, c;
		cin >> f >> t >> c;
		--f, --t;
		e[f].push_back(make_pair(t, c));
		e[t].push_back(make_pair(f, c));
	}
	cout << fixed << setprecision(17) << floyd() << endl;
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
