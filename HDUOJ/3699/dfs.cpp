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

#define ALPHABET_SIZE 5
#define DIGIT_SIZE 10

bool num[ALPHABET_SIZE], hasUsed[DIGIT_SIZE], noZero[DIGIT_SIZE];
int cntMap[ALPHABET_SIZE];
long long int val[3], ans;
string str[3];

void dfs(int cntPt)
{
    if (cntPt == 5)
    {
        for (int i = 0; i < 3; i++)
        {
            val[i] = 0;
            for (int j = 0; j < (int)str[i].size(); j++)
            {
                val[i] = val[i] * 10 + cntMap[str[i][j] - 'A'];
            }
        }

        if (val[0] + val[1] == val[2])
            ans++;
        if (val[0] - val[1] == val[2])
            ans++;
        if (val[0] * val[1] == val[2])
            ans++;
        if (val[1] != 0 && val[0] == val[1] * val[2])
            ans++;

        return;
    }

    if (!num[cntPt])
    {
        dfs(cntPt + 1);
    }
    else
    {
        int startDigit = noZero[cntPt] ? 1 : 0;
        for (int i = startDigit; i < 10; i++)
        {
            if (hasUsed[i])
                continue;

            hasUsed[i] = true;
            cntMap[cntPt] = i;

            dfs(cntPt + 1);
            
            hasUsed[i] = false;
            cntMap[cntPt] = -1;
        }
    }
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
        memset(num, false, sizeof(num));
        memset(hasUsed, false, sizeof(hasUsed));
        memset(noZero, false, sizeof(noZero));
        memset(cntMap, -1, sizeof(cntMap));
        for (int i = 0; i < 3; i++)
        {
            cin >> str[i];
            for (int j = 0; j < (int)str[i].size(); j++)
            {
                num[str[i][j] - 'A'] = true;
            }

            if (str[i].size() > 1)
            {
                noZero[str[i][0] - 'A'] = true;
            }
        }

        ans = 0;
        dfs(0);

        cout << ans << endl;
    }
    return 0;
}