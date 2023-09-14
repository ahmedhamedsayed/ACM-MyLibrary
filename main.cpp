#define _USE_MATH_DEFINES
 
#include <bits/stdc++.h>
#include <ext/numeric>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
 
typedef long long ll;
typedef unsigned long long ull;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void fastInOut();

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  fastInOut();
  return 0;
}
 
void fastInOut() {
  ios_base::sync_with_stdio(0);
  cin.tie(NULL), cout.tie(NULL);
}
