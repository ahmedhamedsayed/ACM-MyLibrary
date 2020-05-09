#include <bits/stdc++.h>

using namespace std;

/**
 * Z Algorithm (Search For All Places That Pattern Happened In Text)
 * An element Z[i] of Z array stores length of the longest substring starting from i which is also a prefix of str.
 * The idea is to maintain an interval [L, R] which is the interval with max R such that [L,R] is prefix substring. 
 * Steps for maintaining this interval are as follows:
 *    1) If i > R then there is no prefix substring that starts before i and ends after i, so we reset and compute new [L,R] by comparing str[0..] to str[i..] then Z[i] = R-L+1.
 *	  2) If i <= R then let K = i-L,
 *	     str[i..] matches with str[K..] for at least R-i+1 characters (they are in [L,R] interval which we know is a prefix substring).
 *   	 Now two sub cases arise:
 *      	a) If Z[K] < R-i+1  then there is no prefix substring starting at str[i] so Z[i] = Z[K] and interval [L,R] remains same.
 *      	b) If Z[K] >= R-i+1 then it is possible to extend the [L,R] interval thus we will set L as i and start matching from str[R] then Z[i] = R-L+1.
 */
const int N = 100000;
int z[N];
void buildZArray(string &str) {
	int l = 0, r = 0, sz = str.size();
	for (int i = 1; i < sz; ++i) {
		if (i > r) {
			l = r = i;
			while (r < sz && str[r - l] == str[r])
				++r;
			z[i] = r - l, --r;
		} else if (z[i - l] < r - i + 1) {
			z[i] = z[i - l];
		} else {
			l = i;
			while (r < sz && str[r - l] == str[r])
				++r;
			z[i] = r - l, --r;
		}
	}
}

vector<int> searchZFunction(string &text, string &pattern) {
	string concat = pattern + "$" + text;
	buildZArray(concat);
	vector<int> places;
	int sz = pattern.size();
	for (int i = sz + 1; i < int(concat.size()); ++i)
		if (z[i] == sz)
			places.push_back(i - sz - 1);
	return places;
}
