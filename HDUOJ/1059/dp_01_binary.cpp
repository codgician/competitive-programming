#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 9999999
using namespace std;

int arr[SIZE], dp[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum = 1;
    while (true)
    {
        int arrPt = 0, valSum = 0;
        for (int i = 1; i <= 6; i++)
        {
            int num;
            cin >> num;
            valSum += num * i;

            if (num > 0)
            {
                int tmp = 0, sum = 0;
                while (sum + (1 << tmp) < num)
                {
                    arr[arrPt] = (i << tmp);
                    arrPt++;
                    sum += (1 << tmp);
                    tmp++;
                }
                if (num > sum)
                {
                    arr[arrPt] = i * (num - sum);
                    arrPt++;
                }
            }
        }

        if (valSum == 0)
            break;

        cout << "Collection #" << caseNum << ":" << endl;
        if (valSum & 1 > 0)
        {
            cout << "Can't be divided." << endl;
        }
        else
        {
            int bagSize = valSum / 2;
            for (int i = 0; i <= bagSize; i++)
                dp[i] = 0;
            for (int i = 0; i < arrPt; i++)
            {
                for (int j = bagSize; j >= arr[i]; j--)
                {
                    dp[j] = max(dp[j], dp[j - arr[i]] + arr[i]);
                }
            }
            if (dp[bagSize] == bagSize)
            {
                cout << "Can be divided." << endl;
            }
            else
            {
                cout << "Can't be divided." << endl;
            }
        }
        cout << endl;
        caseNum++;
    }
    return 0;
}
