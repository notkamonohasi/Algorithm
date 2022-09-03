// Longest Increasing Subsequence   最長増加部分列
// verify https://atcoder.jp/contests/abc006/submissions/34521768 


template <typename T>
struct SegmentTree{
    using F = function<T(T, T)>;
    ll n;         // 葉の数
    vector<T> dat; // 完全二分木の配列
    F f;   // 関数
    T m;   // 単位元
    
    SegmentTree(ll n_, F f, T m) : n(), dat(n_ * 4, m), f(f), m(m){ // 葉の数は 2^x の形
        ll x = 1;
        while(n_ >= x){x *= 2;}
        n = x;
    }
    
    void add(ll i, T x){
        i += n - 1;
        dat[i] += x;
        while(i > 0){
            i = (i - 1) / 2;  // parent
            dat[i] = f(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    void set(ll i, T x) {
        i += n - 1;
        dat[i] = x;
        while(i > 0){
            i = (i - 1) / 2;  // parent
            dat[i] = f(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }
    
    T get(ll i){return dat[i + n - 1];}

    T query(ll a, ll b){ return query_sub(a, b, 0, 0, n); }
    T query_sub(ll a, ll b, ll k, ll l, ll r){
        if(r <= a || b <= l){
            return m;
        }else if(a <= l && r <= b){
            return dat[k];
        }else{
            T vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return f(vl, vr);
        }
    }
};


template <typename T>
void compress(vector<T> &X) {
    vector<T> vals = X;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (ll i = 0; i < (ll)X.size(); i++) {
        X[i] = lower_bound(vals.begin(), vals.end(), X[i]) - vals.begin();
    }
}


/* 最初に座標圧縮をしている */
ll LIS(vector<ll> v1){
    compress(v1);
    ll size = v1.size();
    auto f = [](ll a, ll b){return max(a, b);};
    ll m = 0;
    SegmentTree<ll> seg(size, f, m);
    ll ret = 0;
    rep(i, size){
        ll a = seg.query(0, v1[i]);
        if(seg.get(v1[i]) < a + 1){
            seg.set(v1[i], a + 1);
            ret = max(ret, a + 1);
        }
    }
    return ret;
}
