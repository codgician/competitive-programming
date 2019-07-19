#include <iostream>
#include <cstdio>
using namespace std;

long long int calc(int a, int b, int c)
{
    long long int ans = 1;
    for (int i = 0; i < b; i++)
        ans = (ans * (a % c)) % c;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int i = 0; i < caseNum; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        cout << calc(a, b, c) << endl;
    }
    return 0;
}
