// keywords: 座標圧縮
// verify: https://atcoder.jp/contests/abc188/submissions/56336265

// https://algo-logic.info/coordinate-compress/#toc_id_1_3

struct Compressor{
    unordered_map<ll, ll> encoder;
    vector<ll> decoder;

    Compressor(){}
    Compressor(vector<ll>& v){
        auto tmp = compress(v);
        ll m = *max_element(tmp.begin(), tmp.end());
        decoder.resize(m + 1);
        for(ll i = 0; i < v.size(); i++){
            encoder[v[i]] = tmp[i];
            decoder[tmp[i]] = v[i]; 
        }
    }

    ll encode(ll x){
        auto it = encoder.find(x);
        assert(it != encoder.end());
        return it->second;
    }

    ll decode(ll x){
        assert(x < decoder.size());
        return decoder[x];
    }

    ll size(){ return decoder.size(); }

    vector<ll> compress(vector<ll> X) {
        vector<ll> vals = X;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        for (ll i = 0; i < (ll)X.size(); i++) {
            X[i] = lower_bound(vals.begin(), vals.end(), X[i]) - vals.begin();
        }
        return X;
    }
};

/* compress
    X を座標圧縮して書き換える（副作用）
    返り値: ソート済みの値
    計算量: O(n log n)
*/
template <typename T>
vector<T> compress(vector<T> &X) {
    // ソートした結果を vals に
    vector<T> vals = X;
    sort(vals.begin(), vals.end());
    // 隣り合う重複を削除(unique), 末端のゴミを削除(erase)
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    // 各要素ごとに二分探索で位置を求める
    for (ll i = 0; i < (ll)X.size(); i++) {
        X[i] = lower_bound(vals.begin(), vals.end(), X[i]) - vals.begin();
    }
    return vals;
}


template <typename T>
ll search_vector(vector<T> vec, T target){
    if(binary_search(vec.begin(), vec.end(), target) == false){
        cout << "not find in search_vector" << endl;
        return -1;
    }
    else{
        auto itr = lower_bound(vec.begin(), vec.end(), target);
        ll ret = distance(vec.begin(), itr);
        return ret;
    }
}


ll max(ll a, ll b){
    if(a > b) return a;
    else return b;
}


int main(){
    ll w, n;   cin >> w >> n;
    ll L[n], R[n];
    vector<ll> vec;
    rep(i, n){
        ll l, r;   cin >> l >> r;   l--;   r--;
        L[i] = l;   R[i] = r;
        vec.push_back(l);
        vec.push_back(r);
    }
    
    vector<ll> before = compress<ll>(vec);
    ll height[before.size()];
    rep(i, before.size()) height[i] = 0;
    
    rep(i, n){
        ll left = search_vector<ll>(before, L[i]);
        ll right = search_vector<ll>(before, R[i]);
        ll ans = 0;
        for(ll j = left; j <= right; j++) ans = max(ans, height[j]);
        cout << ans + 1 << endl;
        for(ll j = left; j <= right; j++) height[j] = ans + 1;
    }
}

