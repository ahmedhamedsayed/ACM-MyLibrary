#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

struct room {
	int av;
	priority_queue<pair<int, int> > workShop;
};

bool operator<(const room& r1, const room& r2) {
	return (r1.av < r2.av);
}

int w, r;
pair<int, int> s[1000];
vector<room> rms;
bool vis[1000];

void init() {
	rms.clear();
	memset(vis, 0, sizeof vis);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int tst = 0;
	while (cin >> w && w != 0) {
		init();
		int ret1 = w, ret2 = 0;
		for (int i = 0; i < w; ++i) {
			cin >> s[i].first >> s[i].second;
			ret2 += s[i].first;
		}
		cin >> r, rms.resize(r);
		for (int i = 0; i < r; ++i) {
			int val, h, m, av;
			char nothing;
			cin >> val >> h >> nothing >> m;
			av = ((h - 14) * 60) + m;
			rms[i].av = av;
			for (int j = 0; j < w; ++j) {
				if (val >= s[j].first && av >= s[j].second)
					rms[i].workShop.push(make_pair(s[j].first, j));
			}
		}
		sort(rms.begin(), rms.end());
		for (int i = 0; i < r; ++i) {
			while (rms[i].workShop.size() && vis[rms[i].workShop.top().second])
				rms[i].workShop.pop();
			if (rms[i].workShop.size()) {
				vis[rms[i].workShop.top().second] = 1;
				--ret1;
				ret2 -= rms[i].workShop.top().first;
			}
		}
		cout << "Trial " << ++tst << ": " << ret1 << " " << ret2 << "\n\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
