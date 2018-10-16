#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define SIZE 64010
#define CHAR_SIZE 2

typedef struct _TrieNode
{
    bool isWord;
    int nextArr[CHAR_SIZE], edgeNum;
} TrieNode;

TrieNode trieArr[SIZE];
int triePt;

unsigned int arr[SIZE];

int newTrieNode()
{
    trieArr[triePt].isWord = false;
    trieArr[triePt].edgeNum = 0;
    for (int i = 0; i < CHAR_SIZE; i++)
        trieArr[triePt].nextArr[i] = -1;
    return triePt++;
}

bool getBitAt(unsigned int num, int pos)
{
    return (num >> pos) & 1;
}

void insertNumber(unsigned int val)
{
    int cntPt = 0;
    for (int i = 31; i >= 0; i--)
    {
        trieArr[cntPt].edgeNum++;
        int cnt = getBitAt(val, i);
        if (trieArr[cntPt].nextArr[cnt] == -1)
            trieArr[cntPt].nextArr[cnt] = newTrieNode();
        cntPt = trieArr[cntPt].nextArr[cnt];
    }
    trieArr[cntPt].edgeNum++;
    trieArr[cntPt].isWord = true;
}

void deleteNumber(unsigned int val)
{
    int cntPt = 0;
    for (int i = 31; i >= 0; i--)
    {
        trieArr[cntPt].edgeNum--;
        int cnt = getBitAt(val, i);
        cntPt = trieArr[cntPt].nextArr[cnt];
    }
    trieArr[cntPt].edgeNum--;
}

unsigned int query(unsigned int val)
{
    int cntPt = 0;
    unsigned int ret = 0;
    for (int i = 31; i >= 0; i--)
    {
        int cnt = getBitAt(val, i);
        if (trieArr[cntPt].nextArr[cnt ^ 1] != -1 && trieArr[trieArr[cntPt].nextArr[cnt ^ 1]].edgeNum > 0)
            cnt ^= 1;
        cntPt = trieArr[cntPt].nextArr[cnt];
        ret = (ret << 1) + cnt; 
    }

    return ret ^ val;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        triePt = 0;
        newTrieNode();

        int num;
        cin >> num;
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i];
            insertNumber(arr[i]);
        }

        unsigned int ans = 0;
        for (int i = 0; i < num; i++)
        {
            deleteNumber(arr[i]);
            for (int j = i + 1; j < num; j++)
            {
                deleteNumber(arr[j]);
                ans = max(ans, query(arr[i] + arr[j]));
                insertNumber(arr[j]);
            }
            insertNumber(arr[i]);
        }
        cout << ans << endl;
    }

    return 0;
}