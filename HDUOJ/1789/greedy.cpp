#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define SIZE 1001
using namespace std;

typedef struct Node {
    int deadline;
    int xuScore;
} hw;

hw arr[SIZE];
bool isAssigned[SIZE];

bool cmpRule(hw a, hw b)
{
    if (a.xuScore != b.xuScore)
        return a.xuScore > b.xuScore;
    else
        return a.deadline < b.deadline;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int i = 0; i < caseNum; i++)
    {
        int hwNum, xuScore = 0, maxDeadline = 0;
        cin >> hwNum;
        for (int i = 0; i < hwNum; i++)
        {
            isAssigned[i] = false;
            cin >> arr[i].deadline;
            if (arr[i].deadline > maxDeadline)
                maxDeadline = arr[i].deadline;
        }
        for (int i = 0; i < hwNum; i++)
            cin >> arr[i].xuScore;

        sort(arr, arr + hwNum, cmpRule);

        for (int i = 0; i < hwNum; i++)
        {
            // For every homework, assign it to a day which is as close to the deadline as possible.
            bool flag = false;
            for (int assignDay = arr[i].deadline - 1; assignDay >= 0; assignDay--)
                if (!isAssigned[assignDay])
                {
                    isAssigned[assignDay] = true;
                    flag = true;
                    break;
                }

            if (!flag)
                xuScore += arr[i].xuScore;
        }

        cout << xuScore << endl;
    }
    return 0;
}
