#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 200001
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int height;
    cin >> height;
    bool isAmbiguous = false;
    int lastAmbigiousHeight = 0;
    cin >> arr[0];
    for (int i = 1; i <= height; i++)
    {
        cin >> arr[i];
        if (arr[i - 1] > 1 && arr[i] > 1)
        {
            isAmbiguous = true;
            lastAmbigiousHeight = i;
        }
    }
    if (isAmbiguous)
    {
        cout << "ambiguous" << endl;

        // All on one node
        cout << 0;
        int cnt = 1;
        for (int i = 1; i <= height; i++)
        {
            for (int j = 0; j < arr[i]; j++)
            {
                cout << " " << cnt;
            }
            cnt += arr[i];
        }
        cout << endl;

        // Shift a little
        cout << 0;
        cnt = 1;
        for (int i = 1; i <= height; i++)
        {
            if (i == lastAmbigiousHeight)
            {
                for (int j = 0; j < arr[i] - 1; j++)
                {
                    cout << " " << cnt;
                }
                cout << " " << cnt - arr[i - 1] + 1;
            }
            else
            {
                for (int j = 0; j < arr[i]; j++)
                {
                    cout << " " << cnt;
                }
            }
            cnt += arr[i];
        }
        cout << endl;
    }
    else
    {
        cout << "perfect" << endl;
    }
    return 0;
}
