// keywords: 最短距離

// verify: https://judge.yosupo.jp/submission/197142

struct Dijkstra{
    EdgeGraph g;
    ll start;
    vector<ll> dist, prev;

    Dijkstra(const EdgeGraph& g_, ll start_) : g(g_), start(start_){ init(); }

    void init(){
        ll N = g.size();
        dist.resize(N, LLONG_MAX);   
        prev.resize(N, -1); // 初期化
        vector<bool> visit(N, false);  // 確定
        IQ<P> pq; 
        dist[start] = 0;
        pq.push(P(dist[start], start));
        while(!pq.empty()){
            P p = pq.top();
            pq.pop();
            ll v = p.second;
            if(visit[v]) continue;   // これがないと確定済み地点を何回も見ることになる
            visit[v] = true;
            for(auto &e : g[v]){
                ll next_cost = dist[v] + e.cost;
                if(!visit[e.to] && dist[e.to] > next_cost){
                    dist[e.to] = next_cost;
                    prev[e.to] = v; // 頂点 v を通って e.to にたどり着いた
                    pq.push(P(next_cost, e.to));
                }
            }
        }
    }

    // goalからstartへの経路を復元する
    vector<ll> get_path(ll goal){
        vector<ll> ret;
        ll pos = goal;
        while(pos >= 0){
            ret.push_back(pos);
            pos = prev[pos];
        }
        reverse(all(ret));
        return ret;
    }

    // startからtへの距離を取得する
    ll get_dist(ll t){ return dist[t]; }
};