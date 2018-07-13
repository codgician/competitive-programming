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

#define SIZE 100100

typedef struct _Node
{
    int minVal, maxVal;
} Node;

Node arr[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        int fst, snd;
        cin >> fst >> snd;
        arr[i].minVal = min(fst, snd);
        arr[i].maxVal = max(fst, snd);
    }

    bool ans = true;
    int cntLim = arr[0].maxVal;
    for (int i = 1; i < num; i++)
    {
        if (arr[i].maxVal <= cntLim)
            cntLim = arr[i].maxVal;
        else if (arr[i].minVal <= cntLim)
            cntLim = arr[i].minVal;
        else
        {
            ans = false;
            break;
        }
    }

    if (ans)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}