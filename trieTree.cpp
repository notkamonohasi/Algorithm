// keywords: suffix, prefix, 最長共通接頭辞

// verify: https://atcoder.jp/contests/ABC353/submissions/53404572

// 参考: https://algo-logic.info/trie-tree/

// memo: IDEの予測が効かない...


/* Trie 木： 文字の種類(char_size)、int型で0に対応する文字(base)
    insert(word): 単語 word を Trie 木に挿入する
    search(word): 単語 word が Trie 木にあるか判定する
    start_with(prefix):  prefix が一致する単語が Trie 木にあるか判定する
    count(): 挿入した単語の数を返す
    size(): Trie 木の頂点数を返す
    計算量：insert, search ともに O(M)（Mは単語の長さ）
*/
template <ll char_size, ll base>
struct Trie {
    struct Node {            // 頂点を表す構造体
        vector<ll> next;    // 子の頂点番号を格納。存在しなければ-1
        vector<ll> accept;  // 末端がこの頂点になる単語の word_id を保存
        ll c;               // base からの間隔をll型で表現したもの
        ll common;          // いくつの単語がこの頂点を共有しているか
        Node(ll c_) : c(c_), common(0) {
            next.assign(char_size, -1);
        }
    };

    vector<Node> nodes;  // trie 木本体
    ll root;
    Trie() : root(0) {
        nodes.push_back(Node(root));
    }

    // 単語の挿入
    void insert(const string &word, ll word_id) {
        ll node_id = 0;
        for (ll i = 0; i < (ll)word.size(); i++) {
            ll c = (ll)(word[i] - base);
            ll &next_id = nodes[node_id].next[c];
            if (next_id == -1) {  // 次の頂点が存在しなければ追加
                next_id = (ll)nodes.size();
                nodes.push_back(Node(c));
            }
            ++nodes[node_id].common;
            node_id = next_id;
        }
        ++nodes[node_id].common;
        nodes[node_id].accept.push_back(word_id);
    }
    void insert(const string &word) {
        insert(word, nodes[0].common);
    }

    // 単語とprefixの検索
    bool search(const string &word, bool prefix = false) {
        ll node_id = 0;
        for (ll i = 0; i < (ll)word.size(); i++) {
            ll c = (ll)(word[i] - base);
            ll &next_id = nodes[node_id].next[c];
            if (next_id == -1) {  // 次の頂点が存在しなければ終了
                return false;
            }
            node_id = next_id;
        }
        return (prefix) ? true : nodes[node_id].accept.size() > 0;
    }

    // prefix を持つ単語が存在するかの検索
    bool start_with(const string &prefix) {
        return search(prefix, true);
    }

    // 挿入した単語の数
    ll count() const {
        return (nodes[0].common);
    }
    // Trie木のノード数
    ll size() const {
        return ((ll)nodes.size());
    }
};
