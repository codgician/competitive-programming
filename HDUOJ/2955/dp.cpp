#include <iostream>
#include <cstdio>
#include <cstring>
#define SIZE 101
using namespace std;

typedef struct Node {
    int money;
    double prob;
} bank;

bank arr[SIZE];

double dp[SIZE * SIZE];  // Stores possibility.

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        double probLimit;
        int bankNum, sum = 0;
        cin >> probLimit >> bankNum;
        for (int i = 0; i < bankNum; i++)
        {
            cin >> arr[i].money >> arr[i].prob;
            sum += arr[i].money;

        }
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (int i = 0; i < bankNum; i++)
        {
            for (int j = sum; j >= arr[i].money; j--)
            {
                dp[j] = max(dp[j], dp[j - arr[i].money] * (1 - arr[i].prob));
            }
        }

        for (int i = sum; i >= 0; i--)
        {
            if (dp[i] > 1 - probLimit)
            {
                cout << i << endl;
                break;
            }
        }
    }
    return 0;
}
