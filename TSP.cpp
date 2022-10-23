/* 配る型のTSP
 * もらう型の方がやや早い（1.1倍くらい）が、こちらは中途半端な状態を取得できる
 * INFの設定でエラーが出る
 * verify : https://atcoder.jp/contests/abc180/submissions/35922312   https://atcoder.jp/contests/abc274/submissions/35922274
 */
template<typename T>
struct TSP{
    using TMat = vector<vector<T>>;
    TMat cost, dp;
    ll n, m;
    T INF;
    vector<ll> memo2pow;   // 2^iをメモ
    
    TSP(TMat cost_) : cost(cost_), n(cost_.size()), memo2pow(n + 1){
        if(typeid(T) == typeid(double)) INF = DBL_MAX;
        else if(typeid(T) == typeid(ll)) INF = LLONG_MAX;
        else{
            print("type error");
            exit(EXIT_FAILURE);
        }
        rep(i, n + 1) memo2pow[i] = POW(2, i);
    }
    
    void build(ll start){
        dp = TMat(1 << n, vector<T>(n, INF));
        dp[0][start] = T(0.0);
        rep(depth, n){
            vector<ll> vec, _pos;
            makeTarget(vec, _pos, depth);
            for(ll& visit : vec){
                rep(i, n){   // 今いる場所
                    if(dp[visit][i] == INF) continue;
                    rep(j, n){   // 次いく場所
                        if(!(visit >> j & 1)){
                            T nextCost = dp[visit][i] + cost[i][j];
                            ll nextVisit = visit | memo2pow[j];
                            chmin(dp[nextVisit][j], nextCost);
                        }
                    }
                }
            }
        }
    }
    
    void makeTarget(vector<ll>& vec, vector<ll>& pos, ll& size){
        if(pos.size() == size) vec.push_back(encode(pos));
        else{
            ll last; 
            if(pos.size() != 0) last = pos[pos.size() - 1];
            else last = -1;
            frep(i, last + 1, n){
                pos.push_back(i);
                makeTarget(vec, pos, size);
                pos.pop_back();
            }
        }
    }
    
    ll encode(vector<ll>& v){
        ll ret = 0;
        for(ll& x : v) ret += memo2pow[x];
        return ret;
    }
    
    T get(ll visit, ll pos){return dp[visit][pos];}
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
