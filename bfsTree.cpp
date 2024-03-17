// keywords: tree 

// GのBFS木は、「GのBFS木に含まれないすべてのGの辺{u,v}についてuとvが祖先と子孫の関係にない」という性質を持ちます。 

// verify: https://atcoder.jp/contests/abc251/submissions/50735835

vector<P> create_bfs_tree(Graph& g, ll root = 0){
    ll n = g.size();
    vector<bool> visit(n, false);
    visit[root] = true;
    vector<P> ret;
    queue<ll> que;
    que.push(root);

    while(!que.empty()){
        ll pos = que.front();
        que.pop();
        for(ll x : g[pos]){
            if(visit[x]) continue;
            visit[x] = true;
            ret.push_back(P(pos, x));
            que.push(x);
        }
    }

    return ret;
}