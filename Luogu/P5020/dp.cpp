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

#define VAL_SIZE 25010
#define NUM_SIZE 110

int arr[NUM_SIZE];
bool dp[VAL_SIZE][2];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(dp, false, sizeof(dp));
        int num;
        cin >> num;
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i];
            dp[arr[i]][0] = true;
        }

        sort(arr + 0, arr + num);

        for (int i = 0; i < num; i++)
        {
            for (int j = arr[i]; j < VAL_SIZE; j++)
            {
                dp[j][1] |= (dp[j - arr[i]][0] | dp[j - arr[i]][1]);
            }
        }

        int ans = 0;
        for (int i = 0; i < num; i++)
        {
            if (dp[arr[i]][0] != dp[arr[i]][1])
                ans++;
        }
        cout << ans << endl;
    }

    return 0;
}