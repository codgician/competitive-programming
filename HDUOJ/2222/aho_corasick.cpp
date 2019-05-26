#include <bits/stdc++.h>
using namespace std;

#define CHAR_SIZE 26

typedef struct _TrieNode {
    struct _TrieNode *failPt;
    struct _TrieNode *nextArr[CHAR_SIZE];
    int count;

    _TrieNode() {
        failPt = nullptr;
        count = 0;
        for (int i = 0; i < CHAR_SIZE; i++)
            nextArr[i] = nullptr;
    }
} TrieNode;

queue<TrieNode*> q;

void insert(TrieNode * rootPt, string & str) {
    TrieNode * cntPt = rootPt;
    for (auto ch : str) {
        int cnt = ch - 'a';
        if (cntPt -> nextArr[cnt] == nullptr)
            cntPt -> nextArr[cnt] = new TrieNode();
        cntPt = cntPt -> nextArr[cnt];
    }
    cntPt -> count++;
}

void build(TrieNode * rootPt) {
    rootPt -> failPt = nullptr;
    q.push(rootPt);
    while (!q.empty()) {
        TrieNode * cntPt = q.front();
        q.pop();
        for (int i = 0; i < CHAR_SIZE; i++) {
            if (cntPt -> nextArr[i] == nullptr)
                continue;
            if (cntPt == rootPt) {
                cntPt -> nextArr[i] -> failPt = rootPt;
            } else {
                TrieNode * nextPt = cntPt -> failPt;
                while (nextPt != nullptr) {
                    if (nextPt -> nextArr[i] != nullptr) {
                        cntPt -> nextArr[i] -> failPt = nextPt -> nextArr[i];
                        break;
                    }
                    nextPt = nextPt -> failPt;
                }
                if (nextPt == nullptr)
                    cntPt -> nextArr[i] -> failPt = rootPt;
            }
            q.push(cntPt -> nextArr[i]);
        }
    }
}

void destruct(TrieNode * cntPt) {
    if (cntPt == nullptr)
        return;
    for (int i = 0; i < CHAR_SIZE; i++)
        if (cntPt -> nextArr[i] != nullptr)
            destruct(cntPt -> nextArr[i]);
    delete cntPt;
}

int query(TrieNode * rootPt, const string & str) {
    int ret = 0;
    TrieNode * cntPt = rootPt;
    for (auto ch : str) {
        int cnt = ch - 'a';
        while (cntPt -> nextArr[cnt] == nullptr && cntPt != rootPt)
            cntPt = cntPt -> failPt;
        cntPt = cntPt -> nextArr[cnt];
        if (cntPt == nullptr)
            cntPt = rootPt;

        for (TrieNode * pt = cntPt; pt != rootPt && pt -> count != -1; pt = pt -> failPt) {
            ret += pt -> count;
            pt -> count = -1;
        }
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        TrieNode * rootPt = new TrieNode();
        int num; string str;
        cin >> num;
        for (int i = 0; i < num; i++) {
            cin >> str;
            insert(rootPt, str);
        }
        build(rootPt);
        cin >> str;
        cout << query(rootPt, str) << '\n';
        destruct(rootPt);
    }

    return 0;
}