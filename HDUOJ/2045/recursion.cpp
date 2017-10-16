#include <iostream>
#include <cstdio>
#define SIZE 51
using namespace std;

long long ans[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    ans[1] = 3;
    ans[2] = 6;
    ans[3] = 6;
    for (int i = 4; i < SIZE; i++)
        ans[i] = ans[i - 1] + 2 * ans[i - 2];
    int n;
    while (cin >> n)
        cout << ans[n] << endl;
    return 0;
}
