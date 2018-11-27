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

#define SIZE 600020
#define CHAR_SIZE 2

typedef struct _TrieNode
{
    int nextArr[CHAR_SIZE], siz;
} TrieNode;

TrieNode trie[SIZE << 5];
int root[SIZE], triePt;

int getBitAt(int num, int pos)
{
    return (num >> pos) & 1;
}

void insert(int & nowPt, int prevPt, int val)
{
    nowPt = ++triePt;
    int cntPt = nowPt;
    for (int i = 24; i >= 0; i--)
    {
        int cnt = getBitAt(val, i);
        if (trie[cntPt].nextArr[cnt] == 0)
        {
            trie[cntPt].nextArr[cnt] = ++triePt;
            trie[cntPt].nextArr[cnt ^ 1] = trie[prevPt].nextArr[cnt ^ 1];
            if (trie[cntPt].nextArr[cnt] == 0)
                trie[trie[cntPt].nextArr[cnt]].siz = 1;
            else
                trie[trie[cntPt].nextArr[cnt]].siz = trie[trie[prevPt].nextArr[cnt]].siz + 1;
        }
        cntPt = trie[cntPt].nextArr[cnt];
        prevPt = trie[prevPt].nextArr[cnt];
    }
}

int query(int fstPt, int sndPt, int val)
{
    int ans = 0;
    for (int i = 24; i >= 0; i--)
    {
        ans <<= 1;
        int cnt = getBitAt(val, i);
        if (trie[trie[sndPt].nextArr[cnt ^ 1]].siz > trie[trie[fstPt].nextArr[cnt ^ 1]].siz)
        {
            ans |= 1;
            cnt ^= 1;
        }

        fstPt = trie[fstPt].nextArr[cnt];
        sndPt = trie[sndPt].nextArr[cnt];
    }

    return ans;
}

int main()
{
    triePt = 0;
    int len, qNum;
    scanf("%d%d", &len, &qNum);

    insert(root[1], root[0], 0);
    int xorSum = 0;
    for (int i = 1; i <= len; i++)
    {
        int cnt;
        scanf("%d", &cnt);
        xorSum ^= cnt;
        insert(root[i + 1], root[i], xorSum);
    }

    while (qNum--)
    {
        char opr[2];
        scanf("%s", opr);
        if (opr[0] == 'A')
        {
            int val;
            scanf("%d", &val);
            xorSum ^= val;
            len++;
            insert(root[len + 1], root[len], xorSum);
        }
        else if (opr[0] == 'Q')
        {
            int qLeftPt, qRightPt, val;
            scanf("%d%d%d", &qLeftPt, &qRightPt, &val);
            printf("%d\n", query(root[qLeftPt - 1], root[qRightPt], xorSum ^ val));
        }
    }

    return 0;
}