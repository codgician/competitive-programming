#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int stopCond, onceMax;
    while (cin >> stopCond >> onceMax)
    {
        if (onceMax > stopCond)
        {
            for (int i = stopCond; i <= onceMax; i++)
            {
                cout << i;
                if (i < onceMax)
                    cout << " ";
                else
                    cout << endl;
            }
        }
        else
        {
            int ans = stopCond % (onceMax + 1);
            if (ans == 0)
            {
                cout << "none" << endl;
            }
            else
            {
                cout << ans << endl;
            }
        }
    }
    return 0;
}
