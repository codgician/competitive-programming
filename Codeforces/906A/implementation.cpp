#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

bool arr[26];

int main()
{
    ios::sync_with_stdio(false);
    memset(arr, true, sizeof(arr));
    int queryNum;
    cin >> queryNum;

    bool isFirst = true;
    bool canBeDetermined = false;
    int ans = 0;
    for (int i = 0; i < queryNum; i++)
    {
        char opr;
        cin >> opr;
        if (opr == '!')
        {
            string s;
            cin >> s;

            if (canBeDetermined)
            {
                for (int j = 0; j < s.length(); j++)
                {
                    if (arr[s[j] - 'a'])
                    {
                        ans++;
                        break;
                    }
                }
            }
            else
            {
                for (int j = 0; j < 26; j++)
                {
                    char c = 'a' + j;
                    if (arr[j] && s.find(c) == string::npos)
                    {
                        arr[j] = false;
                    }
                }
            }
        }
        else if (opr == '.')
        {
            string s;
            cin >> s;
            for (int j = 0; j < s.length(); j++)
            {
                arr[s[j] - 'a'] = false;
            }
        }
        else if (opr == '?')
        {
            char c;
            cin >> c;
            // The show ends with a correct guess,
            // therefore guessed before the last are all incorrect.
            if (i < queryNum - 1)
            {
                arr[c - 'a'] = false;
                if (canBeDetermined)
                    ans++;
            }
        }

        if (!canBeDetermined)
        {
            int trueNum = 0;
            for (int j = 0; j < 26; j++)
            {
                char ch = 'a' + j;
                if (arr[j])
                    trueNum++;
            }
            if (trueNum == 1)
            {
                canBeDetermined = true;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
