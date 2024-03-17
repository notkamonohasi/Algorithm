// keywords: ランレングス圧縮

// verify: https://atcoder.jp/contests/abc259/submissions/50987895 

vector<pair<char, ll>> run_length_encode(string& s){
  vector<pair<char, ll>> v;
  char prev;
  ll count = 0;
  for(ll i = 0; i < s.size(); i++){
    char c = s[i];
    if(i == 0){
      prev = c; 
      count++;
    }
    else if(c == prev) count++;
    else{
      v.push_back(make_pair(prev, count));
      prev = c;
      count = 1;
    }
  }
  v.push_back(make_pair(prev, count));
  return v;
}