// https://www.hackerearth.com/problem/algorithm/point-coverage-f0a7e815/?source=list_view
// required some sweep algorithm concepts with usage of fenwick tree or segment tree
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n, q, a[N], ans[N], l[N], r[N], x[N];

template <typename T>
class fenwick {
  vector<T> bit; int N;
public:
  fenwick(int n) { N = n + 5; bit.resize(N);}
  void add(int i, T val) { while (i < N) { bit[i] += val; i += (i & -i);} }
  void add(int l, int r, T val) { add(l, val); add(r + 1, -val);}
  T query(int i) { T ans(0); while (i > 0) { ans += bit[i]; i -= (i & -i); } return ans;} // prefix sum
  T rquery(int l, int r) { return (T)(query(r) - query(l - 1)); } // range sum
  T pquery(int idx) { return (T)(query(idx) - query(idx - 1));}
  int lb(T val) {
    static const int LOG = log2(N); T sum(0); int pos = 0;
    for (int i = LOG; i >= 0; --i) { int calc = pos + (1 << i); if (calc < N && sum + bit[calc] < val) { sum += bit[calc]; pos = calc;}}
    if (pos > N - 5) pos = N - 5; return pos + 1;//// +1 because 'pos' will have position of largest value less than 'v'
  }
};
struct tup {
  int p, q, r;
};

int main() {
  cin >> n >> q;
  set<int> st;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= q; ++i) {
    cin >> l[i] >> r[i] >> x[i];
  }

  vector<tup> v;
  // think [a[i], a[i + 1]] as a segment
  // 1 for starting a segment
  // 2 for queries
  // 3 for ending a segment
  for (int i = 1; i + 1 <= n; ++i) {
    v.push_back({min(a[i], a[i + 1]), 1, i});
    v.push_back({max(a[i], a[i + 1]), 3, i});
  }
  for (int i = 1; i <= q; ++i) {
    v.push_back({x[i], 2, i});
  }

  sort(v.begin(), v.end(), [&](tup & a, tup & b) {
    return make_pair(a.p, a.q) < make_pair(b.p, b.q);
  });


  fenwick<int> f(N);
  for (auto &u : v) {
    if (u.q == 1) {
      f.add(u.r, 1);
    } else if (u.q == 2) {
      ans[u.r] = f.query(r[u.r]) - f.query(l[u.r] - 1);
    } else {
      f.add(u.r, -1);
    }
  }

  for (int i = 1; i <= q; ++i) {
    cout << ans[i] << '\n';
  }

}
