struct Combination{
    vector<ll> fac, finv, inv;
    ll MAX;
    Combination(ll MAX_) : fac(MAX_), finv(MAX_), inv(MAX_), MAX(MAX_){
        fac[0] = fac[1] = 1;
        finv[0] = finv[1] = 1;
        inv[1] = 1;
        frep(i, 2, MAX){
            fac[i] = fac[i - 1] * i % MOD;
            inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
            finv[i] = finv[i - 1] * inv[i] % MOD;
        }
    }
    
    ll nCk(ll n, ll k){
        if(n >= MAX){print("Combination input is over n : " + to_string(n)); exit(0);}
        if(n < k){print("n < k : n = " + to_string(n) + " k = " + to_string(k)); exit(0);}
        if(n < 0){print("n < 0 : n = " + to_string(n)); exit(0);}
        if(k < 0){print("k < 0 : k = " + to_string(k)); exit(0);}
        return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
    }
    
    ll nHk(ll n, ll k){
        return nCk(n + k - 1, k);
    }
};
