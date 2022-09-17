/* 重み付きUnionFind
 * verify : https://atcoder.jp/contests/abc214/submissions/34906883 
 */

struct UnionFind {
    vector<ll> par, rank, weight;

    UnionFind(ll n) : par(n, -1), rank(n, 0), weight(n, 1){}
    
    // 途中で重みを足すのには対応していない
    void setWeight(ll k, ll w){
        weight[k] = w;
    }

    ll root(ll x){
        if(par[x] == -1) return x; 
        else return par[x] = root(par[x]);   // 経路圧縮
    }

    bool issame(ll x, ll y){
        return root(x) == root(y);
    }

    void unite(ll x, ll y) {
        ll rx = root(x);
        ll ry = root(y); 
        if(rx == ry) return; 
        if(rank[rx] < rank[ry]) swap(rx, ry); 
        par[ry] = rx; 
        if(rank[rx] == rank[ry]) rank[rx]++; 
        weight[rx] += weight[ry]; 
    }
    
    ll getWeight(ll x){
        return weight[root(x)];
    }
};
