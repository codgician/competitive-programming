#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define SIZE 100001
using namespace std;

long long int arr[SIZE], leftNode[SIZE], rightNode[SIZE];

long long int getMax(long long int a, long long int b)
{
    return a > b ? a : b;
}

int main()
{
    ios::sync_with_stdio(false);
    long long int recNum;
    while (cin >> recNum)
    {
        if (recNum == 0)
            break;
        for (long long int i = 0; i < recNum; i++)
        {
            cin >> arr[i];
            leftNode[i] = rightNode[i] = i;
        }

        // Find leftNode.
        for (long long int i = 1; i < recNum; i++)
        {
            while (arr[leftNode[i] - 1] >= arr[i] && leftNode[i] > 0)
            {
                leftNode[i] = leftNode[leftNode[i] - 1];
            }
        }

        // Find rightNode.
        for (long long int i = recNum - 2; i >= 0; i--)
        {
            while (arr[rightNode[i] + 1] >= arr[i] && rightNode[i] < recNum - 1)
            {
                rightNode[i] = rightNode[rightNode[i] + 1];
            }
        }

        long long int ans = 0;
        for (long long int i = 0; i < recNum; i++)  // Lowest rec.
        {
            ans = getMax(ans, (rightNode[i] - leftNode[i] + 1) * arr[i]);
        }

        cout << ans << endl;
    }
    return 0;
}
