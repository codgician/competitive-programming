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

map<string, int> ansMp;
map<string, bool> usedMp;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num;
    while (cin >> num)
    {
        ansMp.clear();
        for (int i = 0; i < num; i++)
        {
            string str;
            cin >> str;

            int len = str.size();
            str = str + str;

            usedMp.clear();

            for (int startPt = 0; startPt < len; startPt++)
            {
                for (int j = 1; j < (1 << len); j++)
                {
                    string cnt = "";
                    for (int k = 0; k < len; k++)
                    {
                        if (j & (1 << k))
                        {
                            cnt += str[startPt + k];
                        }
                    }

                    if (usedMp[cnt] == false)
                    {
                        ansMp[cnt]++;
                        usedMp[cnt] = true;
                    }
                }
            }
        }

        string ans = "";
        for (auto it = ansMp.begin(); it != ansMp.end(); ++it)
        {
            if (it -> second == num)
            {
                if (it -> first.size() > ans.size())
                {
                    ans = it -> first;
                }
            }
        }

        if (ans.empty())
            cout << 0 << endl;
        else
            cout << ans << endl;
    }

    return 0;
}