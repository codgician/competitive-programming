#include <iostream>
#include <cstdio>
using namespace std;

int getGcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return getGcd(b, a % b);
}

int getLcm(int a, int b)
{
    return a / getGcd(a, b) * b;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int eleNum;
        cin >> eleNum;
        int prev, next;
        cin >> prev;
        int product = prev;
        for (int i = 1; i < eleNum; i++)
        {
            cin >> next;
            product *= next;
            prev = getLcm(prev, next);
        }
        cout << prev << endl;
    }
    return 0;
}
