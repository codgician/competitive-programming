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

int sumArr[SIZE];
int preNext[SIZE], sufNext[SIZE];
int valArr[26];
bool preIsPalindrome[SIZE], sufIsPalindrome[SIZE];  

void initNext(int *nextArr, string &str)
{
    int strLen = str.length();
    nextArr[0] = 0;
    for (int i = 1, matchNum = 0; i < strLen; i++)
    {
        while (matchNum > 0 && str[i] != str[matchNum])
            matchNum = nextArr[matchNum - 1];
        if (str[i] == str[matchNum])
            matchNum++;
        nextArr[i] = matchNum;
    }
}

int kmp(int *nextArr, string &a, string &b)
{
    int aLen = a.length(), bLen = b.length();
    int matchNum = 0;
    for (int i = 0; i < aLen; i++)
    {
        while (matchNum > 0 && (matchNum == bLen || a[i] != b[matchNum]))
            matchNum = nextArr[matchNum - 1];
        if (a[i] == b[matchNum])
            matchNum++;
    }
    return matchNum;
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
        int strLen = str.length();

        sumArr[0] = 0;
        for (int i = 1; i <= (int)str.length(); i++)
        {
            sumArr[i] = sumArr[i - 1] + valArr[str[i - 1] - 'a'];
        }

        initNext(preNext, str);
        initNext(sufNext, revStr);

        int pt;
        pt = kmp(preNext, revStr, str);
        memset(preIsPalindrome, false, sizeof(preIsPalindrome));
        while (pt > 0)
        {
            preIsPalindrome[pt] = true;
            pt = preNext[pt - 1];
        }

        pt = kmp(sufNext, str, revStr);
        memset(sufIsPalindrome, false, sizeof(sufIsPalindrome));
        while (pt > 0)
        {
            sufIsPalindrome[pt] = true;
            pt = sufNext[pt - 1];
        }

        int ans = -1;
        for (int i = 1; i < strLen - 1; i++)
        {
            int cntAns = 0;
            if (preIsPalindrome[i])
                cntAns += sumArr[i];
            if (sufIsPalindrome[strLen - i])
                cntAns += sumArr[strLen] - sumArr[i];
            ans = max(ans, cntAns);
        }
        cout << ans << endl;
    }
    return 0;
}