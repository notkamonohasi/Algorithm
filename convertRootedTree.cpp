// keywords: 根付き木, 木

// verify: https://atcoder.jp/contests/abc348/submissions/52097845

// 木を根付き木に変換する
Graph convertRootedTree(Graph& g, ll root = 0){
    ll size = g.size();
    Graph ret = init_graph(size);
    vector<bool> visit(size, false);
    visit[root] = true;
    queue<ll> que;
    que.push(root);
    while(!que.empty()){
        ll pos = que.front();
        que.pop();
        for(auto x : g[pos]){
            if(visit[x] == true) continue;
            else{
                visit[x] = true;
                ret[pos].push_back(x);
                que.push(x);
            }
        }
    }
    return ret;
}
