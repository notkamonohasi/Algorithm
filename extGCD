/* ax + by = 1 を求める
 * 返り値はP(x, y)
 */
P extGCD(ll a, ll b){
    ll d = a;
    function<ll(ll, ll, ll&, ll&)> f = [&](ll a, ll b, ll& x, ll& y){
        if(b != 0){
            d = f(b, a % b, y, x);
            y -= (a / b) * x;
        }
        else{
            x = 1; y = 0;
        }
        return d;
    };
    ll x, y;
    f(a, b, x, y);
    return P(x, y);
}

/* ax + by = c を求める
 * 返り値はP(x, y)
 */
P extGCD(ll a, ll b, ll c){
    P p = extGCD(a, b);
    return P(p.first * c, p.second * c);
}
