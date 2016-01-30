#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int n;
ull k;
vector<ull> powTwo;

void init() {
	for (ull i = 0; i < 64; ++i)
		powTwo.push_back(power(2LL, i));
}

vector<pair<int, int> > ret;
void build(int idx, int rem, int prv) {
	while (true) {
		if (rem - 1 >= 64) {
			ret.push_back(make_pair(idx, prv + 1));
			++idx, --rem, ++prv;
		} else if (rem == 0)
			return;
		else {
			int bt = 0;
			for (int i = rem - 1; i >= 0; --i) {
				if (powTwo[max(0, i - 1)] < k) {
					++bt;
					ret.push_back(make_pair(idx + bt, prv + bt));
					k -= powTwo[i - 1];
				} else {
					ret.push_back(make_pair(idx, prv + bt + 1));
					break;
				}
			}
			idx += (bt + 1), rem -= (bt + 1), prv += (bt + 1);
		}
	}
}

int main() {
	freopen("bubble.in", "r", stdin);
	freopen("bubble.out", "w", stdout);
	fastInOut();
	init();
	while (cin >> n >> k && n != 0 && k != 0) {
		ret.clear();
		build(0, n, 0);
		sort(ret.begin(), ret.end());
		for (int i = 0; i < int(ret.size()); ++i)
			cout << ((i == 0) ? "" : " ") << ret[i].second;
		cout << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
