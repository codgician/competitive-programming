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

#define SIZE 200010

long long int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int len;
    cin >> len;
    for (int i = 1; i <= len; i++)
    {
        cin >> arr[i];
    }

    int headPt = 0, tailPt = len + 1;
    long long int headSum = 0, tailSum = 0;
    long long int cntMaxSum = 0;
    while (headPt <= tailPt)
    {
        if (headSum == tailSum)
        {
            cntMaxSum = max(cntMaxSum, headSum);
            if (headPt + 1 == tailPt - 1)
                break;
            headSum += arr[++headPt];
            tailSum += arr[--tailPt];
        }
        else if (headSum < tailSum)
        {
            headSum += arr[++headPt];
        }
        else
        {
            tailSum += arr[--tailPt];
        }
    }

    cout << cntMaxSum << endl;
    return 0;
}