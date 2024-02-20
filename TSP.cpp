/* 配る型のTSP
 * verify : https://atcoder.jp/contests/abc180/submissions/50469749
 */
template<typename T>
class TSP{
public:
    using TMat = vector<vector<T>>;
    TMat cost;  // i->jのコスト
    T INF;  // 到達不可能などをコントロール

    TMat dp;
    ll n;  // 地点数
    vector<ll> pow2vec;  // 2^iをメモ
    ll start;

    TSP(TMat& cost_, T INF_ = LLONG_MAX) : cost(cost_), INF(INF_){
        n = cost.size();
        pow2vec.resize(n);
        rep(i, n) pow2vec[i] = (1 << i);
    }

    /* `start_`を出発地点とした時のdp[i][j]を構築 */
    void build(ll start_){
        start = start_;
        const ll SIZE = (1 << n);
        dp = TMat(SIZE, vector<T>(n, INF));
        dp[0][start] = T(0);

        rep(i, SIZE){
            rep(j, n){
                if(dp[i][j] == INF) continue;  // 到達不可能
                rep(k, n){
                    if(cost[j][k] == INF) continue;  // j->kに辺が貼られていない
                    else if(i & pow2vec[k] != 0) continue;  // 既にkを訪問している
                    else{
                        ll next = i | pow2vec[k];
                        dp[next][k] = min(dp[next][k], dp[i][j] + cost[j][k]);
                    }
                }
            }
        }
    }

    /* 一周の最短距離を取得。`build()`が実行されている必要あり */
    T get(){ return dp[(1 << n) - 1][start]; }
};



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
