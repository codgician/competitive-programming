#include <iostream>
#include <cstdio>
#define SIZE 21
using namespace std;

long long int arr[SIZE];

void init()
{
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 1;
    for (int i = 3; i < SIZE; i++)
        arr[i] = (i - 1) * (arr[i - 1] + arr[i - 2]);
}

long long int calcCombination(int n, int k)
{
    if (n == 0 || n == k)
        return 1;
    if (n > k / 2)
        n = k - n;

    long long int ans = 1, a = 1, b = 1;
    for (int i = 1; i <= n; i++)
    {
        a *= k + 1 - i;
        b *= i;
    }

    return a / b;
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int n, m;
        cin >> n >> m;
        cout << calcCombination(m, n) * arr[m] << endl;
    }
    return 0;
}
