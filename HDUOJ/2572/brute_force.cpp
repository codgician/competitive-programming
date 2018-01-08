#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#define SIZE 101
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        string s;
        cin >> s;
        string a, b;
        cin >> a >> b;

        bool hasFound = false;
        string ans;
        for (int i = 0; i < s.length(); i++)
        {
            for (int j = i + 1; j < s.length(); j++)
            {
                string sub = s.substr(i, j - i);
                if (sub.find(a) != -1 && sub.find(b) != -1)
                {
                    if (!hasFound || sub.length() < ans.length())
                    {
                        ans = sub;
                        hasFound = true;
                    }
                    else if (sub.length() == ans.length())
                    {
                        if (sub < ans)
                        {
                            ans = sub;
                        }
                    }
                }
            }
        }

        if (!hasFound)
            cout << "No" << endl;
        else
            cout << ans << endl;
    }
    return 0;
}
