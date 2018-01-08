#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int num;
    while (cin >> num)
    {
        if (num == 0)
            break;
        int maxAC = -1;
        for (int i = 0; i < num; i++)
        {
            int cnt;
            cin >> cnt;
            maxAC = max(maxAC, cnt);
        }
        cout << maxAC << endl;
    }
    return 0;
}
