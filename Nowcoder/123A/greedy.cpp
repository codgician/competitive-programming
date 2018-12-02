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

#define SIZE 60

bool used[SIZE];

int getDis(char a, char b)
{
    if (a >= b)
        return a - b;
    return a + 26 - b; 
}

int main()
{
    ios::sync_with_stdio(false);
    string fst, snd;
    while (cin >> fst >> snd)
    {
        memset(used, false, sizeof(used));
        int ans = 0;
        for (int i = 0; i < (int)fst.size(); i++)
        {
            int minPt = -1, minDis = INT_MAX;
            for (int j = 0; j < (int)snd.size(); j++)
            {
                if (used[j])
                    continue;
                int cntDis = getDis(snd[j], fst[i]);
                if (cntDis < minDis)
                {
                    minPt = j;
                    minDis = cntDis;
                }
            }
            used[minPt] = true;
            ans += minDis;
        }
        cout << ans << endl;
    }
    return 0;
}