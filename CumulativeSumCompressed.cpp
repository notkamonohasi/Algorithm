// keywords: いもす法, imos法, 座標圧縮, 座圧, 累積和, CumulativeSum
// verify: https://atcoder.jp/contests/ABC365/submissions/56336977
//         https://atcoder.jp/contests/abc188/submissions/56336265
// どちらも微妙にclassの中をいじる必要があった

/**
 * 座標圧縮してからいもす法をして累積和を計算
 * 大きい かつ staticなケースで遅延セグ木のようなことをしたいときに有効
 * compressorの計算量が大きいことに注意
 */

struct Compressor{
    unordered_map<ll, ll> encoder;
    vector<ll> decoder;

    Compressor(){}
    Compressor(vector<ll>& v){
        auto tmp = compress(v);
        ll m = *max_element(tmp.begin(), tmp.end());
        decoder.resize(m + 1);
        for(ll i = 0; i < v.size(); i++){
            encoder[v[i]] = tmp[i];
            decoder[tmp[i]] = v[i]; 
        }
    }

    ll encode(ll x){
        auto it = encoder.find(x);
        assert(it != encoder.end());
        return it->second;
    }

    ll decode(ll x){
        assert(x < decoder.size());
        return decoder[x];
    }

    ll size(){ return decoder.size(); }

    vector<ll> compress(vector<ll> X) {
        vector<ll> vals = X;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        for (ll i = 0; i < (ll)X.size(); i++) {
            X[i] = lower_bound(vals.begin(), vals.end(), X[i]) - vals.begin();
        }
        return X;
    }
};

struct Event{
    ll start;
    ll end;
    ll value;
};

struct CompressedCumulativeSum{
    vector<ll> records;  // 登場するすべての数字
    vector<Event> events;  // 見たい対象のevent
    Compressor compressor;
    vector<ll> values;

    ll START = -1;  // const や static const にすると面倒
    
    CompressedCumulativeSum(vector<ll>& records_, vector<Event>& events_){
        records = records_;
        for(ll x : records) assert(x >= 0);  // startを-1に設定しているため
        records.push_back(START);
        events = events_;

        compressor = Compressor(records);

        ll m = compressor.size();
        vector<ll> tmp(m);
        for(Event e : events){
            tmp[compressor.encode(e.start)] += e.value;
            tmp[compressor.encode(e.end)] -= e.value;
        }

        vector<ll> imos(m, 0);
        values.resize(m, 0);
        for(ll i = 0; i < m - 1; i++){
            imos[i + 1] = imos[i] + tmp[i];
            values[i + 1] = values[i] + imos[i + 1] * (compressor.decode(i + 1) - compressor.decode(i));
        }
    }

    // [start, end)を計算
    ll query(ll start, ll end){
        return values[compressor.encode(end)] - values[compressor.encode(start)];
    }

    // [0, startを計算)
    ll query(ll end){
        return query(START, end);
    }
};
