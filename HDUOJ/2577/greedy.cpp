#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

bool isCaps(char c)
{
    return c >= 'A' && c <= 'Z';
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        string str;
        cin >> str;

        bool cntState = false;
        int ans = str.length();
        for (int i = 0; i < str.length(); i++)
        {
            if (isCaps(str[i]) == !cntState)
            {
                if (isCaps(str[i + 1]) == !cntState)
                {
                    // Press caps lock
                    cntState = !cntState;
                }
                ans++;
            }
        }
        if (cntState == true)
            ans++;
        cout << ans << endl;
    }
    return 0;
}
