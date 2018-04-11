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
#include <map>
#include <set>
#define SIZE 200100
using namespace std;

bool arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int seatNum, progNum, athNum;
    cin >> seatNum >> progNum >> athNum;
    for (int i = 0; i < seatNum; i++)
    {
        char ch;
        cin >> ch;
        if (ch == '*')
            arr[i] = true;
        else
            arr[i] = false;
    }
    arr[seatNum] = true;

    int maxNum = max(progNum, athNum);
    int minNum = min(progNum, athNum);

    int ans = 0, cntLen = 0;
    for (int i = 0; i <= seatNum; i++)
    {
        if (arr[i] && cntLen > 0)
        {
            if (cntLen > 1 && (cntLen & 1))
            {
                maxNum -= (cntLen + 1) >> 1;
                minNum -= cntLen >> 1;
                ans += cntLen;
            }
            else if (cntLen == 1)
            {
                if (maxNum > 0)
                {
                    maxNum--;
                    ans++;
                }
                else if (minNum > 0)
                {
                    minNum--;
                    ans++;
                }
                else
                    break;
            }
            else if (!(cntLen & 1))
            {
                maxNum -= cntLen >> 1;
                minNum -= cntLen >> 1;
                ans += cntLen;
            }

            if (maxNum < 0 || minNum < 0)
            {
                if (maxNum < 0)
                {
                    ans += maxNum;
                    maxNum = 0;
                }
                if (minNum < 0)
                {
                    ans += minNum;
                    minNum = 0;
                }
            }
            if (maxNum < minNum)
                swap(maxNum, minNum);
            cntLen = 0;
        }
        else if (!arr[i])
        {
            cntLen++;
        }
    }
    cout << ans << endl;
    return 0;
}
