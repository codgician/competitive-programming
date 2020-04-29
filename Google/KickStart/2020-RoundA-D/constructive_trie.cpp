#include <bits/stdc++.h>
using namespace std;

#define SIZE 4000010
#define CHAR_SIZE 26

class TrieNode {
public:
    int cnt;
    int nexts[CHAR_SIZE];
};

TrieNode trie[SIZE];
int triePt, len, siz;
long long int ans;

int newTrieNode() {
    trie[triePt].cnt = 0;
    for (int i = 0; i < CHAR_SIZE; i++)
        trie[triePt].nexts[i] = -1;
    return triePt++;
}

void insertStr(const string & str) {
    int cntPt = 0;
    for (const auto & ch : str) {
        int ch1 = ch - 'A'; 
        if (trie[cntPt].nexts[ch1] == -1)
            trie[cntPt].nexts[ch1] = newTrieNode();
        cntPt = trie[cntPt].nexts[ch1];
    }
    trie[cntPt].cnt++;
}

int dfs(int cntPt, int dep) {
    int rem = trie[cntPt].cnt;
    for (int i = 0; i < CHAR_SIZE; i++) {
        if (trie[cntPt].nexts[i] == -1)
            continue;
        rem += dfs(trie[cntPt].nexts[i], dep + 1);
    }
    ans += 1ll * (rem / siz) * dep;
    return rem % siz;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        triePt = 0; ans = 0; newTrieNode();
        cin >> len >> siz;
        for (int i = 0; i < len; i++) {
            string s; cin >> s;
            insertStr(s);
        }

        int ret = dfs(0, 0);
        assert(ret == 0);
        cout << "Case #" << t << ": " << ans << '\n';
    }

    return 0;
}