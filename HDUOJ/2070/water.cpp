#include <iostream>
#include <cstdio>
using namespace std;

long long int fibb[100];

int main()
{
    ios::sync_with_stdio(false);
    fibb[0] = 1;
    fibb[1] = 1;
    int n;
    while (cin >> n)
    {
        if (n == -1)
            break;
        for (int i = 2; i < n; i++)
            fibb[i] = fibb[i - 1] + fibb[i - 2];
        cout << fibb[n - 1] << endl;
    }
    return 0;
}
