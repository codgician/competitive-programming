#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

long long int rikkaArr[3], yutaArr[3];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        long long int sum = 0;
        for (int i = 0; i < 3; i++)
        {
            cin >> yutaArr[i];
        }
        for (int i = 0; i < 3; i++)
        {
            cin >> rikkaArr[i];
            sum += rikkaArr[i];
        }

        long long int up = 0, down = sum;
        for (int i = 0; i < 3; i++)
        {
            up += yutaArr[i] * (rikkaArr[(i + 1) % 3] - rikkaArr[(i + 2) % 3]);
        }

        bool isNeg = false;
        if (up < 0)
        {
            isNeg = true;
            up = -up;
        }

        long long int gcd = __gcd(up, down);
        up /= gcd;
        down /= gcd;

        if (isNeg)
        {
            up = -up;
        }

        if (up == 0)
            cout << 0 << endl;
        else if (down == 1)
            cout << up << endl;
        else
            cout << up << "/" << down << endl;
    }
    return 0;
}