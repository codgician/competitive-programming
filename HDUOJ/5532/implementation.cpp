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

#define SIZE 100010

int arr[SIZE], num[2];

void update(bool type, int prev, int cnt)
{
    if (prev == cnt)
        return;

    int id = 0;
    if (prev > cnt)
        id = 1;

    if (type == 0)
        num[id]++;
    else
        num[id]--;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(num, 0, sizeof(num));
        int len;
        cin >> len >> arr[0];

        for (int i = 1; i < len; i++)
        {
            cin >> arr[i];
            update(0, arr[i - 1], arr[i]);
        }

        bool ans = false;
        for (int i = 0; i < len; i++)
        {
            if (i > 0)
                update(1, arr[i - 1], arr[i]);
            if (i < len - 1)
                update(1, arr[i], arr[i + 1]);
            if (i > 0 && i < len - 1)
                update(0, arr[i - 1], arr[i + 1]);

            if (num[0] == 0 || num[1] == 0)
            {
                ans = true;
                break;
            }

            if (i > 0)
                update(0, arr[i - 1], arr[i]);
            if (i < len - 1)
                update(0, arr[i], arr[i + 1]);
            if (i > 0 && i < len - 1)
                update(1, arr[i - 1], arr[i + 1]);
        }

        if (ans)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}