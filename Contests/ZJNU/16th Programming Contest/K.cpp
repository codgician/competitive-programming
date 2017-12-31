#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <queue>
#include <vector>
#define SIZE 100001
using namespace std;

typedef struct _Toy {
    int index;
    int value;
    int oprNum;

    bool operator < (const _Toy t) const
    {
        if (t.value == value)
            return t.oprNum < oprNum;
        else
            return t.value < value;
    }

} toy;

toy arr[SIZE];

bool cmpRule(toy a, toy b)
{
    return a.oprNum < b.oprNum;
}

int main()
{
    ios::sync_with_stdio(false);
    priority_queue<toy> pq;
    int boxSize, oprNum;
    cin >> boxSize >> oprNum;
    for (int i = 0; i < oprNum; i++)
    {
        string oprType;
        cin >> oprType;
        if (oprType == "Add")
        {
            toy cnt;
            cin >> cnt.index >> cnt.value;
            cnt.oprNum = i;
            // The new toy should never be abandoned!
            while (pq.size() == boxSize)
                pq.pop();
            pq.push(cnt);
        }
        else if (oprType == "Expand")
        {
            int delta;
            cin >> delta;
            boxSize += delta;
        }
    }

    int toyPt = 0;
    while (!pq.empty())
    {
        arr[toyPt++] = pq.top();
        pq.pop();
    }

    sort(arr + 0, arr + toyPt, cmpRule);
    for (int i = 0; i < toyPt; i++)
    {
        cout << arr[i].index;
        if (i < toyPt - 1)
            cout << " ";
        else
            cout << endl;
    }

    return 0;
}
