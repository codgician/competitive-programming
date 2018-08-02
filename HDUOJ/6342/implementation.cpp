#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

bool isOpr(char ch)
{
    return ch == '+' || ch == '*';
}

bool isNonZeroDigit(char ch)
{
    return ch - '0' > 0 && ch - '0' <= 9;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        string str;
        cin >> str;
        int len = (int)str.size();

        bool ans = true;
        bool flag = false;
        for (int i = 0; i < len; i++)
        {
            if (isOpr(str[i]))
            {
                if (i == 0 || i == len - 1 || isOpr(str[i - 1]) || isOpr(str[i + 1]))
                {
                    ans = false;
                    break;
                }
                flag = false;
            }
            else if (str[i] == '0')
            {
                if (i == 0 && (len > i + 1 && !isOpr(str[i + 1]) && str[i + 1] != '?'))
                {
                    ans = false;
                    break;
                }

                if (i > 0 && isOpr(str[i - 1]))
                {
                    if (len > i + 1 && !isOpr(str[i + 1]) && str[i + 1] != '?')
                    {
                        ans = false;
                        break;
                    }
                }

                if (len > i + 1 && str[i + 1] == '?' && !flag)
                {
                    str[i + 1] = '+';
                }
            }
            else if (str[i] == '?')
            {
                str[i] = '1';
                flag = true;
            }
            else
                flag = true;
        }

        if (ans)
            cout << str << endl;
        else
            cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}