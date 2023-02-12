/* 未verify
 */

template<typename T>
struct Tree{
    struct Edge{ll to; T cost;}; 
    using Graph = vector<vector<Edge> >;
    Graph g;
    ll V; 
    
    Tree(){}
    Tree(ll V_) : V(V_){
        g = vector<vector<Edge>>(V); 
    }
    
    void add(ll from, ll to, T cost){
        g[from].push_back({to, cost}); 
    }
    
    // sからの距離を計算する
    vector<T> calcDist(ll s){
        vector<T> dist(V, -1); 
        dist[s] = 0;
        queue<ll> que;
        que.push(s);
        while(!que.empty()){
            ll pos = que.front();
            que.pop(); 
            for(Edge& edge : g[pos]){
                ll next = edge.to;
                if(dist[next] < 0){
                    dist[next] = dist[pos] + edge.cost;
                    que.push(next); 
                }
            }
        }
        return dist;
    }
}; 
