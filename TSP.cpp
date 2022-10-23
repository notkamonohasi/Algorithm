/* u->vが存在しない場合はcost[u][v]をLLONG_MAXで初期化しておく必要あり 
 * costの型はlong longかdoubleである必要がある
 * INFの設定周りでコンパイルエラーがめっちゃでる
 * verify : https://atcoder.jp/contests/abc180/submissions/35913642
 */
template<typename T>
struct TSP{
    using TMat = vector<vector<T>>;
    TMat cost, dp;
    ll n;
    T INF;
    TSP(TMat cost_) : cost(cost_), n(cost_.size()){
        if(typeid(T) == typeid(double)) INF = DBL_MAX;
        else if(typeid(T) == typeid(ll)) INF = LLONG_MAX;
        else{
            print("type error");
            exit(EXIT_FAILURE);
        }
    }
    
    T getCost(ll start){
        dp = TMat(1 << n, vector<T>(n, -1));
        return getCostSub(0, start, start);
    }
    
    T getCostSub(ll visit, ll pos, ll start){
        if(dp[visit][pos] >= 0) return dp[visit][pos];
        else{
            if(visit == (1 << n) - 1 && pos == start){
                dp[visit][pos] = 0;
                return dp[visit][pos];
            }
        }

        T ret = INF;
        rep(i, n){
            if(cost[pos][i] == INF || pos == i) continue;
            if(!(visit >> i & 1)){ 
                ll nextVisit = visit | 1 << i;
                if(i == start && nextVisit != (1 << n) - 1) continue;   // ゴール状態でないのにスタート地点に戻ってくるのを防ぐ
                T nextCost = getCostSub(nextVisit, i, start);
                if(nextCost != INF && cost[pos][i] != INF) ret = min(ret, nextCost + cost[pos][i]);
            }
        }
    
        if(ret != INF) dp[visit][pos] = ret;   // 解決不可能なルート
        return ret;
    }
};


/* 配る型のTSP
 * 上のメモ再帰より10倍ほど遅いが、中途半端な状態のコストも計算できる
 * verify : https://atcoder.jp/contests/abc180/submissions/35920936 
 */
template<typename T>
struct TSP{
    using TMat = vector<vector<T>>;
    TMat cost, dp;
    ll n;
    T INF;
    
    struct State{
        ll visit, pos;
        T cost;
        State(){}
        State(ll visit_, ll pos_, T cost_) : visit(visit_), pos(pos_), cost(cost_){}
        
        bool operator > (const State& another) const{return cost > another.cost;}
        bool operator < (const State& another) const{return cost < another.cost;}
    };
    
    TSP(TMat cost_) : cost(cost_), n(cost_.size()){
        if(typeid(T) == typeid(double)) INF = DBL_MAX;
        else if(typeid(T) == typeid(ll)) INF = LLONG_MAX;
        else{
            print("type error");
            exit(EXIT_FAILURE);
        }
    }
    
    void build(ll start){
        dp = TMat(1 << n, vector<T>(n, INF));
        IQ<State> pq;
        State firstState(0, start, double(0.0));
        pq.push(firstState);
        while(!pq.empty()){
            State state = pq.top();
            pq.pop();
            ll visit = state.visit;
            ll pos = state.pos;
            ll posCost = state.cost;
            if(dp[visit][pos] < posCost) continue;
            rep(i, n){
                if(!(visit >> i & 1)){ 
                    T nextCost = posCost + cost[pos][i];
                    ll nextVisit = visit | 1 << i;
                    if(dp[nextVisit][i] > nextCost){
                        dp[nextVisit][i] = nextCost;
                        State nextState(nextVisit, i, nextCost);
                        pq.push(nextState);
                    }
                }
            }
        }
    }
    
    T get(ll visit, ll pos){return dp[visit][pos];}
};
