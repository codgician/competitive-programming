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

#define SIZE 110

map<string, int> mp;
int fst[SIZE], snd[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    memset(fst, 0, sizeof(fst));
    memset(snd, 0, sizeof(snd));

    mp["XXXS"] = 1;
    mp["XXS"] = 2;
    mp["XS"] = 3;
    mp["S"] = 4;
    mp["M"] = 5;
    mp["L"] = 6;
    mp["XL"] = 7;
    mp["XXL"] = 8;
    mp["XXXL"] = 9;

    int num;
    cin >> num;

    for (int i = 0; i < num; i++)
    {
        string cnt;
        cin >> cnt;
        fst[mp[cnt]]++;
    }
    for (int i = 0; i < num; i++)
    {
        string cnt;
        cin >> cnt;
        snd[mp[cnt]]++;
    }

    bool isIdentical = true;
    for (int i = 1; i <= 9; i++)
    {
        if (fst[i] != snd[i])
        {
            isIdentical = false;
            break;
        }
    }

    if (isIdentical)
    {
        cout << 0 << endl;
        return 0;
    }

    int ans = 0;
    for (int i = 1; i <= 9; i++)
    {
        fst[i] -= snd[i];
        if (fst[i] > 0)
            ans += fst[i];
    }

    cout << ans << endl;
    return 0;
}