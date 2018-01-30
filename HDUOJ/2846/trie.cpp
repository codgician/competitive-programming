#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 999999
using namespace std;

typedef struct _TrieNode
{
    int lastStrId;
    int num;
    int next[26];
    bool isWord;
} TrieNode;
TrieNode arr[SIZE];

int nextFreePt = 0;

int createTrieNode()
{
    arr[nextFreePt].lastStrId = -1;
    arr[nextFreePt].num = 0;
    arr[nextFreePt].isWord = false;
    for (int i = 0; i < 26; i++)
    {
        arr[nextFreePt].next[i] = -1;
    }
    return nextFreePt++;
}

void insertName(string& str, int cntStrId)
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
        if (arr[cntNodePt].lastStrId != cntStrId)
        {
            arr[cntNodePt].num++;
            arr[cntNodePt].lastStrId = cntStrId;
        }
    }
    arr[cntNodePt].isWord = true;
}

int getNum(string& str)
{
    int cntNodePt = 0;
    for (int i = 0; i < str.length(); i++)
    {
        int cnt = str[i] - 'a';
        cntNodePt = arr[cntNodePt].next[cnt];
        if (cntNodePt == -1)
            return 0;
    }
    return arr[cntNodePt].num;
}

int main()
{
    ios::sync_with_stdio(false);
    createTrieNode();
    int dictNum;
    cin >> dictNum;
    for (int i = 0; i < dictNum; i++)
    {
        string str;
        cin >> str;
        for (int j = 0; j < str.length(); j++)
        {
            string sub = str.substr(j);
            insertName(sub, i);
        }
    }
    int queryNum;
    cin >> queryNum;
    while (queryNum--)
    {
        string str;
        cin >> str;
        cout << getNum(str) << endl;
    }
    return 0;
}
