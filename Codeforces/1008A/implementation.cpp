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

bool isVowel(char ch)
{
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

int main()
{
    ios::sync_with_stdio(false);
    string str;
    cin >> str;

    bool ans = true;
    for (int i = 0; i < (int)str.size(); i++)
    {
        if (!isVowel(str[i]) && str[i] != 'n')
        {
            if (i == (int)str.size() - 1 || !isVowel(str[i + 1]))
            {
                ans = false;
                break;
            }
        }
    }

    if (ans)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}