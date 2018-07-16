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

#define SIZE 1000010

typedef struct _Node
{
    char ch;
    int num;
} Node;

Node arr[SIZE];
int arrPt;

void compress()
{
    int mergePt = 0;
    for (int i = 1; i < arrPt; i++)
    {
        if (arr[i].num > 0)
        {
            if (arr[i].ch == arr[mergePt].ch)
                arr[mergePt].num += arr[i].num;
            else
            {
                if (arr[mergePt].num == 0)
                    arr[mergePt] = arr[i];
                else
                    arr[++mergePt] = arr[i];
            }
        }
    }
    arrPt = mergePt + 1;
}

int main()
{
    ios::sync_with_stdio(false);
    string str;
    cin >> str;

    arrPt = 0;
    arr[arrPt].ch = str[0];
    arr[arrPt].num = 1;
    for (int i = 1; i < (int)str.size(); i++)
    {
        if (str[i] == arr[arrPt].ch)
        {
            arr[arrPt].num++;
        }
        else
        {
            arr[++arrPt].ch = str[i];
            arr[arrPt].num = 1;
        }
    }
    arrPt++;

    int ans = 0;
    while (arrPt > 1)
    {
        ans++;
        arr[0].num--;
        arr[arrPt - 1].num--;
        for (int i = 1; i < arrPt - 1; i++)
            arr[i].num -= 2;
        compress();
    }
    cout << ans << endl;

    return 0;
}