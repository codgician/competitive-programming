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

#define SIZE 1100

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int num;
    while (cin >> num)
    {
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i];
        }
        sort(arr + 0, arr + num, [](int fst, int snd) {
            return fst > snd;
        });

        int ans = -1;
        for (int i = 0; i < num - 3; i++)
        {
            if (arr[i + 1] + arr[i + 2] > arr[i])
            {
                ans = arr[i] + arr[i + 1] + arr[i + 2];
                break; 
            }
        }
        cout << ans << endl;
    }
    return 0;
}