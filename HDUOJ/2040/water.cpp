#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int getDivisorSum(int n)
{
    int sum = 1;
    for (int i = 2; i <= n / 2; i++)
        if (n % i == 0)
        {
            sum += i;
        }

    return sum;
}

bool isFriendly(int a, int b)
{
    if (getDivisorSum(a) == b && getDivisorSum(b) == a)
        return true;
    else
        return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int a, b;
        cin >> a >> b;
        if (isFriendly(a, b))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
