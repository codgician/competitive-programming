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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


    int len;
    cin >> len;
    string str;
    cin >> str;

    for (int i = 0; i < len - 1; i++)
    {
        if (str[i] != str[i + 1])
        {
            cout << "YES" << endl;
            cout << str[i] << str[i + 1] << endl;
            return 0;
        }
    }

    cout << "NO" << endl;
    return 0;
}