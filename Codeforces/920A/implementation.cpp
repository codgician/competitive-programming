#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 201
using namespace std;

bool arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(arr, false, sizeof(arr));
        int bedNum, tapNum;
        cin >> bedNum >> tapNum;
        for (int i = 0; i < tapNum; i++)
        {
            int tmp;
            cin >> tmp;
            tmp--;
            arr[tmp] = true;
        }
        int lastPt = -1, maxGap = 0;
        for (int i = 0; i < bedNum; i++)
        {
            if (arr[i])
            {
                if (lastPt == -1)
                {
                    maxGap = i - lastPt;
                }
                else
                {
                    maxGap = max(maxGap, (i - lastPt + 2) >> 1);
                }

                lastPt = i;
            }
        }
        maxGap = max(maxGap, bedNum - lastPt);
        cout << maxGap << endl;
    }
    return 0;
}
