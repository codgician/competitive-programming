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
#define SIZE 50010
using namespace std;

string arr[SIZE];
map<string, bool> mp;

int main()
{
    ios::sync_with_stdio(false);
    string str;
    int arrPt = 0;
    while (cin >> arr[arrPt])
    {
        mp[arr[arrPt]] = true;
        arrPt++;
    }

    for (int i = 0; i < arrPt; i++)
    {
        for (int j = 1; j <= arr[i].length() - 1; j++)
        {
            string s1 = arr[i].substr(0, j);
            string s2 = arr[i].substr(j);

            if (mp[s1] && mp[s2])
            {
                cout << arr[i] << endl;
                break;
            }
        }
    }
    return 0;
}
