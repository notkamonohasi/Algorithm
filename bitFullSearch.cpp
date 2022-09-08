/* メモリを大量に食うので怒られる場合あり */
Mat bitFullSearch(ll a){
    ll size = (1 << a);
    Mat ret = init_mat(size, a);
    rep(bit, size){
        rep(i, a){
            if(bit & (1 << i)) ret[bit][i] = 1; 
            else ret[bit][i] = 0;
        }
    }
    return ret;
}
