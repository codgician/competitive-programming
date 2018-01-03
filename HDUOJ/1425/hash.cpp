#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#define SIZE 1000001
#define C 500000
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m)
    {
        memset(arr, 0, sizeof(arr));
        int pt = 0;
        for (int i = 0; i < n; i++)
        {
            int tmp;
            cin >> tmp;
            arr[tmp + C]++;
            pt = max(pt, tmp + C);
        }

        while (m > 0 && pt >= 0)
        {
            while (arr[pt])
            {
                cout << pt - C;
                arr[pt]--;
                m--;
                if (m == 0)
                    cout << endl;
                else
                    cout << " ";
            }
            pt--;
        }
    }
    return 0;
}
