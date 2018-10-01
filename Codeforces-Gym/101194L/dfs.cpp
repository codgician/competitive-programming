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

int arr[4], cnt[4];
pair<int, int> rnd[6];

int ans;

void dfs(int rndId)
{
    if (rndId == 6)
    {
        bool isIdentical = true;
        for (int i = 0; i < 4; i++)
        {
            if (cnt[i] != arr[i])
            {
                isIdentical = false;
                break;
            }
        }

        if (isIdentical)
        {
            if (ans == -1)
                ans = 0;
            else
                ans = 1;
        }
        return;
    }

    if (ans == 1)
        return;

    int fst = rnd[rndId].first;
    int snd = rnd[rndId].second;

    // fst win
    cnt[fst] += 3;
    dfs(rndId + 1);
    cnt[fst] -= 3;

    // draw
    cnt[fst]++;
    cnt[snd]++;
    dfs(rndId + 1);
    cnt[fst]--;
    cnt[snd]--;

    // snd win
    cnt[snd] += 3;
    dfs(rndId + 1);
    cnt[snd] -= 3;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {

        int maxVal = -1, sum = 0;
        for (int i = 0; i < 4; i++)
        {
            cnt[i] = 0;
            cin >> arr[i];
            sum += arr[i];
            maxVal = max(maxVal, arr[i]);
        }

        cout << "Case #" << t << ": ";
        if (maxVal > 9 || sum < 12)
        {
            cout << "Wrong Scoreboard" << endl;
            continue;
        }

        int rPt = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = i + 1; j < 4; j++)
            {
                rnd[rPt++] = make_pair(i, j);
            }
        }

        ans = -1;
        dfs(0);

        if (ans == -1)
            cout << "Wrong Scoreboard" << endl;
        else if (ans == 0)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}