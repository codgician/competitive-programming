#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 5001
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int planeNum;
    cin >> planeNum;
    for (int i = 0; i < planeNum; i++)
    {
        cin >> arr[i];
        arr[i]--;
    }

    bool ans = false;
    for (int i = 0; i < planeNum; i++)
    {
        if (arr[i] != i && arr[arr[i]] != arr[i] && arr[arr[i]] != i && arr[arr[arr[i]]] != arr[arr[i]] && arr[arr[arr[i]]] == i)
        {
            ans = true;
            break;
        }
    }

    if (ans)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
