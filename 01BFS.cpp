/* 計算量 : O(E + V)
 * verify : https://atcoder.jp/contests/abc213/submissions/34891632 
 */

struct Edge{ll to, cost;};
using Graph = vector<vector<Edge> >;
Graph init_graph(ll V){Graph ret; vector<Edge> empty; rep(i, V) ret.push_back(empty); return ret;}

vector<ll> bfs(Graph& g, ll start){
    ll size = g.size();
    vector<ll> opt(size, INT_MAX);

    deque<Edge> dq;
    Edge first{start, 0};
    opt[start] = 0;
    dq.push_back(first);
    
    while(!dq.empty()){
        Edge e = dq.front();
        dq.pop_front();
        
        for(Edge e2 : g[e.to]){
            ll nextCost = e.cost + e2.cost;
            if(nextCost < opt[e2.to]){
                opt[e2.to] = nextCost;
                Edge next{e2.to, nextCost};
                if(e2.cost == 0) dq.push_front(next);
                else dq.push_back(next);
            }
        }
    }
    return opt;
}
