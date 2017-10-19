#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define SIZE 1001
using namespace std;

typedef struct Node {
    int value;
    int origNum;
} fuck;

fuck degree[SIZE];
bool matrix[SIZE][SIZE];

bool cmpRule(fuck a, fuck b)
{
    return a.value > b.value;
}

bool cmpRuleRevert(fuck a, fuck b)
{
    return a.origNum < b.origNum;
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
            for (int j = 0; j < nodeNum; j++)
                matrix[i][j] = false;
        for (int i = 0; i < nodeNum; i++)
        {
            cin >> degree[i].value;
            degree[i].origNum = i;
        }

        bool ans = true;
        int startPt = 0;
        while (startPt < nodeNum)
        {
            sort(degree + startPt, degree + nodeNum, cmpRule);
            if (degree[nodeNum - 1].value < 0)
            {
                ans = false;
                break;
            }
            startPt++;
            int rearEnd = startPt + degree[startPt - 1].value;
            if (rearEnd > nodeNum)
            {
                ans = false;
                break;
            }
            for (int i = startPt; i < rearEnd; i++)
            {
                degree[i].value--;
                matrix[degree[startPt - 1].origNum][degree[i].origNum] = true;
                matrix[degree[i].origNum][degree[startPt - 1].origNum] = true;
            }

        }
        if (ans)
        {
            cout << "YES" << endl;
            sort(degree, degree + nodeNum, cmpRuleRevert);
            for (int i = 0; i < nodeNum; i++)
            {
                for (int j = 0; j < nodeNum; j++)
                {
                    cout << matrix[i][j];
                    if (j < nodeNum - 1)
                        cout << " ";
                    else
                        cout << endl;
                }
            }
        }
        else
            cout << "NO" << endl;
        cout << endl;
    }
    return 0;
}
