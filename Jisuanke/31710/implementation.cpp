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

void convert(string & str)
{
    for (auto it = str.begin(); it != str.end(); it++)
    {
        if (*it >= 'A' && *it <= 'Z')
            *it = 'a' + *it - 'A';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int qNum;
    while (cin >> qNum)
    {
        while (qNum--)
        {
            string name;
            cin >> name;
            convert(name);

            if (name == "jessie")
                cout << "Good guy!" << endl;
            else
                cout << "Dare you say that again?" << endl;
        }
    }

    return 0;
}