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
    int weight;
    int next[26];
} TrieNode;
TrieNode arr[SIZE];
int nextFreePt = 0, maxWeight = 0;

char cntStr[101], ans[101];

int t9Arr[8][4];

void initT9()
{
    int tmp = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (j == 3 && i != 5 && i != 7)
            {
                t9Arr[i][j] = -1;
            }
            else
            {
                t9Arr[i][j] = tmp;
                tmp++;
            }
        }
    }
}

int createTrieNode()
{
    arr[nextFreePt].weight = 0;
    for (int i = 0; i < 26; i++)
    {
        arr[nextFreePt].next[i] = -1;
    }
    return nextFreePt++;
}

int insertWord(string& str, int weight)
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
        arr[cntNodePt].weight += weight;
    }
}

void dfs(int cntNodePt, int cntLen, int len, string& query)
{
    if (cntLen == len)
    {
        if (arr[cntNodePt].weight > maxWeight)
        {
            maxWeight = arr[cntNodePt].weight;
            for (int i = 0; i < len; i++)
            {
                ans[i] = cntStr[i];
            }
            ans[len] = '\0';
        }
        return;
    }
    int cnt = query[cntLen] - '2';
    for (int i = 0; i < 4; i++)
    {
        int ch = t9Arr[cnt][i];
        if (ch == -1)
            continue;
        if (arr[cntNodePt].next[ch] != -1)
        {
            cntStr[cntLen] = ch + 'a';
            dfs(arr[cntNodePt].next[ch], cntLen + 1, len, query);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    initT9();
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        nextFreePt = 0;
        createTrieNode();
        int dictNum;
        cin >> dictNum;
        while (dictNum--)
        {
            string str;
            int weight;
            cin >> str >> weight;
            insertWord(str, weight);
        }
        int queryNum;
        cin >> queryNum;
        cout << "Scenario #" << t << ":" << endl;
        while (queryNum--)
        {
            string query;
            cin >> query;
            for (int i = 1; i < query.length(); i++)
            {
                maxWeight = 0;
                dfs(0, 0, i, query);
                if (maxWeight == 0)
                {
                    cout << "MANUALLY" << endl;
                }
                else
                {
                    cout << ans << endl;
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
