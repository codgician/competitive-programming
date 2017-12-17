#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 200010
using namespace std;

long long int arr[SIZE];
long long int minChange[SIZE];
int minChangePt = 0;

bool cmpRule(int a, int b)
{
    return a < b;
}

bool isSquareNum(long long int n)
{
    long long int squareRoot = sqrt(n);
    if (squareRoot * squareRoot == n)
        return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    long long int n;
    cin >> n;
    long long int squareNum = 0, zeroNum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        if (isSquareNum(arr[i]))
        {
            squareNum++;
            if (arr[i] == 0)
                zeroNum++;
        }
        else
        {
            long long int squareRoot = sqrt(arr[i]);
            long long int lowerSquare = squareRoot * squareRoot;
            long long int upperSquare = (squareRoot + 1) * (squareRoot + 1);
            minChange[minChangePt] = min(arr[i] - lowerSquare, upperSquare - arr[i]);
            minChangePt++;
        }
    }

    long long int ans = 0;
    if (squareNum > n / 2)
    {
        ans = squareNum - n / 2;
        if (zeroNum > n / 2)
            ans += (zeroNum - n / 2);  // Zero requires an extra addition!
    }
    else if (squareNum < n / 2)
    {
        long long int changeNum = n / 2 - squareNum;
        sort(minChange, minChange + minChangePt, cmpRule);
        for (int i = 0; i < changeNum; i++)
        {
            ans += minChange[i];
        }
    }
    cout << ans << endl;
    return 0;
}
