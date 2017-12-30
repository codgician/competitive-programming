#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int arr[20];

int main()
{
    ios::sync_with_stdio(false);
    arr[0] = 2;
    arr[1] = 3;
    int n;
    cin >> n;
    for (int i = 2; i < n; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
    cout << arr[n - 1] << endl;
    return 0;
}
