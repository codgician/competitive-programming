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

#define SIZE 101

bool arr[SIZE][SIZE];
pair<int, int> areaArr[3];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> areaArr[0].first >> areaArr[1].first >> areaArr[2].first)
    {
        areaArr[0].second = 3;  // zyx: 011
        areaArr[1].second = 5;  // zyx: 101
        areaArr[2].second = 6;  // zyx: 110

        memset(arr, false, sizeof(arr));
        sort(areaArr + 0, areaArr + 3);

        if (areaArr[2].first > areaArr[0].first * areaArr[1].first)
        {
            cout << -1 << endl;
            continue;
        }

        for (int i = 0; i < areaArr[0].first; i++)
        {
            arr[i][i] = true;
        }
        for (int i = areaArr[0].first; i < areaArr[1].first; i++)
        {
            arr[areaArr[0].first - 1][i] = true;
        }

        int upperNum = areaArr[1].first;
        for (int i = 0; i < areaArr[0].first && upperNum < areaArr[2].first; i++)
        {
            for (int j = 0; j < areaArr[1].first && upperNum < areaArr[2].first; j++)
            {
                if (!arr[i][j])
                {
                    arr[i][j] = true;
                    upperNum++;
                }
            }
        }

        cout << upperNum << endl;
        for (int i = 0; i < areaArr[0].first; i++)  // Oxz
        {
            for (int j = 0; j < areaArr[1].first; j++)  // Oyz
            {
                if (arr[i][j])
                {
                    pair<int, int> cntArr[3];                    

                    cntArr[0] = make_pair(areaArr[0].second - (areaArr[0].second & areaArr[1].second), i);
                    cntArr[1] = make_pair(areaArr[1].second - (areaArr[0].second & areaArr[1].second), j);
                    cntArr[2] = make_pair(areaArr[0].second & areaArr[1].second, 0);

                    sort(cntArr + 0, cntArr + 3);
                    for (int k = 0; k < 3; k++)
                    {
                        cout << cntArr[k].second;
                        if (k < 2)
                            cout << " ";
                        else
                            cout << endl;
                    }
                }
            }
        }
    }

    return 0;
}