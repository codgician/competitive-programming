#include <iostream>
#include <cstdio>
#define SIZE 31
using namespace std;

unsigned long long int ans[SIZE];

void init()
{
    ans[1] = 1;
    ans[2] = 3;
    for (int i = 3; i < SIZE; i++)
        ans[i] = ans[i - 1] + 2 * ans[i - 2];
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int n;
        cin >> n;
        cout << ans[n] << endl;
    }
    return 0;
}
