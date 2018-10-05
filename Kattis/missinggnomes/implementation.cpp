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

#define SIZE 100010

bool arr[SIZE];
int partialArr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num, partialNum;
    while (cin >> num >> partialNum)
    {
        memset(arr, false, sizeof(arr));
        for (int i = 0; i < partialNum; i++)
        {
            cin >> partialArr[i];
            arr[partialArr[i]] = true;
        }

        int cntPt = 1;
        for (int i = 0; i < partialNum; i++)
        {
            while (cntPt < partialArr[i])
            {
                if (!arr[cntPt])
                    cout << cntPt << endl;
                cntPt++;
            }
            cout << partialArr[i] << endl;
        }

        while (cntPt <= num)
        {
            if (!arr[cntPt])
                cout << cntPt << endl;
            cntPt++;
        }
    }

    return 0;
}