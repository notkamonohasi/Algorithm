/* 計算量 : O(E + V)
 * verify : https://atcoder.jp/contests/abc222/submissions/44250371, https://atcoder.jp/contests/abc213/submissions/44250167
 */


struct BFS01{
    vector<ll> prev, dist;
    ll V; 
    ll start; 

    BFS01(){}

    // EdgeGraphをclass変数に持つと初期化コストが大きくなるので、都度引数にいれることにする
    vector<ll> build(const EdgeGraph& edge_graph, ll start_){
        start = start_; 
        V = edge_graph.size(); 
        prev.resize(V, -1); 
        dist.resize(V, INT_MAX); 
        
        deque<ll> dq;
        dq.push_back(start); 
        dist[start] = 0; 

        while(!dq.empty()){
            ll pos = dq.front(); 
            dq.pop_front(); 
            ll cost = dist[pos]; 
            for(const Edge& e : edge_graph[pos]){
                ll next_cost = cost + e.cost; 
                if(dist[e.to] > next_cost){
                    dist[e.to] = next_cost; 
                    prev[e.to] = pos;

                    // コストが0なら前に入れ、1なら後ろに入れる
                    if(e.cost) dq.push_back(e.to); 
                    else dq.push_front(e.to); 
                }
            }
        }

        return dist; 
    }

    // 経路を復元する
    vector<ll> get_path(ll goal){
        ll pos = goal;
        vector<ll> ret;  
        while(pos != -1){
            ret.push_back(pos); 
            pos = prev[pos]; 
        }
        reverse(all(ret));
        assert(ret[0] == start); 
        return ret; 
    }
}; 
