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

#define SIZE 960100
#define CHAR_SIZE 2

typedef struct _TrieNode
{
    bool isWord;
    int nextArr[CHAR_SIZE];
} TrieNode;

TrieNode arr[SIZE];
int arrPt;

vector<pair<unsigned int, int> > vec;

int ip[4];

int newTrieNode()
{
    arr[arrPt].isWord = false;
    for (int i = 0; i < CHAR_SIZE; i++)
        arr[arrPt].nextArr[i] = -1;
    return arrPt++;
}

int getBitAt(unsigned int num, int pos)
{
    return (num >> pos) & 1;
}

void insertName(unsigned int val, int len)
{
    val >>= (32 - len);

    int cntPt = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        int cnt = getBitAt(val, i);
        if (arr[cntPt].nextArr[cnt] == -1)
            arr[cntPt].nextArr[cnt] = newTrieNode();
        cntPt = arr[cntPt].nextArr[cnt];
    }

    arr[cntPt].isWord = true;
}

void printSubnet(unsigned int val, int len)
{
    memset(ip, 0, sizeof(ip));

    int fac = 1;
    for (int i = 0; i < 32; i++)
    {
        int cnt = (val & 1) * fac;
        val >>= 1;

        if (i % 8 == 7)
            fac = 1;
        else
            fac <<= 1;

        int id = 3 - (i / 8);
        ip[id] += cnt;
    }

    for (int i = 0; i < 4; i++)
    {
        printf("%d", ip[i]);
        if (i < 3)
            printf(".");
    }

    printf("/");
    printf("%d\n", len);
}

void dfs(int cntPt, unsigned int cntVal, int cntLen)
{
    if (arr[cntPt].isWord)
        return;

    for (int i = 0; i < CHAR_SIZE; i++)
    {
        unsigned int nextVal = (cntLen == 0) ? i : (cntVal << 1) + i;
        if (arr[cntPt].nextArr[i] != -1)
        {
            dfs(arr[cntPt].nextArr[i], nextVal, cntLen + 1);
        }
        else
        {
            vec.push_back(make_pair(nextVal << (31 - cntLen), cntLen + 1));
        }
    }
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    for (int t = 1; t <= caseNum; t++)
    {
        vec.clear();
        arrPt = 0;
        newTrieNode();

        int num;
        scanf("%d", &num);
        for (int i = 0; i < num; i++)
        {
            int pfxLen;
            scanf("%d.%d.%d.%d/%d", ip + 0, ip + 1, ip + 2, ip + 3, &pfxLen);
            unsigned int val = 0;
            for (int j = 0; j < 4; j++)
            {
                val = (val << 8) + ip[j];
            }

            insertName(val, pfxLen);
        }

        printf("Case #%d:\n", t);
        if (num == 0)
        {
            puts("1");
            puts("0.0.0.0/0");
            continue;
        }

        dfs(0, 0, 0);

        printf("%d\n", (int)vec.size());
        for (auto i : vec)
        {
            printSubnet(i.first, i.second);
        }
    }

    return 0;
}