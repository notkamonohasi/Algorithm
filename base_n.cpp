// keywords: n進法

// verify: https://atcoder.jp/contests/typical90/submissions/51274247

// 10→n
string base_10_to_n(ll x, ll n){
    assert(x >= 0);
    if(x == 0) return "0";
    string ret;
    ll pos = 1;
    while(x){
        ll a = x % (pos * n);
        x -= a;
        ll b = a / pos;
        ret = to_string(b) + ret;
        pos *= n;
    }
    return ret;
}

// n→10
ll base_n_to_10(string s, ll n){
    ll ret = 0;
    ll pos = 1;
    rep(i, s.size()){
        ret += pos * (s[s.size() - 1 - i] - '0');
        pos *= n;
    }
    assert(ret >= 0);  // オーバーフロー注意
    return ret;
}

// n→m
string base_n_to_m(string s, ll n, ll m){
    return base_10_to_n(base_n_to_10(s, n), m);
}