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

#define SIZE 210

int arr[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    memset(arr, 0, sizeof(arr));
    int num;
    cin >> num;

    arr[0][0] = 1;
    arr[1][1] = 1;

    for (int i = 2; i <= num; i++)
    {
        for (int j = 0; j < i; j++)
        {
            arr[i][j + 1] = arr[i - 1][j];
        }

        for (int j = 0; j < i - 1; j++)
        {
            arr[i][j] = (arr[i][j] + arr[i - 2][j]) & 1;
        }
    }

    cout << num << endl;
    for (int i = 0; i <= num; i++)
        cout << arr[num][i] << " ";
    cout << endl;
    cout << num - 1 << endl;
    for (int i = 0; i < num; i++)
        cout << arr[num - 1][i] << " ";
    cout << endl;

    return 0;
}