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
#define SIZE 10001
using namespace std;

long long int arr[SIZE];
int num, rowNum;

int xorGauss()
{
    int cntRow = 0;
    for (int i = 63; i >= 0; i--)
    {
        for (int j = cntRow; j < num; j++)
        {
            if (arr[j] & ((long long int)1 << i))
            {
                swap(arr[cntRow], arr[j]);
                for (int k = 0; k < num; k++)
                {
                    if (k == cntRow)
                        continue;
                    if (arr[k] & ((long long int)1 << i))
                    {
                        arr[k] ^= arr[cntRow];
                    }
                }
                cntRow++;
                break;
            }
        }
    }
    return cntRow;
}

long long int getKthSmallest(int k)
{
    // R(matrix) == 0
    if (rowNum < num)
    {
        if (k == 1)
            return 0;
        else
            k--;
    }

    if (k >= (long long int)1 << rowNum)
        return -1;
    long long int ans = 0;
    for (int i = 0; i <= 63 && i < rowNum; i++)
    {
        if (k & (long long int)1 << i)
        {
            ans ^= arr[rowNum - i - 1];
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        cin >> num;
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i];
        }

        rowNum = xorGauss();

        int queryNum;
        cin >> queryNum;
        cout << "Case #" << t << ":" << endl;
        while (queryNum--)
        {
            int k;
            cin >> k;
            cout << getKthSmallest(k) << endl;
        }
    }
    return 0;
}
