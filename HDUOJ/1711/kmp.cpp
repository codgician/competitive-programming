#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 1000010
using namespace std;

int a[SIZE], b[SIZE];
int nextArr[SIZE];

void initNext(int len)
{
    nextArr[0] = 0;
    for (int i = 1, matchNum = 0; i < len; i++)
    {
        while (matchNum > 0 && b[i] != b[matchNum])
            matchNum = nextArr[matchNum - 1];
        if (b[i] == b[matchNum])
            matchNum++;
        nextArr[i] = matchNum;
    }
}

int kmp(int aLen, int bLen)
{
    for (int i = 0, matchNum = 0; i < aLen; i++)
    {
        while (matchNum > 0 && (matchNum == bLen || a[i] != b[matchNum]))
            matchNum = nextArr[matchNum - 1];
        if (a[i] == b[matchNum])
            matchNum++;
        if (matchNum == bLen)
            return i - bLen + 2;
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int aLen, bLen;
        cin >> aLen >> bLen;
        for (int i = 0; i < aLen; i++)
            cin >> a[i];
        for (int i = 0; i < bLen; i++)
            cin >> b[i];

        if (bLen > aLen)
        {
            cout << -1 << endl;
            continue;
        }

        initNext(bLen);
        int ans = kmp(aLen, bLen);
        cout << ans << endl;
    }
    return 0;
}
