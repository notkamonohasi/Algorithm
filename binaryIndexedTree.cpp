// keywords: 区間加算, 区間和, 一点取得, SegmentTree

/* 
  区間加算・区間和・一点取得
  初期値は全て0
  add, query, getの入力は0-index
  計算量は全て O(logn)


  verified: https://onlinejudge.u-aizu.ac.jp/status/users/notkamonohasi/submissions/1/DSL_2_G/judge/8911738/C++17 https://atcoder.jp/contests/abc341/submissions/50409552 
  thanks: https://algo-logic.info/binary-indexed-tree/#
*/
template <typename T>
struct BIT {
  int n;       // 要素数
  vector<T> bit[2];  // データの格納先
  BIT(int n_) { init(n_); }
  void init(int n_) {
    n = n_ + 1;
    for (int p = 0; p < 2; p++) bit[p].assign(n, 0);
  }


  void add_sub(int p, int i, T x) {
    for (int idx = i; idx < n; idx += (idx & -idx)) {
      bit[p][idx] += x;
    }
  }
  void add(int l, int r, T x) {  // [l,r) に加算
    l++, r++;  // 0-index -> 1-index
    add_sub(0, l, -x * (l - 1));
    add_sub(0, r, x * (r - 1));
    add_sub(1, l, x);
    add_sub(1, r, -x);
  }


  T sum_sub(int p, int i) {
    T s(0);
    for (int idx = i; idx > 0; idx -= (idx & -idx)) {
      s += bit[p][idx];
    }
    return s;
  }
  T sum(int i) { return sum_sub(0, i) + sum_sub(1, i) * i; }


  // [l,r) の区間和を取得
  T query(int l, int r) { 
    l++; r++;  // 0-index -> 1-index
    return sum(r - 1) - sum(l - 1); 
  }


  // xの値を取得する
  T get(int x) {
    return sum(x + 1) - sum(x); 
  }
};