#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

/**
 * Z Algorithm (Search For All Places That Pattern Happened In Text)
 */
vector<int> buildZArray(string &str) {
	vector<int> Z(str.size(), 0);
	int l = 0, r = 0, sz = str.size();
	for (int i = 1; i < sz; ++i) {
		if (i > r) {
			l = r = i;
			while (r < sz && str[r - l] == str[r])
				++r;
			Z[i] = r - l, --r;
		} else if (Z[i - l] < r - i + 1) {
			Z[i] = Z[i - l];
		} else {
			l = i;
			while (r < sz && str[r - l] == str[r])
				++r;
			Z[i] = r - l, --r;
		}
	}
	return Z;
}

vector<int> searchZFunction(string &text, string &pattern) {
	string concat = pattern + "$" + text;
	vector<int> Z = buildZArray(concat);
	vector<int> places;
	int sz = pattern.size();
	for (int i = sz + 1; i < int(concat.size()); ++i)
		if (Z[i] == sz)
			places.push_back(i - sz - 1);
	return places;
}
