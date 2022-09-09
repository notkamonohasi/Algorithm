/* 素因数分解
 * 一つだけ欲しいならPrimeFactより早い
 */
map<ll, ll> getPrimeFact(ll n){
    ll k = sqrt(n) + 5;
    map<ll, ll> ret;
    frep(i, 2, k){
        while(true){
            if(n % i == 0){
                n /= i;
                ret[i]++;
            }
            else break;
        }
    }
    if(n != 1) ret[n]++;
    return ret;
}

/*  PrimeFact
    init(N): 初期化。O(N log log N)
    get(n): クエリ。素因数分解を求める。O(log n)
 */
template <typename T>
struct PrimeFact {
    vector<T> spf;
    PrimeFact(T N) { init(N); }
    void init(T N) { // 前処理。spf を求める
        spf.assign(N + 1, 0);
        for (T i = 0; i <= N; i++) spf[i] = i;
        for (T i = 2; i * i <= N; i++) {
            if (spf[i] == i) {
                for (T j = i * i; j <= N; j += i) {
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
    }
    map<T, T> get(T n) { // nの素因数分解を求める
        map<T, T> m;
        while (n != 1) {
            m[spf[n]]++;
            n /= spf[n];
        }
        return m;
    }
};
