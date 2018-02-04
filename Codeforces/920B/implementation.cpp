#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 6002
using namespace std;

typedef struct _Student
{
    int index;
    int entryTime;
    int leaveTime;
    int ans;
} student;

student q[SIZE];

bool cmpRule(student a, student b)
{
    return a.index < b.index;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        for (int i = 0; i < SIZE; i++)
        {
            q[i].index = SIZE;
        }

        int stuNum;
        cin >> stuNum;
        for (int i = 0; i < stuNum; i++)
        {
            int entryTime, leaveTime;
            cin >> entryTime >> leaveTime;

            int cnt = entryTime;
            while (q[cnt].index != SIZE)
            {
                cnt++;
            }
            q[cnt].entryTime = entryTime;
            q[cnt].leaveTime = leaveTime;
            q[cnt].index = i;
        }

        int delta = 0;
        for (int i = 0; i < SIZE; i++)
        {
            if (q[i].index != SIZE)
            {
                if (q[i].leaveTime < i - delta)
                {
                    q[i].ans = 0;
                    delta++;
                }
                else
                {
                    if (q[i].entryTime > i - delta)
                    {
                        q[i].ans = q[i].entryTime;
                        delta = i - q[i].entryTime;
                    }
                    else
                    {
                        q[i].ans = i - delta;
                    }
                }
            }
            else
            {
                if (delta)
                    delta--;
            }
        }

        sort(q + 0, q + SIZE, cmpRule);

        for (int i = 0; i < stuNum; i++)
        {
            cout << q[i].ans;
            if (i < stuNum - 1)
                cout << " ";
            else
                cout << endl;
        }
    }
    return 0;
}
