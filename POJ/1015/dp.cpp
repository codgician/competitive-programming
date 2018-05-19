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
#include <stack>
#include <functional>
#include <iterator>
#define JURY_SIZE 21
#define CAND_SIZE 210
#define BAG_SIZE 888
using namespace std;

int fstArr[CAND_SIZE], sndArr[CAND_SIZE];
int dp[JURY_SIZE][BAG_SIZE];
vector<int> path[JURY_SIZE][BAG_SIZE];

inline int getSize(int i)
{
    return fstArr[i] - sndArr[i];
}

inline int getValue(int i)
{
    return fstArr[i] + sndArr[i];
}

int main()
{
    ios::sync_with_stdio(false);
    int candNum, juryNum, casePt = 0;
    while (cin >> candNum >> juryNum)
    {
        if (candNum == 0 && juryNum == 0)
            break;

        const int padding = 20 * juryNum;
        for (int i = 0; i < candNum; i++)
        {
            cin >> fstArr[i] >> sndArr[i];
        }

        for (int i = 0; i <= juryNum; i++)
        {
            for (int j = 0; j <= (padding << 1); j++)
            {
                dp[i][j] = INT_MIN;
                path[i][j].clear();
            }
        }
        dp[0][padding] = 0;

        for (int i = 0; i < candNum; i++)
        {
            for (int j = juryNum - 1; j >= 0; j--)
            {
                for (int k = 0; k <= (padding << 1); k++)
                {
                    if (dp[j][k] == INT_MIN || k + getSize(i) > (padding << 1) || k + getSize(i) < 0)
                        continue;

                    if (dp[j + 1][k + getSize(i)] <= dp[j][k] + getValue(i))
                    {
                        dp[j + 1][k + getSize(i)] = dp[j][k] + getValue(i);
                        path[j + 1][k + getSize(i)] = path[j][k];
                        path[j + 1][k + getSize(i)].push_back(i);
                    }
                }
            }
        }

        int delta = 0;
        while (dp[juryNum][padding + delta] == INT_MIN && dp[juryNum][padding - delta] == INT_MIN)
            delta++;

        cout << "Jury #" << ++casePt << endl;
        delta = (dp[juryNum][padding + delta] > dp[juryNum][padding - delta]) ? delta : -delta;
        int fstAns = (dp[juryNum][padding + delta] + delta) >> 1;
        int sndAns = (dp[juryNum][padding + delta] - delta) >> 1;
        cout << "Best jury has value " << fstAns << " for prosecution and value " << sndAns << " for defence:" << endl;

        for (int i = 0; i < juryNum; i++)
        {
            cout << " " << path[juryNum][padding + delta][i] + 1;
        }
        cout << endl << endl;
    }
    return 0;
}
