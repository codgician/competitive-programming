#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#define SIZE 10
using namespace std;

int arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    string origNum, maxNum;
    cin >> origNum >> maxNum;

    memset(arr, 0, sizeof(arr));
    for (int i = 0; i < origNum.length(); i++)
    {
        arr[origNum[i] - '0']++;
    }

    /*
    if (origNum.length() > maxNum.length())
    {
        int delta = origNum.length() - maxNum.length();
        string tmp = "";
        while (delta--)
        {
            tmp += '0';
        }
        maxNum = tmp + maxNum;
    }
    */

    if (maxNum.length() == origNum.length())
    {
        for (int i = 0; i < origNum.length(); i++)
        {
            if (arr[maxNum[i] - '0'] > 0)
            {
                arr[maxNum[i] - '0']--;

                string tmp = "";
                for (int j = 0; j <= 9; j++)
                {
                    for (int k = 0; k < arr[j]; k++)
                    {
                        tmp += (char)(j + '0');
                    }
                }

                bool canSelect = true;
                for (int j = i + 1; j < origNum.length(); j++)
                {
                    if (maxNum[j] > tmp[j - i - 1])
                    {
                        canSelect = true;
                        break;
                    }
                    else if (maxNum[j] < tmp[j - i - 1])
                    {
                        canSelect = false;
                        break;
                    }
                }

                if (canSelect)
                {
                    cout << maxNum[i];
                    continue;
                }
                else
                {
                    arr[maxNum[i] - '0']++;
                }
            }

            bool quitFlag = false;
            for (int j = maxNum[i] - '0' - 1; j >= 0; j--)
            {
                if (arr[j] > 0)
                {
                    cout << j;
                    arr[j]--;
                    quitFlag = true;
                    break;
                }
            }
            if (quitFlag)
                break;
        }
    }

    for (int i = 9; i >= 0; i--)
    {
        while (arr[i])
        {
            cout << i;
            arr[i]--;
        }
    }

    cout << endl;
    return 0;
}
