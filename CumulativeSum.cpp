/* verify : https://atcoder.jp/contests/abc129/submissions/38778444
 */

template<typename T>
struct CumulativeSum{
    vector<T> v, sum; 
    ll n;
    
    CumulativeSum(){}
    CumulativeSum(vector<T>& v_) : v(v_){ init(); }
    
    void init(){
        n = v.size(); 
        sum.resize(n + 1, (T)0);
        rep(i, n) sum[i + 1] = sum[i] + v[i];
    }
    
    // [a, b)の和を出力
    T query(ll a, ll b){ return sum[b] - sum[a]; }
    
    // [0, b)の和を出力
    T query(ll b){ return sum[b]; }
    
    // 全ての和
    T getAllSum(){ return sum[n]; }
}; 
