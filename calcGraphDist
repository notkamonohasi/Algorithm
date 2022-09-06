/* verify : https://atcoder.jp/contests/abc070/submissions/34656290
 */
 
struct Edge{ll to, cost;};
using Graph = vector<vector<Edge> >;
Graph init_graph(ll V){Graph ret; vector<Edge> empty; rep(i, V) ret.push_back(empty); return ret;}
vector<ll> calcGraphDist(Graph& g, ll k){
    ll n = len(g);
    vector<ll> ret(n), visit(n, false);
    ret[k] = 0;
    queue<ll> que;
    que.push(k);
    while(!que.empty()){
        ll pos = que.front();
        que.pop();
        ll c = ret[pos];
        if(visit[pos]) continue;
        visit[pos] = true;
        for(auto e : g[pos]){
            ll to = e.to;
            if(visit[to]) continue;
            ret[to] = c + e.cost;
            que.push(to);
        }
    }
    return ret;
}
