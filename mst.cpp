
// keywords: 最小全域木

// verify: https://atcoder.jp/contests/ABC270/submissions/51466797

struct Kruskal{
    vector<Edge> edge_vec;
    ll min_cost;
    ll V;

    Kruskal(const vector<Edge>& edge_vec_, ll V_) : edge_vec(edge_vec_), V(V_){ init(); }

    void init(){
        sort(edge_vec.begin(), edge_vec.end());
        DisjointSet ds(V);
        min_cost = 0;
        for(auto e : edge_vec){
            if(!ds.same(e.from, e.to) || e.cost < 0){
                ds.unite(e.from, e.to);
                min_cost += e.cost;
            }
        }

        // 連結であるかをチェックする
        for(int i = 0; i < V; i++){
            if(!ds.same(0, i)) min_cost = LLONG_MAX;
        }
    }
};
