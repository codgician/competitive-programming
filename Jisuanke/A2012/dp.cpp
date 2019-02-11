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

#define ROOM_SIZE 1010
#define OPR_SIZE 10

long long int dp[ROOM_SIZE][OPR_SIZE][2];
long long int arr[ROOM_SIZE];
char curseArr[OPR_SIZE];

long long int calc(char opr, long long int fst, long long int snd)
{
    if (opr == '+')
        return fst + snd;
    if (opr == '-')
        return fst - snd;
    if (opr == '*')
        return fst * snd;
    if (opr == '/')
        return fst / snd;
    return LLONG_MIN;
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
        int roomNum, curseNum, initScr;
        cin >> roomNum >> curseNum >> initScr;
        for (int i = 1; i <= roomNum; i++)
        {
            cin >> arr[i];
        }
        for (int i = 1; i <= curseNum; i++)
        {
            cin >> curseArr[i];
        }
        
        for (int i = 0; i <= roomNum; i++)
        {
            for (int j = 0; j <= curseNum; j++)
            {
                dp[i][j][0] = LLONG_MIN;
                dp[i][j][1] = LLONG_MAX;
            }
        }
        dp[0][0][0] = initScr;
        dp[0][0][1] = initScr;

        for (int i = 1; i <= roomNum; i++)
        {
            dp[i][0][0] = initScr;
            dp[i][0][1] = initScr;
            for (int j = 1; j <= curseNum; j++)
            {
                // Use
                if (dp[i - 1][j - 1][0] != LLONG_MIN)
                {
                    dp[i][j][0] = max(dp[i][j][0], calc(curseArr[j], dp[i - 1][j - 1][0], arr[i]));
                    dp[i][j][0] = max(dp[i][j][0], calc(curseArr[j], dp[i - 1][j - 1][1], arr[i]));
                }
                if (dp[i - 1][j - 1][1] != LLONG_MAX)
                {
                    dp[i][j][1] = min(dp[i][j][1], calc(curseArr[j], dp[i - 1][j - 1][1], arr[i]));
                    dp[i][j][1] = min(dp[i][j][1], calc(curseArr[j], dp[i - 1][j - 1][0], arr[i]));
                }

                // Or not
                if (dp[i - 1][j][0] != LLONG_MIN)
                    dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][0]);
                if (dp[i - 1][j][1] != LLONG_MAX)
                    dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j][1]);
            }
        }
        cout << dp[roomNum][curseNum][0] << endl;
    }

    return 0;
}