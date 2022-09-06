/* DFSで帰りがけ順を作成する
 * verify : https://atcoder.jp/contests/abc036/submissions/34656001
 * functionが重いことに注意
 */
 
 queue<ll> makePostOrder(Graph& g, ll root = 0){
    ll n = g.size();
    vector<ll> visit(n, false);
    queue<ll> ret;
    function<void(ll)> f = [&](ll pos){
        if(visit[pos]) return;
        visit[pos] = true;
        for(auto x : g[pos]) f(x);
        ret.push(pos);
    };
    f(root);
    return ret;
}
