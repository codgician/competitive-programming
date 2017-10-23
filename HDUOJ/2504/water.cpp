#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int getGcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return getGcd(b, a % b);
}

bool isRelativelyPrime(int a, int b)
{
    if (getGcd(a, b) == 1)
        return true;
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
        int i = a / b;
        int j = 2;
        while (true)
        {
            if (getGcd(i, j) == 1)
                break;
            else
                j++;
        }
        cout << b * j << endl;
    }
    return 0;
}
