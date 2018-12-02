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
    string s;
    cin >> s;
    int prev = s[0] - '0';
    bool flag = true;
    for (int i = 1; i < s.length(); i++)
    {
        if (s[i] - '0' != prev)
        {
            flag = false;
            break;
        }
        prev = s[i] - '0';
    }
    if  (flag)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
