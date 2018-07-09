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
using namespace std;

#define SIZE 200100

int arr[SIZE];
long long int suffixSum[SIZE];

bool check(int i)
{
    return suffixSum[i] >= i;
}

int main()
{
    ios::sync_with_stdio(false);
    int num;
    while (cin >> num)
    {
        for (int i = 0; i <= num; i++)
        {
            cin >> arr[i];
        }

        suffixSum[num + 1] = 0;
        for (int i = num; i >= 0; i--)
        {
            suffixSum[i] = suffixSum[i + 1] + arr[i];
        }

        int leftPt = 0, rightPt = num;
        int ans = 0;
        while (leftPt <= rightPt)
        {
            int midPt = (leftPt + rightPt) >> 1;
            if (check(midPt))
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