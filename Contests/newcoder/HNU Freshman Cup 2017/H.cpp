#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#define SIZE 10001
using namespace std;

long long int arr[SIZE];
const long long int mod = 100000007;

long long int getA(long long int m, long long int n)
{
    if (m == 0)
        return 1;
    long long int ans = n % mod;
    for (long long int i = n - 1; i > n - m; i--)
    {
        ans *= i;
        ans %= mod;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        long long int ballonNum, pigmentNum;
        cin >> ballonNum >> pigmentNum;

        arr[0] = pigmentNum;
        arr[1] = getA(2, pigmentNum);
        arr[2] = arr[1] * (pigmentNum - 2);
        for (long long int i = 3; i < ballonNum; i++)
        {
            arr[i] = (((pigmentNum - 2) * arr[i - 1]) % mod + ((pigmentNum - 1) * arr[i - 2]) % mod) % mod;
        }
        cout << arr[ballonNum - 1] << endl;
    }
    return 0;
}
