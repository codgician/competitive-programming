#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

int interval[26], lastPos[26];

int main()
{
    ios::sync_with_stdio(false);
    string s;
    cin >> s;

    for (int i = 0; i < 26; i++)
    {
        interval[i] = -1;
        lastPos[i] = -1;
    }

    for (int i = 0; i < s.length(); i++)
    {
        int index = s[i] - 'a';
        interval[index] = max(interval[index], i - lastPos[index] - 1);
        lastPos[index] = i;
    }

    int minInterval = s.length();
    for (int i = 0; i < 26; i++)
    {
        if (interval[i] != -1)
        {
            if (lastPos[i] != s.length() - 1)
                interval[i] = max(interval[i], (int)s.length() - lastPos[i] - 1);
            if (interval[i] < minInterval)
                minInterval = interval[i];
        }
    }

    cout << minInterval + 1 << endl;
    return 0;
}
