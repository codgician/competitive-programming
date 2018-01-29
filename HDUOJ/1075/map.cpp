#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
using namespace std;

map<string, string> dict;

int main()
{
    string earth, mars;
    cin >> earth;
    while (cin >> earth >> mars)
    {
        if (earth == "END")
        {
            break;
        }
        dict[mars] = earth;
    }

    getchar();
    char ch;
    mars = "";
    while ((ch = getchar()) != EOF)
    {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            mars += ch;
        }
        else
        {
            if (!mars.empty())
            {
                if (mars == "END")
                    break;
                string ans = dict[mars] + "";
                if (!ans.empty())
                {
                    cout << ans;
                }
                else
                    cout << mars;
            }
            cout << ch;
            mars = "";
        }
    }
    return 0;
}
