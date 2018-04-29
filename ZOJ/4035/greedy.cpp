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
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 101
using namespace std;

typedef struct _Word
{
    string str;
    long long int pref;
} Word;

Word arr[SIZE];

bool cmpRule(Word &a, Word &b)
{
    if (a.pref == b.pref)
    {
        for (int i = 0; i < min((int)a.str.length(), (int)b.str.length()); i++)
        {
            if (a.str[i] == b.str[i])
            {
                continue;
            }

            return a.str[i] < b.str[i];
        }

    return a.str.length() < b.str.length();
    }

    return a.pref > b.pref;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int wordNum, needNum;
        cin >> wordNum >> needNum;
        for (int i = 0; i < wordNum; i++)
        {
            cin >> arr[i].str >> arr[i].pref;
        }

        sort(arr + 0, arr + wordNum, cmpRule);

        long long int ans = 0;
        for (int i = 0; i < needNum; i++)
        {
            ans += (needNum - i) * arr[i].pref;
        }

        cout << ans;

        for (int i = 0; i < needNum; i++)
        {
            cout << " " << arr[i].str;
        }
        cout << endl;
    }
    return 0;
}