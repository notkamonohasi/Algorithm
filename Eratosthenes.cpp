/* key word : エラトステネスの篩
 */
vector<bool> Eratosthenes(ll N) {
    vector<bool> isprime(N + 1, true);
    isprime[0] = isprime[1] = false;
    for (ll p = 2; p <= N; ++p) {
        if (!isprime[p]) continue;
        for (int q = p * 2; q <= N; q += p) {
            isprime[q] = false;
        }
    }
    return isprime;
}

// nまでの素数が入ったvectorを作成
vector<ll> makePrimeVec(ll n){
    vector<bool> isprime = Eratosthenes(n);
    vector<ll> ret;
    rep(i, n){
        if(isprime[i]) ret.push_back(i);
    }
    return ret;
}
