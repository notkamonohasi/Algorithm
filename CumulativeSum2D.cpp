/* https://atcoder.jp/contests/abc203/submissions/38840235
 */

template<typename T>
struct CumulativeSum2D{
    using Mat = vector<vector<T>>; 
    Mat data;
    Mat sumMat;
    
    CumulativeSum2D(){}
    CumulativeSum2D(Mat& data_) : data(data_){ init(); }
    
    void init(){
        ll h = data.size();
        ll w = data[0].size();
        sumMat = vector<vector<T>>(h + 1, vector<T>(w + 1, (T)0));
        rep(i, h){
            rep(j, w){
                sumMat[i + 1][j + 1] = data[i][j];
            }
        }

        frep(i, 1, h + 1){
            frep(j, 1, w + 1){
                sumMat[i][j] += sumMat[i][j - 1] + sumMat[i - 1][j] - sumMat[i - 1][j - 1];
            }
        }
    }
    
    // 半開区間で与えることに注意[(sy, sx), (gy, gx))
    T query(ll sy, ll sx, ll gy, ll gx){
        return (sumMat[gy][gx] - sumMat[sy][gx] - sumMat[gy][sx] + sumMat[sy][sx]);
    }
}; 
