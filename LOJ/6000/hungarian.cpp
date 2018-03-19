#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 101
using namespace std;

bool arr[SIZE][SIZE];
bool sndVisited[SIZE];
int sndMatch[SIZE];
int fstNum, sndNum;

bool canFind(int fstId)
{
    for (int i = 0; i < sndNum; i++)
    {
        if (!sndVisited[i] && arr[fstId][i])
        {
            sndVisited[i] = true;
            if (sndMatch[i] == -1 || canFind(sndMatch[i]))
            {
                sndMatch[i] = fstId;
                return true;
            }
        }
    }
    return false;
}

int hungarian()
{
    int ans = 0;
    memset(sndMatch, -1, sizeof(sndMatch));
    for (int i = 0; i < fstNum; i++)
    {
        memset(sndVisited, false, sizeof(sndVisited));
        if (canFind(i))
            ans++;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int totNum;
    cin >> totNum >> fstNum;
    sndNum = totNum - fstNum;

    memset(arr, false, sizeof(arr));
    int fst, snd;
    while (cin >> fst >> snd)
    {
        arr[fst - 1][snd - fstNum - 1] = true;
    }

    int ans = hungarian();
    cout << ans << endl;
    return 0;
}
