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

#define DIV_SIZE 5010

int arr[DIV_SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(arr, 0, sizeof(arr));
        int len, div;
        cin >> len >> div;

        int cntPfx = 0;
        arr[0] = 1;
        bool ans = false;
        for (int i = 1; i <= len; i++)
        {
            int cnt;
            cin >> cnt;
            cntPfx = (cntPfx + cnt) % div;
            arr[cntPfx]++;

            if (arr[cntPfx] > 1)
                ans = true;
        }

        cout << (ans ? "YES" : "NO") << endl;
    }

    return 0;
}