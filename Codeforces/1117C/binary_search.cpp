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
#include <bitset>
#include <cassert>
using namespace std;

#define SIZE 100010

pair<long long int, long long int> startPt, endPt, dArr[SIZE];
int len;
string str;

pair<long long int, long long int> operator + (const pair<long long int, long long int> & fst, const pair<long long int, long long int> & snd)
{
    return make_pair(fst.first + snd.first, fst.second + snd.second);
}

pair<long long int, long long int> operator * (const pair<long long int, long long int> & fst, const long long int snd)
{
    return make_pair(fst.first * snd, fst.second * snd);
}

bool check(long long int cnt)
{
    pair<long long int, long long int> cntPt = startPt + dArr[len] * (cnt / len) + dArr[cnt % len];
    long long int cntAns = llabs(endPt.first - cntPt.first) + llabs(endPt.second - cntPt.second);
    if (cntAns <= cnt)
        return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> startPt.first >> startPt.second >> endPt.first >> endPt.second;
    cin >> len >> str;
    dArr[0] = make_pair(0, 0);
    for (int i = 1; i <= len; i++)
    {
        dArr[i] = dArr[i - 1];
        if (str[i - 1] == 'U')
            dArr[i].second++;
        else if (str[i - 1] == 'D')
            dArr[i].second--;
        else if (str[i - 1] == 'L')
            dArr[i].first--;
        else if (str[i - 1] == 'R')
            dArr[i].first++;
    }

    long long int leftPt = 0, rightPt = 1e18, ans = -1;
    while (leftPt <= rightPt)
    {
        long long int midPt = (leftPt + rightPt) >> 1;
        if (check(midPt))
        {
            ans = midPt;
            rightPt = midPt - 1;
        }
        else
        {
            leftPt = midPt + 1;
        }
    }

    cout << ans << endl;
    return 0;
}