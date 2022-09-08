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
    
    /* find_leftest : [a,b) で x以下の要素を持つ最左位置はどこか
     * find_rightest : [a,b) で x以下の要素を持つ最右位置はどこか
     * f(a, b) = a + b   を想定
     * 参考 : https://qiita.com/recuraki/items/ae8e965b84f0e5443dc5   https://algo-logic.info/segment-tree/
     * verify : https://atcoder.jp/contests/arc033/submissions/34523671
     * rightは未verify
     */
    using BLL = pair<bool, ll>;
    ll find_leftest(ll a, ll b, T x){
        BLL ret = find_leftest_sub(a, b, x, 0, 0, n);
        return (ret.first == true ? ret.second : -1);   // 答えがない時は-1を返す
    }
    BLL find_leftest_sub(ll a, ll b, T x, ll k, ll l, ll r){
        if(dat[k] < x || r <= a || b <= l) return BLL(false, x - dat[k]);   // x - dat[k]の部分は（多分）f^-1(a, b)を入れれば良い
        if(k >= n - 1) return BLL(true, k - (n - 1));   // 自分が葉ならその位置をreturn
        BLL resLeft = find_leftest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);   // 左側を探索
        if(resLeft.first == true) return resLeft;   // 左で解が見つかったのならそれを返す
        else return find_leftest_sub(a, b, resLeft.second, 2 * k + 2, (l + r) / 2, r);   // 左にないなら右へ
    }
    
    ll find_rightest(ll a, ll b, T x){
        BLL ret = find_rightest_sub(a, b, x, 0, 0, n);
        return (ret.first == true ? ret.second : -1);   // 答えがない時は-1を返す
    }
    BLL find_rightest_sub(ll a, ll b, T x, ll k, ll l, ll r){
        if(dat[k] < x || r <= a || b <= l) return BLL(false, x - dat[k]);   // x - dat[k]の部分は（多分）f^-1(a, b)を入れれば良い
        if(k >= n - 1) return BLL(true, k - (n - 1));   // 自分が葉ならその位置をreturn
        BLL resRight = find_rightest_sub(a, b, x, 2 * k + 2, l, (l + r) / 2);   // 右側を探索
        if(resRight.first == true) return resRight;   // 右で解が見つかったのならそれを返す
        else return find_rightest_sub(a, b, resRight.second, 2 * k + 2, (l + r) / 2, r);   // 右にないなら左へ
    }
};
