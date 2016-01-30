#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;

void fastInOut();

int ret = 0;
string x;

struct TST {
	int val;
	char data;
	TST *lft, *eq, *rgt;

	TST(char D) {
		val = 0;
		data = D;
		lft = eq = rgt = NULL;
	}
};

TST* insert(TST* root, int st, int ed, int type) {
	if (root == NULL)
		root = new TST(x[st]);
	if (x[st] < root->data)
		root->lft = insert(root->lft, st, ed, type);
	else if (x[st] > root->data)
		root->rgt = insert(root->rgt, st, ed, type);
	else {
		if (st + 1 <= ed)
			root->eq = insert(root->eq, st + 1, ed, type);
		else if (root->val != type && root->val != 3) {
			++ret;
			root->val += type;
		}
	}
	return root;
}

TST *root;
int calc(int st, int ed, int nxt) {
	int md = st;
	int is = ((st == ed) ? 1 : 2);
	while (st >= 0 && ed < int(x.size()) && x[st] == x[ed]) {
		if (ed > nxt)
			root = insert(root, st, md, is);
		--st, ++ed;
	}
	++st, --ed;
	if (st <= ed)
		return ed;
	return nxt;
}

int main() {
	freopen("palindromes.in", "r", stdin);
	freopen("palindromes.out", "w", stdout);
	fastInOut();
	cin >> x;
	root = NULL;
	int nxt1 = -1, nxt2 = -1;
	for (int i = 0; i < int(x.size()); ++i) {
		nxt1 = calc(i, i, nxt1);
		if (i + 1 < int(x.size()))
			nxt2 = calc(i, i + 1, nxt2);
	}
	cout << ret << "\n";
	return 0;
}

void fastInOut() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL), cout.tie(NULL);
}
