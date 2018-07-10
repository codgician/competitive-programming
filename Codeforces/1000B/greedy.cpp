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

#define SIZE 100010

int arr[SIZE];
int prefixSum[SIZE][2];

int main()
{
    ios::sync_with_stdio(false);
    int len, endPt;
    cin >> len >> endPt;

    arr[1] = 0;
    for (int i = 2; i <= len + 1; i++)
    {
        cin >> arr[i];
    }
    arr[len + 2] = endPt;

    int sumArr[2] = {0, 0};
    for (int i = 1; i <= len + 1; i++)
    {
        arr[i] = arr[i + 1] - arr[i];
        sumArr[i & 1] += arr[i];
    }

    memset(prefixSum, 0, sizeof(prefixSum));
    prefixSum[1][1] = arr[1];
    for (int i = 2; i <= len + 1; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            prefixSum[i][j] = prefixSum[i - 1][j];
        }

        prefixSum[i][i & 1] += arr[i];
    }
    

    int ans = prefixSum[len + 1][1];
    for (int i = 1; i <= len + 1; i++)
    {
        ans = max(ans, prefixSum[i - 1][1] + arr[i] - 1 + prefixSum[len + 1][0] - prefixSum[i][0]);
    }
    cout << ans << endl;

    return 0;
}