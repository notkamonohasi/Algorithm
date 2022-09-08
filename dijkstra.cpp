struct Edge{ll to, cost;};
using Graph = vector<vector<Edge> >;
Graph init_graph(ll V){Graph ret; vector<Edge> empty; rep(i, V) ret.push_back(empty); return ret;}

void dijkstra(const Graph& G, ll s, vector<ll>& dis, vector<ll>& prev) {
    ll N = G.size();
    dis.resize(N, INT_MAX);  // LLONG_MAXにすると壊れる。場合によってはINT_MAXだと危険かも
    prev.resize(N, -1); // 初期化
    priority_queue<P, vector<P>, greater<P>> pq; 
    dis[s] = 0;
    pq.emplace(dis[s], s);
    while(!pq.empty()){
        P p = pq.top();
        pq.pop();
        ll v = p.second;
        if(dis[v] < p.first){
            continue;
        }
        for(auto &e : G[v]){
            if(dis[e.to] > dis[v] + e.cost){
                dis[e.to] = dis[v] + e.cost;
                prev[e.to] = v; // 頂点 v を通って e.to にたどり着いた
                pq.emplace(dis[e.to], e.to);
            }
        }
    }
}

// tへの最短path
vector<ll> get_path(const vector<ll>& prev, ll t){
    vector<ll> path;
    for(ll cur = t; cur != -1; cur = prev[cur]){
        path.push_back(cur);
    }
    reverse(path.begin(), path.end()); // 逆順なのでひっくり返す
    return path;
}
