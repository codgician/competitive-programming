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

int arr[SIZE];
long long int prefixSum[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    long long int roomNum, dis, std;
    cin >> roomNum >> dis >> std;
    prefixSum[0] = 0;
    for (int i = 1; i <= roomNum; i++)
    {
        cin >> arr[i];
        prefixSum[i] = prefixSum[i - 1] + arr[i];
    }

    long long int passNum, minPassNum = LLONG_MAX;

    // Satisfy left
    passNum = 0;
    for (long long int i = 1; i <= roomNum >> 1; i++)
    {
        long long int movableNum = prefixSum[min(roomNum, i * dis + i)] - passNum * std;
        if (movableNum >= std)
            passNum++;
    }
    minPassNum = min(minPassNum, passNum);

    // Satisfy right
    passNum = 0;
    for (long long int i = 1; i <= roomNum >> 1; i++)
    {
        long long int movableNum = prefixSum[roomNum] - prefixSum[max(0ll,  roomNum - i * dis - i)] - passNum * std;
        if (movableNum >= std)
            passNum++;
    }
    minPassNum = min(minPassNum, passNum);

    long long int ans = (roomNum >> 1) - minPassNum;
    cout << ans << endl;

    return 0;
}