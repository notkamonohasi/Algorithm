/* u->vが存在しない場合はcost[u][v]をLLONG_MAXで初期化しておく必要あり 
 * verify : https://atcoder.jp/contests/abc180/submissions/34526777 
 */
struct TSP{
    Mat cost, dp;
    ll n;
    TSP(Mat cost_) : cost(cost_), n(cost_.size()){}
    
    ll getCost(ll start){
        dp = init_mat(1 << n, n, -1);
        return getCostSub(0, start, start);
    }
    
    ll getCostSub(ll visit, ll pos, ll start){
        if(dp[visit][pos] >= 0) return dp[visit][pos];
        else{
            if(visit == (1 << n) - 1 && pos == start){
                dp[visit][pos] = 0;
                return dp[visit][pos];
            }
        }
    
        ll ret = LLONG_MAX;
        rep(i, n){
            if(cost[pos][i] == LLONG_MAX || pos == i) continue;
            if(!(visit >> i & 1)){ 
                ll nextVisit = visit | 1 << i;
                if(i == start && nextVisit != (1 << n) - 1) continue;   // ゴール状態でないのにスタート地点に戻ってくるのを防ぐ
                ll nextCost = getCostSub(nextVisit, i, start);
                if(nextCost != LLONG_MAX) ret = min(ret, nextCost + cost[pos][i]);
            }
        }
    
        if(ret != LLONG_MAX) dp[visit][pos] = ret;   // 解決不可能なルート
        return ret;
    }
};
