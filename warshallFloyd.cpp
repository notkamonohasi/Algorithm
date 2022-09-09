Mat warshallFloyd(Mat mat){
    ll V = mat.size();
    rep(k, V){
        rep(i, V){
            rep(j, V){
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }
    return mat;
}
