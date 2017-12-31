#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 10001
using namespace std;

long long int arr[SIZE];

long long int getSum(int leftPt, int rightPt)
{
    long long int ans = arr[leftPt];
    for (int i = leftPt + 1; i <= rightPt; i++)
        ans += arr[i];
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int boxNum;
    cin >> boxNum;
    for (int i = 0; i < boxNum; i++)
    {
        cin >> arr[i];
    }
    int methodNum;
    cin >> methodNum;
    long long int ans = 0;
    while (methodNum--)
    {
        int leftPt, rightPt;
        cin >> leftPt >> rightPt;
        leftPt--;
        rightPt--;
        long long int tmp = getSum(leftPt, rightPt);
        if (tmp > 0)
            ans += tmp;
    }
    cout << ans << endl;
    return 0;
}
