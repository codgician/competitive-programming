#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 101
using namespace std;

bool arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    memset(arr, false, sizeof(arr));
    int teleportNum, friendLoc;
    cin >> teleportNum >> friendLoc;
    for (int i = 0; i < teleportNum; i++)
    {
        int startPt, endPt;
        cin >> startPt >> endPt;
        for (int j = startPt + 1; j <= endPt; j++)
        {
            arr[j] = true;
        }
        if (startPt == 0)
            arr[0] = true;
    }

    bool ans = true;
    for (int i = 0; i <= friendLoc; i++)
    {
        if (!arr[i])
        {
            ans = false;
            break;
        }
    }

    if (ans)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
