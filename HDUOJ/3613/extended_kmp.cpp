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
#include <stack>
#include <iterator>
#include <functional>
#define SIZE 500010
using namespace std;

int valArr[26];
int nextArr[SIZE];
int extArr1[SIZE], extArr2[SIZE];
int sumArr[SIZE];

void initNext(string &str)
{
    nextArr[0] = (int)str.length();

    int pt = 0;
    while (str[pt] == str[pt + 1] && pt < (int)str.length() - 1)
        pt++;
    nextArr[1] = pt;

    int farthestPt = 1;
    for (int i = 2; i < (int)str.length(); i++)
    {
        if (nextArr[i - farthestPt] + i < nextArr[farthestPt] + farthestPt)
        {
            nextArr[i] = nextArr[i - farthestPt];
        }
        else
        {
            pt = nextArr[farthestPt] + farthestPt - i;
            if (pt < 0)
                pt = 0;
            while (i + pt < (int)str.length() && str[pt] == str[i + pt])
                pt++;
            nextArr[i] = pt;
            farthestPt = i;
        }
    }
}

void exKmp(int *extArr, string &a, string &b)
{
    initNext(b);

    int pt = 0;
    while (a[pt] == b[pt] && pt < (int)a.length() && pt < (int)b.length())
        pt++;
    extArr[0] = pt;

    int farthestPt = 0;
    for (int i = 1; i < (int)a.length(); i++)
    {
        if (nextArr[i - farthestPt] + i < extArr[farthestPt] + farthestPt)
        {
            extArr[i] = nextArr[i - farthestPt];
        }
        else
        {
            pt = extArr[farthestPt] + farthestPt - i;
            if (pt < 0)
                pt = 0;
            while (i + pt < (int)a.length() && pt < (int)b.length() && a[i + pt] == b[pt])
                pt++;
            extArr[i] = pt;
            farthestPt = i;
        }
    }
}


int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        for (int i = 0; i < 26; i++)
        {
            cin >> valArr[i];
        }

        string str, revStr;
        cin >> str;
        revStr = str;
        reverse(revStr.begin(), revStr.end());

        sumArr[0] = 0;
        for (int i = 1; i <= (int)str.length(); i++)
        {
            sumArr[i] = sumArr[i - 1] + valArr[str[i - 1] - 'a'];
        }

        exKmp(extArr1, revStr, str);
        exKmp(extArr2, str, revStr);

        int ans = -1;
        for (int i = 0; i < (int)str.length(); i++)
        {
            if (i > 0 && extArr1[i] + i == (int)str.length())
            {
                int pos = extArr1[i];
                int cntVal = sumArr[pos];
                if (extArr2[pos] + pos == (int)str.length())
                {
                    cntVal += sumArr[(int)str.length()] - sumArr[pos];
                }
                ans = max(ans, cntVal);
            }
            else
            {
                int pos = i + 1;
                int cntVal = 0;
                if (extArr2[pos] + pos == (int)str.length())
                {
                    cntVal += sumArr[(int)str.length()] - sumArr[pos];
                }
                ans = max(ans, cntVal);
            }
        }

        cout << ans << endl;
    }
    return 0;
}