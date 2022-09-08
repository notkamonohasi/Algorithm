/* key以下の最大値を持つインデックスを返す
 * vecはsort済み
 */
template<typename T>
ll getMaxIndex(vector<T>& vec, T key){
    if(vec[0] > key) return -1;
    auto it = upper_bound(all(vec), key);
    return (ll)distance(vec.begin(), it) - 1LL;
}
