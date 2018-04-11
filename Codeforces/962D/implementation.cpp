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
#include <map>
#include <set>
#include <list>
#define SIZE 151000
using namespace std;

unsigned long long int arr[SIZE];
map<unsigned long long int, int> mp;

int main()
{
    ios::sync_with_stdio(false);
    int intNum;
    cin >> intNum;
    for (int i = 0; i < intNum; i++)
    {
        cin >> arr[i];
    }

    int cntSize = intNum;
    for (int i = 0; i < intNum; i++)
    {
        if (mp.find(arr[i]) == mp.end() || mp[arr[i]] == -1)
        {
            mp[arr[i]] = i;
            continue;
        }

        while (mp.find(arr[i]) != mp.end() && mp[arr[i]] < i)
        {
            if (mp[arr[i]] == -1)
            {
                mp[arr[i]] = i;
                break;
            }

            arr[mp[arr[i]]] = 0;
            mp[arr[i]] = -1;
            cntSize--;
            arr[i] <<= 1;

            if (mp.find(arr[i]) == mp.end())
            {
                mp[arr[i]] = i;
                break;
            }
        }
    }

    cout << cntSize << endl;
    bool isFirst = true;
    for (int i = 0; i < intNum; i++)
    {
        if (arr[i] > 0)
        {
            if (isFirst)
                isFirst = false;
            else
                cout << " ";
            cout << arr[i];
        }
    }
    cout << endl;
    return 0;
}
