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

#define SIZE 1024

int arr[SIZE][SIZE];
int ans[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        memset(arr, 0, sizeof(arr));
        memset(ans, 0, sizeof(ans));
        int papNum, probNum, k;
        cin >> papNum >> probNum >> k;

        int totState = 1 << probNum;
        for (int i = 0; i < papNum; i++)
        {
            string str;
            cin >> str;

            int state = 0;
            for (int i = 0; i < probNum; i++)
            {
                if (str[i] == 'B')
                    state += (1 << (probNum - i - 1));
            }
            for (int j = 0; j < totState; j++)
            {
                ans[j] += i - arr[j][(state & j)];
                arr[j][(state & j)]++;
            }
        }

        int num = 0;
        for (int i = 0; i < totState; i++)
        {
            if (ans[i] >= k)
                num++;
        }

        cout << "Case #" << t << ": " << num << endl;
    }
    return 0;
}