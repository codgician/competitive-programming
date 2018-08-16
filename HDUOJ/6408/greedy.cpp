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

#define SIZE 50010

typedef struct _Month
{
    int matPrice, manuPrice;
    int storMatPrice, storComPrice, storComNum;
    int manuNum, demand;
    int minMatPrice;
} Month;

Month arr[SIZE];

map<int, int> mp;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int monthNum;
        cin >> monthNum;
        for (int i = 0; i < monthNum; i++)
        {
            cin >> arr[i].matPrice >> arr[i].demand >> arr[i].manuPrice >> arr[i].manuNum;
        }
        for (int i = 0; i < monthNum - 1; i++)
        {
            cin >> arr[i].storComNum >> arr[i].storMatPrice >> arr[i].storComPrice;
        }

        if (arr[0].demand > arr[0].manuNum)
        {
            cout << -1 << endl;
            continue;
        }

        // Initialize minimum raw material price for each month
        arr[0].minMatPrice = arr[0].matPrice;
        for (int i = 1; i < monthNum; i++)
        {
            arr[i].minMatPrice = min(arr[i].matPrice, arr[i - 1].minMatPrice + arr[i - 1].storMatPrice);
        }

        long long int ans = 0, incCost = 0;
        int storNum = 0;
        mp.clear();
        for (int i = 0; i < monthNum; i++)
        {
            // Manufacture computers
            int cntCost = arr[i].minMatPrice + arr[i].manuPrice - incCost;
            mp[cntCost] += arr[i].manuNum;
            storNum += arr[i].manuNum;

    
            if (storNum < arr[i].demand)
            {
                ans = -1;
                break;
            }

            // Satiisfy demand
            while (mp.size() > 0)
            {
                auto it = mp.begin();
                if (it -> second <= arr[i].demand)
                {
                    ans += it -> second * (it -> first + incCost);
                    storNum -= it -> second;
                    arr[i].demand -= it -> second;
                    mp.erase(it);
                }
                else
                {
                    it -> second -= arr[i].demand;
                    ans += arr[i].demand * (it -> first + incCost);
                    storNum -= arr[i].demand;
                    arr[i].demand = 0;
                    break;
                }
            }

            // Satisfy storage upper limit
            if (storNum > arr[i].storComNum)
            {
                int abandonNum = storNum - arr[i].storComNum;
                while (mp.size() > 0)
                {
                    auto it = prev(mp.end());
                    if (it -> second <= abandonNum)
                    {
                        abandonNum -= it -> second;
                        storNum -= it -> second;
                        mp.erase(it);
                    }
                    else
                    {
                        storNum -= abandonNum;
                        it -> second -= abandonNum;
                        abandonNum = 0;
                        break;
                    }
                }
            }

            incCost += arr[i].storComPrice;
        }

        cout << ans << endl;
    }
    return 0;
}