#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <map>
#define SIZE 200010
using namespace std;

queue<int> q[SIZE];
int tmpAns[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    string str;
    cin >> str;
    int cnt = 0, oneNum = 0, zeroNum = 0;
    int arrPt = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (i > 0 && str[i] != str[i - 1])
        {
            arrPt++;
        }
        if (str[i] == '0')
        {
            zeroNum++;
            cnt++;
        }
        else
        {
            if (cnt == 0)
            {
                cout << -1 << endl;
                return 0;
            }
            oneNum++;
            cnt--;
        }
        q[arrPt].push(i);
    }
    arrPt++;
    cnt = 0;
    for (int i = str.length() - 1; i >= 0; i--)
    {
        if (str[i] == '0')
        {
            cnt++;
        }
        else
        {
            if (cnt == 0)
            {
                cout << -1 << endl;
                return 0;
            }
            cnt--;
        }
    }

    int num = zeroNum - oneNum;
    cout << num << endl;
    int fstNonEmpty = 0;
    while (oneNum > 0)
    {
        int tmpAnsPt = 0;
        bool flag = false;
        for (int i = fstNonEmpty; i < arrPt; i++)
        {
            while (q[i].empty() && i < arrPt)
                i += 2;
            if (!flag)
            {
                fstNonEmpty = i;
                flag = true;
            }
            if (i < arrPt)
            {
                tmpAns[tmpAnsPt] = q[i].front();
                if (str[tmpAns[tmpAnsPt]] == '1')
                    oneNum--;
                tmpAnsPt++;
                q[i].pop();
            }
        }

        cout << tmpAnsPt;
        for (int i = 0; i < tmpAnsPt; i++)
        {
            cout << " " << tmpAns[i] + 1;
        }
        cout << endl;
    }

    for (int i = 0; i < arrPt; i += 2)
    {
        while (!q[i].empty())
        {
            cout << 1 << " " << q[i].front() + 1 << endl;
            q[i].pop();
        }
    }
    return 0;
}
