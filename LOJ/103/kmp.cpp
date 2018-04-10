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
#define SIZE 1000100
using namespace std;

int nextArr[SIZE];

void initNext(string &str)
{
    nextArr[0] = 0;
    for (int i = 1, matchNum = 0; i < (int)str.length(); i++)
    {
        while (matchNum > 0 && str[i] != str[matchNum]) // (matchNum + 1) - 1
            matchNum = nextArr[matchNum - 1];
        if (str[i] == str[matchNum])
            matchNum++;
        nextArr[i] = matchNum;
    }
}

int kmp(string &a, string &b)
{
    int ans = 0;
    for (int i = 0, matchNum = 0; i < (int)a.length(); i++)
    {
        while (matchNum > 0 && (matchNum== (int)b.length() || a[i] != b[matchNum]))
            matchNum = nextArr[matchNum - 1];
        if (a[i] == b[matchNum])
            matchNum++;
        if (matchNum == (int)b.length())
            ans++;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    string a, b;
    cin >> a >> b;
    initNext(b);
    int ans = kmp(a, b);
    cout << ans << endl;
    return 0;
}
