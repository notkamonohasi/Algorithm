// オーバーフロー対策を入れている
// verified: https://atcoder.jp/contests/abc243/submissions/50456774
Mat warshallFloyd(Mat mat, ll INF = LLONG_MAX){
    ll V = mat.size();
    rep(k, V){
        rep(i, V){
            if(mat[i][k] == LLONG_MAX) continue;
            rep(j, V){
                if(mat[k][j] == LLONG_MAX) continue;
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }
    return mat;
}
