// keywords: 木

// GのDFS木は、「GのDFS木に含まれないすべてのGの辺{u,v}についてuとvが祖先と子孫の関係にある」という性質を持ちます。 

// verify: https://atcoder.jp/contests/abc251/submissions/50735835

vector<P> create_dfs_tree(Graph& g, ll root = 0){
    ll n = g.size();
    vector<bool> visit(n, false);
    visit[root] = true;
    vector<P> ret;
    
    function<void(ll)> dfs = [&](ll pos) -> void {
        for(ll x : g[pos]){
            if(!visit[x]){
                visit[x] = true;
                ret.push_back(P(pos, x));
                dfs(x);
            }
        }
    };
    dfs(root);

    return ret;
}