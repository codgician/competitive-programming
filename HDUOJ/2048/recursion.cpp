#include <iostream>
#include <cstdio>
#define SIZE 21
using namespace std;

long long int arr[SIZE];

void getAns()
{
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 1;
    arr[3] = 2;
    for (int i = 4; i < SIZE; i++)
        arr[i] = (i - 1) * (arr[i - 2] + arr[i - 1]);
}

long long int getArrange(int n, int k)
{
    long long int ans = 1;
    for (int i = n; i > n - k; i--)
        ans *= i;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    getAns();
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int n;
        cin >> n;
        if (n == 1)
            printf("100.00%%\n");
        else
            printf("%.2lf%%\n", 100 * (double)arr[n] / getArrange(n, n));
    }
    return 0;
}
