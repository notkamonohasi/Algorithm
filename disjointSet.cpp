
// keywords: DisjointSet, UnionFind

// DisjointSet

// verify: https://algo-method.com/tasks/431/editorial 

class DisjointSet{
public:
    vector<ll> rank, p;
    DisjointSet(){}
    DisjointSet(ll size){rank.resize(size, 0); p.resize(size, 0); for(ll i=0; i<size; i++) makeSet(i);}
    void makeSet(ll x){p[x]=x; rank[x]=0;}
    bool same(ll x, ll y){return findSet(x) == findSet(y);}
    void unite(ll x, ll y){link(findSet(x), findSet(y));}
    void link(ll x, ll y){if(rank[x]>rank[y]) p[y]=x; else{p[x]=y; if(rank[x]==rank[y]) rank[y]++;}}
    ll findSet(ll x){if(x!=p[x]) p[x]=findSet(p[x]); return p[x];}
};


// グループサイズ付きDisjointSet

// verify: https://atcoder.jp/contests/abc264/submissions/51246693

class DisjointSet{
public:
    vector<ll> rank, p, sizeVec;
    DisjointSet(){}
    DisjointSet(ll size){rank.resize(size, 0); p.resize(size, 0); sizeVec.resize(size, 1); for(ll i=0; i<size; i++) makeSet(i);}
    void makeSet(ll x){p[x]=x; rank[x]=0;}
    bool same(ll x, ll y){return findSet(x) == findSet(y);}
    void unite(ll x, ll y){
        ll par1 = findSet(x); 
        ll par2 = findSet(y); 
        link(par1, par2);
    }
    void link(ll x, ll y){
        if(x == y) return;
        ll s_x = sizeVec[x];
        ll s_y = sizeVec[y];
        if(rank[x]>rank[y]){ 
            p[y]=x; 
            sizeVec[x] += s_y;
            sizeVec[y] = 0;
        }
        else{
            p[x]=y;
            sizeVec[y] += s_x;
            sizeVec[x] = 0;
            if(rank[x]==rank[y]) rank[y]++;
        }
    }
    ll findSet(ll x){if(x!=p[x]) p[x]=findSet(p[x]); return p[x];}
    ll getSize(ll x){return sizeVec[findSet(x)];}
};