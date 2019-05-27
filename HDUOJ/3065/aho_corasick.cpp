#include <bits/stdc++.h>
using namespace std;

#define SIZE 50010
#define STR_SIZE 1010
#define CHAR_SIZE 26

typedef struct _TrieNode {
    int failPt, id;
    int nextArr[CHAR_SIZE];
} TrieNode;

TrieNode trie[SIZE];
int triePt;

queue<int> q;
pair<string, int> arr[STR_SIZE];

int newTrieNode() {
    TrieNode & cntPt = trie[triePt];
    cntPt.failPt = -1;
    cntPt.id = -1;
    for (int i = 0; i < CHAR_SIZE; i++)
        cntPt.nextArr[i] = -1;
    return triePt++;
}

void insert(int rootPt, string & str, int cntId) {
    int cntPt = rootPt;
    for (auto ch : str) {
        int cnt = ch - 'A';
        if (trie[cntPt].nextArr[cnt] == -1)
            trie[cntPt].nextArr[cnt] = newTrieNode();
        cntPt = trie[cntPt].nextArr[cnt];
    }
    trie[cntPt].id = cntId;
}

void build(int rootPt) {
    trie[rootPt].failPt = -1;
    q.push(rootPt);
    while (!q.empty()) {
        int cntPt = q.front();
        q.pop();
        for (int i = 0; i < CHAR_SIZE; i++) {
            if (trie[cntPt].nextArr[i] == -1)
                continue;

            if (cntPt == rootPt) {
                trie[trie[cntPt].nextArr[i]].failPt = rootPt;
            } else {
                int nextPt = trie[cntPt].failPt;
                while (nextPt != -1) {
                    if (trie[nextPt].nextArr[i] != -1) {
                        trie[trie[cntPt].nextArr[i]].failPt = trie[nextPt].nextArr[i];
                        break;
                    }
                    nextPt = trie[nextPt].failPt;
                }
                if (nextPt == -1)
                    trie[trie[cntPt].nextArr[i]].failPt = rootPt;
            }
            q.push(trie[cntPt].nextArr[i]);
        }
    }
}

void query(int rootPt, const string & str) {
    int cntPt = rootPt;
    for (auto ch : str) {
        int cnt = ch - 'A';
        if (cnt < 0 || cnt >= 26) {
            cntPt = rootPt;
            continue;
        }
        while (trie[cntPt].nextArr[cnt] == -1 && cntPt != rootPt)
            cntPt = trie[cntPt].failPt;
        cntPt = trie[cntPt].nextArr[cnt];
        if (cntPt == -1)
            cntPt = rootPt;

        for (int i = cntPt; i != rootPt; i = trie[i].failPt) {
            if (trie[i].id != -1)
                arr[trie[i].id].second++;
            //trie[i].id = -1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int num;
    while (cin >> num) {
        triePt = 0;
        int rootPt = newTrieNode();
        cin.ignore();
        for (int i = 0; i < num; i++) {
            getline(cin, arr[i].first); arr[i].second = 0;
            insert(rootPt, arr[i].first, i);
        }
        build(rootPt);
        string str;
        getline(cin, str);
        query(rootPt, str);
        for (int i = 0; i < num; i++)
            if (arr[i].second > 0)
                cout << arr[i].first << ": " << arr[i].second << '\n';
    }
    return 0;
}