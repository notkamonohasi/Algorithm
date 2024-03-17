// keywords: 因数分解, 高速因数分解

/*  PrimeFact
    init(N): 初期化。O(N log log N)
    get(n): クエリ。素因数分解を求める。O(log n)
 */
struct PrimeFact {
  vector<ll> spf;
  PrimeFact(ll N) { init(N); }

  // 前処理。spf を求める
  void init(ll N) {
    spf.assign(N + 1, 0);
    for (ll i = 0; i <= N; i++) spf[i] = i;
    for (ll i = 2; i * i <= N; i++) {
      if (spf[i] == i) {
        for (ll j = i * i; j <= N; j += i) {
          if (spf[j] == j) {
            spf[j] = i;
          }
        }
      }
    }
  }

  // nの素因数分解を求める
  map<ll, ll> get(ll n) {   
    map<ll, ll> m;
    while (n != 1) {
      m[spf[n]]++;
      n /= spf[n];
    }
    return m;
  }
};