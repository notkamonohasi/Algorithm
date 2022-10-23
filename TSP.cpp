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
