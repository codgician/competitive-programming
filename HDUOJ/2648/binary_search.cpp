#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 10001
using namespace std;

typedef struct _Shop {
    string name;
    int price;
} shop;

shop arr[SIZE];

int cmpRule(shop a, shop b)
{
    return a.name < b.name;
}

void work(int leftPt, int rightPt, string name, int price)
{
    int midPt = (leftPt + rightPt) / 2;

    if (arr[midPt].name == name)
    {
        arr[midPt].price += price;
        return;
    }

    if (arr[midPt].name > name)
        return work(leftPt, midPt - 1, name, price);
    else
        return work(midPt + 1, rightPt, name, price);
}

int main()
{
    ios::sync_with_stdio(false);
    int shopNum;
    while (cin >> shopNum)
    {
        for (int i = 0; i < shopNum; i++)
        {
            cin >> arr[i].name;
            arr[i].price = 0;
        }

        sort(arr + 0, arr + shopNum, cmpRule);

        int dayNum, memoryPrice = 0;
        cin >> dayNum;
        for (int i = 0; i < dayNum; i++)
        {
            for (int j = 0; j < shopNum; j++)
            {
                int price;
                string name;
                cin >> price >> name;
                if (name == "memory")
                    memoryPrice += price;
                work(0, shopNum - 1, name, price);
            }

            int rankNum = 1;
            for (int j = 0; j < shopNum; j++)
            {
                if (arr[j].price > memoryPrice)
                    rankNum++;
            }
            cout << rankNum << endl;
        }
    }
    return 0;
}
