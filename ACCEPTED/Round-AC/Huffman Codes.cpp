#include <bits/stdc++.h>

using namespace std;

struct node {
	pair<int, int> zo;
	node *left, *right;
}*sen = new node( { make_pair(-1, -1), sen, sen });

int n;
vector<node*> save[210];
map<pair<int, int>, int> cnt[210];
bool vis[210];
pair<int, int> arr[101];
string ans[101];
void init() {
	for (int i = 0; i <= 200; ++i)
		save[i].clear(), cnt[i].clear();
}

void update(int lvl, pair<int, int> cur1, pair<int, int> cur2) {
	node *nxt = new node { make_pair(cur1.first, cur2.second), sen, sen };
	for (int i = 0; i < int(save[lvl].size()); ++i) {
		if (vis[i])
			continue;
		if (save[lvl][i]->zo == cur1 && nxt->right == sen)
			nxt->right = save[lvl][i], vis[i] = 1;
		if (save[lvl][i]->zo == cur2 && nxt->left == sen)
			nxt->left = save[lvl][i], vis[i] = 1;
	}
	save[lvl - 1].push_back(nxt);
}

bool solve(int lvl) {
	memset(vis, 0, sizeof vis);
	for (auto &item : cnt[lvl]) {
		pair<int, int> cur1 = item.first;
		pair<int, int> cur2 = make_pair(cur1.first + 1, cur1.second - 1);
		pair<int, int> nxt = make_pair(cur1.first, cur2.second);
		while (item.second) {
			if (cnt[lvl][cur2] == 0)
				return 0;
			update(lvl, cur1, cur2);
			--cnt[lvl][cur1];
			--cnt[lvl][cur2];
			++cnt[lvl - 1][nxt];
		}
	}
	return 1;
}

void rec(node *cur, string att) {
	if (cur->left == sen && cur->right == sen) {
		for (int i = 0; i < n; ++i) {
			if (vis[i] || arr[i] != cur->zo)
				continue;
			ans[i] = att, vis[i] = 1;
			break;
		}
		return;
	}
	rec(cur->left, att + "0");
	rec(cur->right, att + "1");
}

int main() {
	freopen("huffman.in", "rt", stdin);
	freopen("huffman.out", "wt", stdout);
	while (cin >> n && n != 0) {
		init();
		node *root = sen;
		int z, o, lvl = 0;
		for (int i = 0; i < n; ++i) {
			cin >> z >> o;
			arr[i] = make_pair(z, o);
			save[z + o].push_back(new node { make_pair(z, o), sen, sen });
			++cnt[z + o][make_pair(z, o)];
			lvl = max(lvl, z + o);
		}
		bool ret = 1;
		while (lvl > 0) {
			if (!solve(lvl))
				ret = 0;
			if (!ret)
				break;
			--lvl;
		}
		if (!ret || int(save[0].size()) != 1)
			cout << "No\n";
		else {
			cout << "Yes\n";
			root = save[0][0];
			memset(vis, 0, sizeof vis);
			rec(root, "");
			for (int i = 0; i < n; ++i)
				cout << ans[i] << "\n";
		}
	}
	return 0;
}
