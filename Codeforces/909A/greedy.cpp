#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    string first, last;
    cin >> first >> last;
    cout << first[0];
    bool flag = false;
    for (int i = 1; i < first.length(); i++)
    {
        if (first[i] >= last[0])
        {
            flag = true;
            for (int j = 1; j < i; j++)
                cout << first[j];
                break;
        }
    }
    if (!flag)
        for (int i = 1; i < first.length(); i++)
            cout << first[i];
    cout << last[0] << endl;
    return 0;
}
