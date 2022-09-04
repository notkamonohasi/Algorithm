/* 最大流（FordFulkerson）
 * パクリ : https://algo-logic.info/bipartite-matching/ 
 * verify : https://onlinejudge.u-aizu.ac.jp/status/users/kamonohasi/submissions/1/GRL_6_A/judge/6940063/C++17
 */
/* FordFulkerson: Ford-Fulkersonのアルゴリズムで最大流を求める構造体
    max_flow(G,s,t)：sからtへのグラフGの最大流を求める
    副作用：G は最大流の残余ネットワークになる
    計算量: O(|f*||E|) (f*:最大流) (この最悪ケースになることはほぼ無い)
*/
template <class T>
struct FordFulkerson {
    struct Edge {
        ll rev, from, to;  // rev:逆向きの辺の番号
        T cap, original_cap;
        Edge(ll r, ll f, ll t, T c) : rev(r), from(f), to(t), cap(c), original_cap(c) {}
    };
    
    struct Graph {
        vector<vector<Edge>> G;
        Graph(ll n = 0) : G(n) {}
        vector<Edge>& operator[](ll i) { return G[i]; }
        const size_t size() const { return G.size(); }
        Edge& redge(Edge e) {  // 逆向きの辺を返す
            return G[e.to][e.rev];   // 自己ループはないと仮定（あれば G[e.to][e.rev + 1] とする必要がある）
        }
        void add_edge(ll from, ll to, T cap) {  // 有向辺を加える
            G[from].push_back(Edge((ll)G[to].size(), from, to, cap));
            G[to].push_back(Edge((ll)G[from].size() - 1, to, from, 0));
        }
    };
    
    const T INF = LLONG_MAX;   // オーバーフローの危険あり
    Graph G;
    vector<ll> used;

    FordFulkerson(ll n) : G(Graph(n)){};
    void add_edge(ll from, ll to, T cap){ G.add_edge(from, to, cap); }
    
    T dfs(ll v, ll t, T f) {  // 増加可能経路を見つけて増加分のフローを返す
        if (v == t) return f;
        used[v] = true;
        for (auto& e : G[v]) {
            if (!used[e.to] && e.cap > 0) {
                T d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G.redge(e).cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    T max_flow(ll s, ll t) {
        T flow = 0;
        while (true) {
            used.assign(G.size(), 0);
            T f = dfs(s, t, INF);  // f が増加分のフロー
            if (f == 0) {
                return flow;
            } else {
                flow += f;
            }
        }
        return 0;
    }
};

int main(){
    ll v, e;
    cin >> v >> e;
    FordFulkerson<ll> ff(v);
    rep(i, e){
        ll a, b, c;
        cin >> a >> b >> c;
        ff.add_edge(a, b, c);
    }
    print(ff.max_flow(0, v - 1));
}
