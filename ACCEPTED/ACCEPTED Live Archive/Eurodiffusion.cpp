#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

struct country {
	string name;
	int day, x1, y1, x2, y2;
	bool stop;

	bool operator<(const country& c) const {
		if (day == c.day) {
			string n1 = name, n2 = c.name;
			for (int i = 0; i < int(name.size()); ++i)
				n1[i] = tolower(name[i]);
			for (int i = 0; i < int(c.name.size()); ++i)
				n2[i] = tolower(c.name[i]);
			return (n1 < n2);
		}
		return (day < c.day);
	}
};

int n;
country in[20];
int cnt[2][20][20][20];
bool isCity[20][20];

void Init() {
	memset(cnt, 0, sizeof cnt);
	memset(isCity, 0, sizeof isCity);
}

void Fill() {
	for (int c = 0; c < n; ++c) {
		for (int x = in[c].x1; x <= in[c].x2; ++x) {
			for (int y = in[c].y1; y <= in[c].y2; ++y) {
				cnt[0][x][y][c] = 1000000;
				isCity[x][y] = 1;
			}
		}
	}
}

bool IsEnd() {
	for (int x = 1; x <= 10; ++x) {
		for (int y = 1; y <= 10; ++y) {
			for (int c = 0; c < n; ++c) {
				if (isCity[x][y] && cnt[0][x][y][c] == 0)
					return 0;
			}
		}
	}
	return 1;
}

void copy(int f, int t) {
	for (int x = 1; x <= 10; ++x)
		for (int y = 1; y <= 10; ++y)
			for (int c = 0; c < n; ++c)
				cnt[t][x][y][c] = cnt[f][x][y][c];
}

int d1[] = { 0, 0, -1, 1 };
int d2[] = { -1, 1, 0, 0 };
void Update(int x, int y, int c) {
	for (int k = 0; k < 4; ++k) {
		int nx = x + d1[k];
		int ny = y + d2[k];
		if (isCity[nx][ny]) {
			cnt[1][nx][ny][c] += (cnt[0][x][y][c] / 1000);
			cnt[1][x][y][c] -= (cnt[0][x][y][c] / 1000);
		}
	}
}

void Stop(int c) {
	for (int x = in[c].x1; x <= in[c].x2; ++x) {
		for (int y = in[c].y1; y <= in[c].y2; ++y) {
			for (int t = 0; t < n; ++t) {
				if (cnt[0][x][y][t] == 0) {
					++in[c].day;
					return;
				}
			}
		}
	}
	if (!in[c].stop)
		in[c].stop = 1, ++in[c].day;
}

void StartCnt() {
	if (IsEnd())
		return;
	copy(0, 1);
	for (int x = 1; x <= 10; ++x) {
		for (int y = 1; y <= 10; ++y) {
			if (isCity[x][y]) {
				for (int c = 0; c < n; ++c) {
					if (cnt[0][x][y][c] >= 1000) {
						Update(x, y, c);
					}
				}
			}
		}
	}
	copy(1, 0);
	for (int c = 0; c < n; ++c)
		Stop(c);
	StartCnt();
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	fastInOut();
	int tst = 0;
	while (cin >> n && n != 0) {
		Init();
		for (int i = 0; i < n; ++i) {
			string n;
			int x1, y1, x2, y2;
			cin >> n >> x1 >> y1 >> x2 >> y2;
			in[i] = {n, 0, x1, y1, x2, y2, 0};
		}
		Fill();
		StartCnt();
		sort(in, in + n);
		cout << "Case Number " << ++tst << "\n";
		for (int c = 0; c < n; ++c)
			cout << "   " << in[c].name << "   " << in[c].day << "\n";
	}
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
