#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/**
 * Hot to use:
 * 		#include <ext/numeric>
 * 	  using namespace __gnu_cxx;
 * 		mat M = power(M, rounds, mul(cnt, cnt));
 */

const ll MOD = 1000000007;

struct mat {
		int r, c;
		vector<vector<ll> > M;
		mat(int rr, int cc) :
				r(rr), c(cc) {
			M.resize(r, vector<ll>(c));
		}
		vector<ll>& operator[](int i) {
			return M[i];
		}
		const vector<ll>& operator[](int i) const {
			return M[i];
		}
};
struct mul {
		int r, c;
		mul(int rr, int cc) {
			r = rr, c = cc;
		}
		mat operator()(const mat&m1, const mat&m2) const {
			mat ret(m1.r, m2.c);
			for (int i = 0; i < m1.r; i++)
				for (int j = 0; j < m2.c; j++)
					for (int k = 0; k < m1.c; k++) {
						ret[i][j] += (m1[i][k] * m2[k][j]) % MOD;
						ret[i][j] %= MOD;
					}
			return ret;
		}
};

mat identity_element(const mul& m) {
	mat M(m.r, m.c);
	for (int i = 0; i < m.r; i++)
		M[i][i] = 1ll;
	return M;
}
