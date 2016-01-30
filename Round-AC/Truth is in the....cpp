#include <bits/stdc++.h>

using namespace std;

const int N = 100000;
int m;
pair<char, int> st[N];
int arr[N + 1][2];
char ans[N + 1];
vector<int> ds;

void build(int idx) {
	for (int i : ds) {
		bool next = st[i].second == idx;
		ans[i] = next ? 't' : 'f';
		for (int j = (i + m - 1) % m; st[j].first != '$'; j = (j + m - 1) % m) {
			next ^= st[j].first == '-';
			ans[j] = next ? 't' : 'f';
		}
	}
}

int main() {
	freopen("truth.in", "rt", stdin);
	freopen("truth.out", "wt", stdout);
	cin >> m;
	map<int, int> cnt;
	for (int i = 0; i < m; ++i) {
		cin >> st[i].first;
		if (st[i].first == '$') {
			cin >> st[i].second;
			cnt[st[i].second]++;
			ds.push_back(i);
		}
	}
	//t t f f t t f f t
	if (ds.empty()) {
		bool next = true;
		for (int i = 0; i < m; ++i) {
			ans[i] = next ? 't' : 'f';
			next ^= st[i].first == '-';
		}
		if (next == true) {
			puts("consistent");
			puts(ans);
		} else {
			puts("inconsistent");
		}
		return 0;
	}
	int sumIfAllFalses = 0;
	for (int i : ds) {
		bool next = true;
		for (int j = (i + m - 1) % m; st[j].first != '$'; j = (j + m - 1) % m) {
			next ^= st[j].first == '-';
			arr[st[i].second][next]++;
		}
	}
	for (auto item : cnt)
		sumIfAllFalses += arr[item.first][0];
	if (cnt.count(sumIfAllFalses) == 0) {
		build(-1);
		puts("consistent");
		puts(ans);
		return 0;
	}
	for (auto item : cnt) {
		int d = item.first;
		if (d - cnt[d] - arr[d][1] - sumIfAllFalses + arr[d][0] == 0) {
			build(d);
			puts("consistent");
			puts(ans);
			return 0;
		}
	}
	puts("inconsistent");
	return 0;
}
