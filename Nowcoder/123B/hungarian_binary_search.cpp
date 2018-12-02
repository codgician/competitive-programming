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

#define SIZE 550

int arr[SIZE][SIZE];
bool sndVisited[SIZE];
int sndMatch[SIZE];
int fstNum, sndNum;

int len, lim;
int maxAns;

bool canFind(int fstId)
{
    for (int i = 0; i < sndNum; i++)
    {
        if (arr[fstId][i] >= lim && !sndVisited[i])
        {
            sndVisited[i] = true;
            
            if (sndMatch[i] == -1 || canFind(sndMatch[i]))
            {
                sndMatch[i] = fstId;
                return true;
            }
        }
    }
    return false;
}

int hungarian()
{
    memset(sndMatch, -1, sizeof(sndMatch));
    int ans = 0;
    for (int i = 0; i < fstNum; i++)
    {
        memset(sndVisited, false, sizeof(sndVisited));
        if (canFind(i))
            ans++;
    }
    return ans;
}

bool check()
{
    int ans = hungarian();
    return ans == maxAns;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> len)
    {
        int leftPt = INT_MAX, rightPt = 0;
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
            {
                cin >> arr[i][j];
                if (arr[i][j] > 0)
                {
                    leftPt = min(leftPt, arr[i][j]);
                    rightPt = max(rightPt, arr[i][j]);
                }
            }
        }

        fstNum = len;
        sndNum = len;
        lim = 1;
        maxAns = hungarian();

        int ans = 1;
        while (leftPt <= rightPt)
        {
            int midPt = (leftPt + rightPt) >> 1;
            lim = midPt;

            if (check())
            {
                leftPt = midPt + 1;
                ans = midPt;
            }
            else
            {
                rightPt = midPt - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}