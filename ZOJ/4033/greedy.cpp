#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define BAG_SIZE 1000100
#define ITEM_SIZE 100010
using namespace std;

bool sex[ITEM_SIZE];
bool ans[ITEM_SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int itemNum, gemSum = 0;
        cin >> itemNum;
        for (int i = 1; i <= itemNum; i++)
        {
            char ch;
            cin >> ch;
            if (ch == '0')
                sex[i] = false;
            else
                sex[i] = true;
            gemSum += i;
        }

        if (gemSum & 1)
        {
            cout << -1 << endl;
            continue;
        }

        int headPt = 1, tailPt = (itemNum & 1) ? itemNum - 1 : itemNum;

        while (headPt < tailPt)
        {
            ans[headPt] = headPt & 1;
            ans[tailPt] = ans[headPt];
            headPt++;
            tailPt--;
        }

        if (itemNum & 1)
            ans[itemNum] = 0;

        for (int i = 1; i <= itemNum; i++)
        {
            int cnt;
            if (!ans[i])
            {
                if (!sex[i])
                    cnt = 1;
                else
                    cnt = 3;
            }
            else
            {
                if (!sex[i])
                    cnt = 2;
                else
                    cnt = 4;
            }
            cout << cnt;
        }
        cout << endl;
    }
    
    return 0;
}