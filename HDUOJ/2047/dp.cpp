#include <iostream>
#include <cstdio>
#define SIZE 41
using namespace std;

long long ans[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    ans[1] = 3;
    ans[2] = 8;
    for (int i = 3; i < SIZE; i++)
        ans[i] = 2 * (ans[i - 1] + ans[i - 2]);
    int n;
    while (cin >> n)
        cout << ans[n] << endl;
    return 0;
}
