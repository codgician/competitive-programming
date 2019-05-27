#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
#define CHAR_SIZE 128

typedef struct _TrieNode {
    int failPt, id;
    int nextArr[CHAR_SIZE];
} TrieNode;

TrieNode trie[SIZE];
int triePt;

queue<int> q;
vector<int> vec;

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
        int cnt = ch;
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

bool query(int rootPt, const string & str) {
    bool ret = false;
    int cntPt = rootPt;
    for (auto ch : str) {
        int cnt = ch;
        while (trie[cntPt].nextArr[cnt] == -1 && cntPt != rootPt)
            cntPt = trie[cntPt].failPt;
        cntPt = trie[cntPt].nextArr[cnt];
        if (cntPt == -1)
            cntPt = rootPt;

        for (int i = cntPt; i != rootPt; i = trie[i].failPt) {
            if (trie[i].id != -1) {
                ret = true;
                vec.push_back(trie[i].id);
            }
            //trie[i].id = -1;
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int num;
    while (cin >> num) {
        cin.ignore();
        triePt = 0;
        int rootPt = newTrieNode();

        for (int i = 1; i <= num; i++) {
            string str;
            getline(cin, str);
            insert(rootPt, str, i);
        }
        build(rootPt);
        cin >> num; int ans = 0;
        cin.ignore();
        for (int i = 1; i <= num; i++) {
            string str;
            getline(cin, str);
            vec.clear();
            if (query(rootPt, str)) {
                ans++;
                sort(vec.begin(), vec.end());
                cout << "web " << i << ": ";
                cout << vec[0];
                for (int i = 1; i < (int)vec.size(); i++)
                    cout << " " << vec[i];
                cout << '\n'; 
            }
        }
        cout << "total: " << ans << '\n';
    }

    return 0;
}