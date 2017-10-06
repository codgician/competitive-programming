#include <iostream>
#include <cstdio>
using namespace std;

long long int calcCombination(int n, int k)
{
    // Optimizations.
    if (n == 0 || n == k)
        return 1;

    if (n > k / 2)
        n = k - n;

    long long int a = 1, b = 1;

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
    int n;
    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                cout << calcCombination(j, i);
                if (j == i)
                    cout << endl;
                else
                    cout << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
