// keywords: なもり、グラフ、木
// verify: https://atcoder.jp/contests/abc266/submissions/51271166

// n頂点n辺からなる連結無向グラフ
struct Namori{
    Graph g;
    vector<ll> loop;  // 閉路内のidx
    vector<ll> par;  // 木の根

    Namori(const Graph& g_) : g(g_){ init(); }

    // 閉路と閉路内の頂点に付属する木に分割する
    void init(){
        ll n = g.size();
        loop = find_loop();
        par.resize(n, -1);
        vector<bool> visit(n, false);
        for(ll x : loop) visit[x] = true;

        for(ll x : loop){
            ll count = 0;
            queue<ll> que;
            que.push(x);
            while(!que.empty()){
                ll pos = que.front();
                que.pop();
                if(visit[pos] && count != 0) continue;
                visit[pos] = true;
                count++;
                par[pos] = x;
                for(ll next : g[pos]){ 
                    que.push(next);
                }
            }
        }

        rep(i, n) assert(par[i] >= 0);
    }

    // グラフ内に一つ存在するループを検出する
    vector<ll> find_loop(){
        ll n = g.size();
        vector<bool> is_in_loop(n, true);
        vector<ll> deg(n, 0);
        queue<ll> que;
        rep(i, n){
            if(g[i].size() == 1){
                is_in_loop[i] = false;
                que.push(i);
            }
            deg[i] = g[i].size();
        }
        while(!que.empty()){
            ll pos = que.front();
            que.pop();
            for(ll next : g[pos]){
                if(!is_in_loop[next]) continue;
                deg[next]--;
                if(deg[next] <= 1){
                    is_in_loop[next] = false;
                    que.push(next);
                }
            }
        }

        vector<ll> ret;
        rep(i, n){
            if(is_in_loop[i]) ret.push_back(i);
        }
        return ret;
    }
};