#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    string s;
    while (getline(cin, s))
    {
        int ans = 0;
        for (int i = 0; i < s.length() - 1; i++)
        {
            if (s[i] == 'i' && s[i + 1] == 'f')
                ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
