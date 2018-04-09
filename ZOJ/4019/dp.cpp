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
#define SIZE 2010
using namespace std;

long long int fstArr[SIZE], sndArr[SIZE];
long long int fstPre[SIZE], sndPre[SIZE];
long long int dp[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int k1, k2, fstNum, sndNum;
        long long int capacity;
        cin >> k1 >> k2 >> capacity >> fstNum >> sndNum;

        for (int i = 1; i <= fstNum; i++)
            cin >> fstArr[i];

        for (int i = 1; i <= sndNum; i++)
            cin >> sndArr[i];

        sort(fstArr + 1, fstArr + fstNum + 1);
        sort(sndArr + 1, sndArr + sndNum + 1);

        fstPre[0] = 0;
        for (int i = 1; i <= fstNum; i++)
            fstPre[i] = fstPre[i - 1] + fstArr[i];
        sndPre[0] = 0;
        for (int i = 1; i <= sndNum; i++)
            sndPre[i] = sndPre[i - 1] + sndArr[i];

        long long int ans = -1;
        dp[0][0] = 0;
        for (int i = 1; i <= fstNum && fstPre[i] <= capacity; i++)
        {
            dp[i][0] = dp[i - 1][0] + k1 * (capacity - fstPre[i]);
            ans = max(ans, dp[i][0]);
        }
        for (int i = 1; i <= sndNum && sndPre[i] <= capacity; i++)
        {
            dp[0][i] = dp[0][i - 1] + k2 * (capacity - sndPre[i]);
            ans = max(ans, dp[0][i]);
        }

        for (int i = 1; i <= fstNum && fstPre[i] <= capacity; i++)
        {
            for (int j = 1; j <= sndNum; j++)
            {
                long long int nextCapacity  = capacity - fstPre[i] - sndPre[j];
                if (nextCapacity <= 0)
                    break;

                dp[i][j] = max(dp[i - 1][j] + k1 * nextCapacity, dp[i][j - 1] + k2 * nextCapacity);
                ans = max(ans, dp[i][j]);
            }
        }

        cout << ans << endl;
    }
    return 0;
}
