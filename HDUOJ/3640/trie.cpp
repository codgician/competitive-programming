#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 999999
using namespace std;

typedef struct _TrieNode
{
    bool isWord;
    int next[26];
} TrieNode;

TrieNode arr[SIZE];
int nextFreeNodePt = 0;

int createTrieNode()
{
    arr[nextFreeNodePt].isWord = false;
    for (int i = 0; i < 26; i++)
    {
        arr[nextFreeNodePt].next[i] = -1;
    }
    nextFreeNodePt++;
    return nextFreeNodePt - 1;
}

void insertName(string& str)
{
    int cntNodePt = 0;
    for (int i = 0; i < str.length(); i++)
    {
        int cnt = str[i] - 'a';
        if (arr[cntNodePt].next[cnt] == -1)
        {
            arr[cntNodePt].next[cnt] = createTrieNode();
        }
        cntNodePt = arr[cntNodePt].next[cnt];
    }
    arr[cntNodePt].isWord = true;
}

int main()
{
    ios::sync_with_stdio(false);
    int teamNum;
    while (cin >> teamNum)
    {
        nextFreeNodePt = 0;
        createTrieNode();
        int maxLen = 0;
        for (int i = 0; i < teamNum; i++)
        {
            string str;
            cin >> str;
            if (str.length() > maxLen)
                maxLen = str.length();
            insertName(str);
        }
        int ans = (nextFreeNodePt - 1) * 2 + teamNum - maxLen;
        cout << ans << endl;
    }
    return 0;
}
