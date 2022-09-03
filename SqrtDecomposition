/* AOJ鯖落ちにつき未verify */

template <typename T>
struct SqrtDecomposition {
    using F = function<T(T, T)>;
    ll N, K, sqrtN;
    F f;
    T m;
    vector<T> data;
    vector<T> bucket;
    
    SqrtDecomposition(ll n, F f, T m) : N(n), sqrtN(sqrt(n)), f(f), m(m) {
        K = (N + sqrtN - 1) / sqrtN;
        data.assign(K * sqrtN, m);
        bucket.assign(K, 0);
    }
    
    void add(ll x, T y) {
        ll k = x / sqrtN;
        data[x] += y;
        T t = m;
        for (ll i = k * sqrtN; i < (k + 1) * sqrtN; ++i) {
            t = f(t, data[i]);
        }
        bucket[k] = t;
    }
    void set(ll x, T y) { add(x, y - data[x]); }
    
    // [x, y)
    T query(ll x, T y) {
        T ret = 0;
        for (ll k = 0; k < K; ++k) {
            ll l = k * sqrtN, r = (k + 1) * sqrtN;
            if (r <= x || y <= l)
            continue;
            if (x <= l && r <= y) {
                ret = f(ret, bucket[k]);
            } else {
                for (ll i = max(x, l); i < min(y, r); ++i) {
                    ret = f(ret, data[i]);
                }
            }
        }
        return ret;
    }
};
