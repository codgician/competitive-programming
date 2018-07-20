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

#define SIZE 1000100

int aff[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int num;
        cin >> num;

        for (int i = 1; i <= num; i++)
            aff[i] = 0;

        int minVal = INT_MAX, secMinVal = INT_MAX;
        for (int i = 1; i <= num; i++)
        {
            int cnt;
            cin >> cnt;
            if (cnt <= minVal)
            {
                secMinVal = minVal;
                minVal = cnt;
            }
            else if (cnt >= minVal && cnt < secMinVal)
            {
                aff[minVal]++;
                aff[cnt]++;
                secMinVal = cnt;
            }
            else if (cnt >= secMinVal)
            {
                aff[cnt]++;
            }
        }

        int minAff = INT_MAX, ans = -1;
        for (int i = 1; i <= num; i++)
        {
            if (aff[i] < minAff)
            {
                minAff = aff[i];
                ans = i;
            }
        }
        cout << ans << endl;
    }
    return 0;
}