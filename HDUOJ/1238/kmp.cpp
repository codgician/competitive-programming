#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 101
using namespace std;

string arr[SIZE];
int nextArr[SIZE];

void initNext(string &str)
{
    nextArr[0] = 0;
    for (int i = 1, matchNum = 0; i < (int)str.length(); i++)
    {
        while (matchNum > 0 && str[i] != str[matchNum]) // (matchNum + 1) - 1
            matchNum = nextArr[matchNum - 1];
        if (str[i] == str[matchNum])
            matchNum++;
        nextArr[i] = matchNum;
    }
}

bool kmp(string &a, string &b)
{
    for (int i = 0, matchNum = 0; i < (int)a.length(); i++)
    {
        while (matchNum > 0 && (matchNum== (int)b.length() || a[i] != b[matchNum]))
            matchNum = nextArr[matchNum - 1];
        if (a[i] == b[matchNum])
            matchNum++;
        if (matchNum == (int)b.length())
            return true;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int strNum;
        cin >> strNum;
        string minStr;
        int minStrLen = INT_MAX;
        for (int i = 0; i < strNum; i++)
        {
            cin >> arr[i];
            if ((int)arr[i].length() < minStrLen)
            {
                minStr = arr[i];
                minStrLen = arr[i].length();
            }
        }

        int ans = 0;
        for (int i = minStr.length(); i > 0; i--)
        {
            for (int j = 0; j + i <= (int)minStr.length(); j++)
            {
                string cmpStr = minStr.substr(j, i);
                initNext(cmpStr);
                bool isValid = true;
                for (int k = 0; k < strNum; k++)
                {
                    if (!kmp(arr[k], cmpStr))
                    {
                        if (i > 1)
                        {
                            string revStr = cmpStr;
                            reverse(revStr.begin(), revStr.end());
                            initNext(revStr);
                            if (kmp(arr[k], revStr))
                            {
                                initNext(cmpStr);
                                continue;
                            }
                        }
                        isValid = false;
                        break;
                    }
                }

                if (isValid)
                {
                    ans = i;
                    break;
                }
            }

            if (ans > 0)
                break;
        }

        cout << ans << endl;
    }
    return 0;
}
