#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

int getNum(char c)
{
    if (c == 'I')
        return 1;
    else if (c == 'V')
        return 5;
    else if (c == 'X')
        return 10;
    else if (c == 'L')
        return 50;
    else if (c == 'C')
        return 100;
    else if (c == 'D')
        return 500;
    else if (c == 'M')
        return 1000;
}

int main()
{
    ios::sync_with_stdio(false);
    string s;
    while (cin >> s)
    {
        int ans = 0;
        for(int i = 0; i < s.length(); i++)
        {
            if (i == s.length() - 1 || getNum(s[i + 1]) <= getNum(s[i]))
                ans += getNum(s[i]);
            else
                ans -= getNum(s[i]);
        }
        cout << ans << endl;
    }
    return 0;
}
