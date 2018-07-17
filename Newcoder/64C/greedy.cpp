#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 100001
using namespace std;

typedef struct _Chocolate {
    int morning;
    int evening;
    int delta;
} chocolate;

chocolate arr[SIZE];

bool cmpRule(chocolate a, chocolate b)
{
    return a.delta > b.delta;
}

int main()
{
    ios::sync_with_stdio(false);
    int chocoNum, morningNum;
    cin >> chocoNum >> morningNum;
    int eveningNum = chocoNum - morningNum;
    for (int i = 0; i < chocoNum; i++)
    {
        cin >> arr[i].morning;
    }
    for (int i = 0; i < chocoNum; i++)
    {
        cin >> arr[i].evening;
        arr[i].delta = abs(arr[i].morning - arr[i].evening);
    }

    sort(arr + 0, arr + chocoNum, cmpRule);

    long long int ans = 0;
    for (int i = 0; i < chocoNum; i++)
    {
        if (arr[i].morning > arr[i].evening)
        {
            if (morningNum > 0)
            {
                ans += arr[i].morning;
                morningNum--;
            }
            else
            {
                ans += arr[i].evening;
                eveningNum--;
            }
        }
        else
        {
            if (eveningNum > 0)
            {
                ans += arr[i].evening;
                eveningNum--;
            }
            else
            {
                ans += arr[i].morning;
                morningNum--;
            }
        }
    }

    cout << ans << endl;
    return 0;
}
