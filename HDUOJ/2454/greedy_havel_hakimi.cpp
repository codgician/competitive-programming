#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define SIZE 1001
using namespace std;

int degree[SIZE];

bool cmpRule(int a, int b)
{
    return a > b;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int nodeNum;
        cin >> nodeNum;
        for (int i = 0; i < nodeNum; i++)
            cin >> degree[i];

        bool ans = true;
        int startPt = 0;
        while (startPt < nodeNum)
        {
            sort(degree + startPt, degree + nodeNum, cmpRule);
            if (degree[nodeNum - 1] < 0)
            {
                ans = false;
                break;
            }
            startPt++;
            int rearEnd = startPt + degree[startPt - 1];
            if (rearEnd > nodeNum)
            {
                ans = false;
                break;
            }
            for (int i = startPt; i < rearEnd; i++)
                degree[i]--;
        }
        if (ans)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}
