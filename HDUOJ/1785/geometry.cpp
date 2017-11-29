#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>
#define SIZE 101
using namespace std;

typedef struct _Dot {
    double x;
    double y;
} dot;

dot arr[SIZE];

double getCrossedProduct(dot a, dot b)
{
    return a.x * b.y - b.x * a.y;
}

bool cmpRule(dot a, dot b)
{
    if (getCrossedProduct(a, b) > 0)
        return true;
    else
        return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int acmerNum;
    while (cin >> acmerNum)
    {
        if (acmerNum < 0)
            break;

        for (int i = 0; i < acmerNum; i++)
        {
            cin >> arr[i].x >> arr[i].y;
        }

        sort(arr + 0, arr + acmerNum, cmpRule);

        for (int i = 0; i < acmerNum; i++)
        {
            cout << fixed << setprecision(1) << arr[i].x << " " << arr[i].y;
            if (i < acmerNum - 1)
                cout << " ";
            else
                cout << endl;
        }
    }
    return 0;
}
