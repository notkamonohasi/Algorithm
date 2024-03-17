// keywords: 木, 直径

// verify: https://atcoder.jp/contests/ABC267/submissions/51374165, https://onlinejudge.u-aizu.ac.jp/status/users/notkamonohasi/submissions/1/GRL_5_A/judge/9000909/C++17 

// 木の直径を計算する
struct Tree{
    EdgeGraph eg;
    ll diameter;  // 直径
    ll left, right;  // 端点

    Tree(const EdgeGraph& eg_) : eg(eg_){ init(); }

    // 木の直径と端点を計算する
    // 任意の点にとって、木の端点の一方が最遠点となることを利用する
    void init(){
        P p = dfs(0, -1);
        P q = dfs(p.second, -1);  // 端点から見た端点
        diameter = q.first;
        left = p.second;
        right = q.second;
    }

    // posからの最遠点を計算する
    // first: 距離, second: 最遠点
    P dfs(ll pos, ll par){
        P ret(0, pos);
        for(auto& e : eg[pos]){
            if(e.to != par){
                P next = dfs(e.to, pos);
                next.first += e.cost;
                ret = max(ret, next);
            }
        }
        return ret;
    }
};// 木の直径を計算する
struct Tree{
    EdgeGraph eg;
    ll diameter;  // 直径
    ll left, right;  // 端点

    Tree(const EdgeGraph& eg_) : eg(eg_){ init(); }

    // 木の直径と端点を計算する
    // 任意の点にとって、木の端点の一方が最遠点となることを利用する
    void init(){
        P p = dfs(0, -1);
        P q = dfs(p.second, -1);  // 端点から見た端点
        diameter = q.first;
        left = p.second;
        right = q.second;
    }

    // posからの最遠点を計算する
    // first: 距離, second: 最遠点
    P dfs(ll pos, ll par){
        P ret(0, pos);
        for(auto& e : eg[pos]){
            if(e.to != par){
                P next = dfs(e.to, pos);
                next.first += e.cost;
                ret = max(ret, next);
            }
        }
        return ret;
    }
};