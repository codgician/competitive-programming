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

#define SIZE 300010

long long int arr[SIZE], queArr[SIZE];
int len, k;

bool check(int cnt)
{
    if (cnt == 0)
        return true;

    int arrPt = 0, quePt = 0, roundPt = 0;
    memset(queArr, 0, sizeof(queArr));

    while (arrPt < len)
    {
        if (arr[arrPt] >= (queArr[quePt] << 1))
        {
            queArr[quePt] = arr[arrPt];
            quePt++;
            arrPt++;
            if (quePt == cnt)
            {
                roundPt++;
                if (roundPt == k)
                    return true;
                quePt = 0;
            }
        }
        else
        {
            arrPt++;
        }
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        cin >> len >> k;
        for (int i = 0; i < len; i++)
        {
            cin >> arr[i];
        }

        sort(arr + 0, arr + len);

        int leftPt = 0, rightPt = len / k;

        int ans = 0;
        while (leftPt <= rightPt)
        {
            int midPt = (leftPt + rightPt) >> 1;
            if (check(midPt))
            {
                ans = midPt;
                leftPt = midPt + 1;
            }
            else
            {
                rightPt = midPt - 1;
            }
        }

        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}