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

#define SIZE 200010

typedef struct _Node
{
    long long int price;
    int id;

    bool operator < (const struct _Node & snd) const
    {
        if (price == snd.price)
            return id < snd.id;
        return price < snd.price;
    }
} Node;

Node heapArr[SIZE];
long long int arr[SIZE], pfxSum;
bool delArr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    memset(delArr, false, sizeof(delArr));

    int num;
    long long int money, minVal = LLONG_MAX;
    cin >> num >> money;

    pfxSum = 0;
    for (int i = 1; i <= num; i++)
    {
        cin >> arr[i];
        pfxSum += arr[i];
        heapArr[i] = {arr[i], i};
        minVal = min(minVal, arr[i]);
    }

    sort(heapArr + 1, heapArr + num + 1);

    long long int ans = 0, cntNum = num;
    long long int cntSum = pfxSum;
    while (money > 0)
    {
        int pos = upper_bound(heapArr + 1, heapArr + num + 1, Node{money, INT_MAX}) - heapArr;
        for (int i = pos; i <= num && delArr[heapArr[i].id] == false; i++)
        {
            delArr[heapArr[i].id] = true;
            cntSum -= heapArr[i].price;
            cntNum--;
        }

        if (cntSum == 0)
            break;

        if (money >= cntSum)
        {
            ans += cntNum * (money / cntSum);
            money = money % cntSum;
        }
        else
        {
            for (int i = 1; i <= num && money > 0; i++)
            {
                if (delArr[i])
                    continue;
                if (money >= arr[i])
                {
                    ans++;
                    money -= arr[i];
                }
            }

            if (money < minVal)
                break;
        }
    }

    cout << ans << endl;

    return 0;
}