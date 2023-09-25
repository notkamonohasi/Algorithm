verify : https://atcoder.jp/contests/abc321/submissions/45939998

// 1-indexに注意
// 1-indexでないと実装が難しい
struct BinaryTree{
    ll n;   // 要素数
    unordered_map<ll, ll> pow2_mp;   // 2^kの結果を記憶しておく

    BinaryTree(){}
    BinaryTree(ll n_) : n(n_){}

    // 要素iの親を計算
    ll get_parent(ll i){
        assert(1 < i && i <= n); 
        return (ll)(i / 2); 
    }

    // 要素iの深さを計算
    // 深さは0-index
    ll get_depth(ll i){
        assert(1 <= i && i <= n); 
        ll d = 0;  
        while(true){
            i >>= 1; 
            if(!i) break; 
            d++; 
        }
        return d; 
    }

    // 要素iから葉の方向にdistの距離にある要素数を計算
    ll get_component_size(ll i, ll dist){
        assert(1 <= i && i <= n); 
        assert(dist >= 0); 

        // 要素が無限にある時、[left, right)
        // distが大きいとオーバーフローするので気を付ける
        ll n2 = my_pow(dist); 
        if(n2 < 0) return 0; 
        if(LLONG_MAX / (i + 1) <= n2) return 0; 
        ll left = i * n2; 
        ll right = (i + 1) * n2 - 1; 

        if(left > n) return 0; 
        else if(left <= n && n < right) return n - left + 1; 
        else return right - left + 1; 
    }

    // オーバーフローに気を付けてpowを計算
    // オーバーフロー時は-1を返す
    // (a, b)=(2, 64)以上ではオーバーフローするので、この計算はそこまで重くない（軽くしたいなら前計算すればよい）
    ll my_pow(ll a, ll MAX=LLONG_MAX){
        assert(a >= 0); 

        if(bs(pow2_mp, a)) return pow2_mp[a]; 
        else{
            ll ret = 1; 
            rep(i, a){
                if(MAX / 2 <= ret){
                    ret = -1; 
                    break; 
                }
                else ret *= 2; 
            }
            pow2_mp[a] = ret; 
            return ret; 
        }
    }
}; 