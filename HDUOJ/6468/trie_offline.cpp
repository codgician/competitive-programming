#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

#define SIZE 1000010
#define CHAR_SIZE 10
#define Q_SIZE 101

class TrieNode {
public:
    bool isWord;
    int nxt[CHAR_SIZE], siz;
};

TrieNode tri[SIZE << 1]; int triePt;

int newTrieNode() {
    tri[triePt].isWord = false; tri[triePt].siz = 0;
    for (int i = 0; i < CHAR_SIZE; i++)
        tri[triePt].nxt[i] = -1;
    return triePt++;
}

void insert(int num) {
    const auto toStr = [](int num) {
        string ret;
        while (num > 0)
            ret.push_back('0' + num % 10), num /= 10;
        reverse(ret.begin(), ret.end());
        return ret;
    };
    string str = toStr(num);
    int cntPt = 0, len = str.size();
    for (int i = 0; i < len; i++) {
        int cnt = str[i] - '0';
        if (tri[cntPt].nxt[cnt] == -1)
            tri[cntPt].nxt[cnt] = newTrieNode();
        tri[cntPt].siz++;
        cntPt = tri[cntPt].nxt[cnt];
    }
    tri[cntPt].siz++; tri[cntPt].isWord = true;
}

int query(int rnk) {
    int cntPt = 0, ret = 0;
    while (rnk > 0) {
        int sum = tri[cntPt].isWord;
        if (sum == rnk)
            break;
        for (int i = 0; i < CHAR_SIZE; i++) {
            if (tri[cntPt].nxt[i] == -1)
                continue;
            if (sum + tri[tri[cntPt].nxt[i]].siz >= rnk) {
                cntPt = tri[cntPt].nxt[i], ret = ret * 10 + i, rnk -= sum;
                break;
            }
            sum += tri[tri[cntPt].nxt[i]].siz;
        }
    }
    return ret;
}

class Query {
public:
    int id, n, k;
    bool operator < (const Query & snd) const {
        if (n != snd.n)
            return n < snd.n;
        return k == snd.k ? id < snd.id : k < snd.k;
    }
};

int ans[Q_SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    vector<Query> ques; 
    triePt = 0; newTrieNode();
    int qNum; cin >> qNum;
    for (int i = 0; i < qNum; i++) {
        int n, k; cin >> n >> k;
        ques.push_back(Query{i, n, k});
    }

    sort(ques.begin(), ques.end()); int cntPt = 1;
    
    for (const auto & q : ques) {
        while (cntPt <= q.n)
            insert(cntPt++);
        ans[q.id] = query(q.k);
    }

    for (int i = 0; i < qNum; i++)
        cout << ans[i] << '\n';
    return 0;
}