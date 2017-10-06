#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

char num[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E' ,'F'};

int main()
{
    ios::sync_with_stdio(false);
    int n, r;
    while (cin >> n >> r)
    {
        bool isNeg = false;
        int pt = 0;
        char str[10010];
        if (n < 0)
        {
            isNeg = true;
            n = abs(n);
        }
        while (n >= r)
        {
            str[pt] = num[(n % r)];
            pt++;
            n /= r;
        }
        str[pt] = num[n];
        if (isNeg)
            cout << "-";
        for (int i = pt; i >= 0; i--)
            cout << str[i];
        cout << endl;
    }
    return 0;
}
