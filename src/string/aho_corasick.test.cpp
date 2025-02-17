// 9250
#include<bits/stdc++.h>

using namespace std;

struct AhoCorasick {
    struct Trie {
        Trie *nxt[26];
        Trie *fail;
        bool output;

        Trie() {
            for(int i=0;i<26;++i) nxt[i]=nullptr;
            fail=nullptr;
            output=false;
        }
        ~Trie() {
            for(int i=0;i<26;++i) if(nxt[i]) delete nxt[i];
        }
    } *root;
    AhoCorasick() { root = new Trie(); }
    void insert(const string &S) {
        Trie *cur = root;
        int N = (int)S.size();
        for(int i = 0; i < N; ++i) {
            int nxt = S[i] - 'a';
            if(cur->nxt[nxt] == nullptr) cur->nxt[nxt] = new Trie();
            cur = cur->nxt[nxt];
        }
        cur->output=true;
    }
    void build() {
        queue<Trie*> Q;
        root->fail = root;
        Q.push(root);
        while(!Q.empty()) {
            Trie* cur = Q.front(); Q.pop();

            for(int i = 0; i < 26; ++i) {
                Trie *next = cur->nxt[i];
                if(next == nullptr) continue;
                if(cur == root) next->fail = root;
                else {
                    Trie *dst = cur->fail;
                    while(dst != root && dst->nxt[i] == nullptr) dst = dst->fail;
                    if(dst->nxt[i]) dst = dst->nxt[i];
                    next->fail = dst;
                }
                if(next->fail->output) next->output = true;
                Q.push(next);
            }
        }
    }
    bool find(const string &S) {
        Trie *cur = root;
        int N = (int)S.size();
        for(int i = 0; i < N; ++i) {
            int nxt = S[i] - 'a';
            while(cur != root && cur->nxt[nxt] == nullptr) cur = cur->fail;
            if(cur->nxt[nxt]) cur = cur->nxt[nxt];
            if(cur->output) return true;
        }
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N; cin >> N;
    AhoCorasick aho;
    for(int i = 0; i < N; ++i) {
        string S; cin >> S;
        aho.insert(S);
    }
    aho.build();
    int M; cin >> M;
    for(int i = 0; i < M; ++i) {
        string S; cin >> S;
        if(aho.find(S)) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}