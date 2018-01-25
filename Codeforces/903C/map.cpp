#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 5001
using namespace std;

map<int, int> box;

int main()
{
    ios::sync_with_stdio(false);
    int boxNum;
    cin >> boxNum;
    int ans = 0;
    for (int i = 0; i < boxNum; i++)
    {
        int tmp;
        cin >> tmp;
        box[tmp]++;
        ans = max(ans, box[tmp]);
    }
    cout << ans << endl;
    return 0;
}
