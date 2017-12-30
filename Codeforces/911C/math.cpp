#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

int arr[3];

int main()
{
    ios::sync_with_stdio(false);
    for (int i = 0; i < 3; i++)
    {
        cin >> arr[i];
    }
    sort(arr + 0, arr + 3);
    if (arr[0] == 1)  // If "1" exists
    {
        cout << "YES" << endl;
    }
    else if (arr[0] == arr[1] && arr[0] == 2)  // If 2 * "2" exist
    {
        cout << "YES" << endl;
    }
    else if (arr[0] == arr[1] && arr[1] == arr[2] && arr[0] == 3) // If 3 * "3" exist
    {
        cout << "YES" << endl;
    }
    else if (arr[0] == 2 && arr[1] == 4 && arr[2] == 4)  // Special: 2, 4, 4
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
    return 0;
}
