/* 最小費用流
 * パクリ : https://ei1333.github.io/luzhiled/snippets/graph/primal-dual.html 
 * verify : https://onlinejudge.u-aizu.ac.jp/status/users/notkamonohasi/submissions/1/GRL_6_B/judge/6940073/C++17
 */
 
template< typename flow_t, typename cost_t >
struct PrimalDual {
  const cost_t INF;

  struct edge {
    ll to;
    flow_t cap;
    cost_t cost;
    ll rev;
    bool isrev;
  };
  vector< vector< edge > > graph;
  vector< cost_t > potential, min_cost;
  vector< ll > prevv, preve;

  PrimalDual(ll V) : INF(numeric_limits< cost_t >::max()), graph(V) {}

  void add_edge(ll from, ll to, flow_t cap, cost_t cost) {
    graph[from].emplace_back((edge) {to, cap, cost, (ll) graph[to].size(), false});
    graph[to].emplace_back((edge) {from, 0, -cost, (ll) graph[from].size() - 1, true});
  }

  cost_t min_cost_flow(ll s, ll t, flow_t f) {
    ll V = (ll) graph.size();
    cost_t ret = 0;
    using Pi = pair< cost_t, ll >;
    priority_queue< Pi, vector< Pi >, greater< Pi > > que;
    potential.assign(V, 0);
    preve.assign(V, -1);
    prevv.assign(V, -1);

    while(f > 0) {
      min_cost.assign(V, INF);
      que.emplace(0, s);
      min_cost[s] = 0;
      while(!que.empty()) {
        Pi p = que.top();
        que.pop();
        if(min_cost[p.second] < p.first) continue;
        for(ll i = 0; i < graph[p.second].size(); i++) {
          edge &e = graph[p.second][i];
          cost_t nextCost = min_cost[p.second] + e.cost + potential[p.second] - potential[e.to];
          if(e.cap > 0 && min_cost[e.to] > nextCost) {
            min_cost[e.to] = nextCost;
            prevv[e.to] = p.second, preve[e.to] = i;
            que.emplace(min_cost[e.to], e.to);
          }
        }
      }
      if(min_cost[t] == INF) return -1;
      for(ll v = 0; v < V; v++) potential[v] += min_cost[v];
      flow_t addflow = f;
      for(ll v = t; v != s; v = prevv[v]) {
        addflow = min(addflow, graph[prevv[v]][preve[v]].cap);
      }
      f -= addflow;
      ret += addflow * potential[t];
      for(ll v = t; v != s; v = prevv[v]) {
        edge &e = graph[prevv[v]][preve[v]];
        e.cap -= addflow;
        graph[v][e.rev].cap += addflow;
      }
    }
    return ret;
  }

  void output() {
    for(ll i = 0; i < graph.size(); i++) {
      for(auto &e : graph[i]) {
        if(e.isrev) continue;
        auto &rev_e = graph[e.to][e.rev];
        cout << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << rev_e.cap + e.cap << ")" << endl;
      }
    }
  }
};


int main(){
    ll v, e, f;
    cin >> v >> e >> f;
    PrimalDual<ll, ll> pd(v);
    rep(i, e){
        ll u, v, c, d;
        cin >> u >> v >> c >> d;
        pd.add_edge(u, v, c, d);
    }
    print(pd.min_cost_flow(0, v - 1, f));
}
