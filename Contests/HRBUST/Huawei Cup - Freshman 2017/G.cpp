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
    while (cin >> s)
    {
        bool isValid = true;
        for (int i = 0, j = s.length() - 1; i < j; i++, j--)
        {
            if (s[i] != s[j])
            {
                isValid = false;
                break;
            }
        }
        if (isValid)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}
