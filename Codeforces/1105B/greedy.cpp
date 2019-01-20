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
#include <cassert>
using namespace std;

vector<int> arr[26];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len, k;
    string str;
    cin >> len >> k >> str;

    int cntNum = 1;
    char cntChar = str[0];
    for (int i = 1; i < len; i++)
    {
        if (str[i] == cntChar)
            cntNum++;
        else
        {
            arr[cntChar - 'a'].push_back(cntNum);
            cntChar = str[i];
            cntNum = 1;
        }
    }

    arr[cntChar - 'a'].push_back(cntNum);

    int ans = 0;
    for (int i = 0; i < 26; i++)
    {
        int cntAns = 0;
        for (auto it = arr[i].begin(); it != arr[i].end(); ++it)
        {
            cntAns += *it / k;
        }
        ans = max(ans, cntAns);
    }

    cout << ans << endl;
    return 0;
}