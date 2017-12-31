#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#define SIZE 1001
using namespace std;

bool hasAppeared[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    memset(hasAppeared, false ,sizeof(hasAppeared));
    int n;
    cin >> n;
    int ans = true;
    for (int i = 0; i < n; i++)
    {
        int cnt = (i * i) % n;
        if (hasAppeared[cnt])
        {
            ans = false;
            break;
        }
        else
        {
            hasAppeared[cnt] = true;
        }
    }
    if (ans)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    return 0;
}
