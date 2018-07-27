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

#define SIZE 31

int arr[SIZE];

int ask(int val)
{
    cout << val << endl << flush;
    int ret;
    cin >> ret;
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    int maxDis, len;
    cin >> maxDis >> len;

    for (int i = 0; i < len; i++)
    {
        arr[i] = ask(1);
        if (arr[i] == 0)
            return 0;
    }

    int cntPos = 0;
    int leftPt = 1, rightPt = maxDis;
    while (leftPt <= rightPt)
    {
        int midPt = (leftPt + rightPt) >> 1;
        int cnt = ask(midPt);
        if (cnt == 0)
            return 0;

        if (arr[cntPos] == -1)
            cnt = -cnt;
        cntPos = (cntPos + 1) % len;

        if (cnt == -1)
        {
            rightPt = midPt - 1;
        }
        else if (cnt == 1)
        {
            leftPt = midPt + 1;
        }
    }

    ask(leftPt);

    return 0;
}