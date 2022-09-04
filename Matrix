/* 行列計算ライブラリ 
 * 未verify
 */

Mat matMul(Mat& a, Mat& b, ll mod = -1){
    ll size1 = a.size();
    ll size2 = b[0].size();
    ll size3 = b.size();
    Mat ret = init_mat(size1, size2);
    rep(i, size1){
        rep(j, size2){
            rep(k, size3){
                ret[i][j] += a[i][k] * b[k][j];
                if(mod > 0) ret[i][j] %= MOD;
            }
        }
    }
    return ret;
}

void matMod(Mat& a, ll mod){
    ll size1 = a.size();
    ll size2 = a[0].size();
    rep(i, size1){
        rep(j, size2){
            a[i][j] %= mod;
        }
    }
}

Mat matPow(Mat a, ll n, ll mod = -1){
    ll size1 = a.size();
    ll size2 = a[0].size();
    Mat ret = init_mat(size1, size2, 1);
    while(n > 0){
        if(n & 1) ret = matMul(ret, a, mod);
        a = matMul(a, a, mod);
        n >>= 1;
    }
    return ret;
}

int main(){
    /* フィボナッチの第10項を求める */
    Mat mat = init_mat(2, 2);
    mat[0][0] = 1;
    mat[0][1] = 1;
    mat[1][0] = 1;
    mat[1][1] = 0;
    Mat a = matPow(mat, 8);
    Mat b = init_mat(2, 1);
    b[0][0] = 1;
    b[1][0] = 0;
    Mat c = matMul(a, b);
    print(c[0][0]);
}
