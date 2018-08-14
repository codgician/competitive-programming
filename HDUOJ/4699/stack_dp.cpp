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

long long int suffixSum[SIZE];
long long int dp[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int qNum;
    while (cin >> qNum)
    {
        stack<int> leftStk, rightStk;
        suffixSum[0] = 0;
        dp[0] = INT_MIN;

        while (qNum--)
        {
            char opr;
            cin >> opr;
            if (opr == 'I')
            {
                // insert
                int val;
                cin >> val;
                leftStk.push(val);

                suffixSum[leftStk.size()] = suffixSum[leftStk.size() - 1] + val;
                dp[leftStk.size()] = max(dp[leftStk.size() - 1], suffixSum[leftStk.size()]);
            }
            else if (opr == 'D')
            {
                // delete
                if (leftStk.empty())
                    continue;

                leftStk.pop();
            }
            else if (opr == 'L')
            {
                // move left
                if (leftStk.empty())
                    continue;

                int cnt = leftStk.top();
                leftStk.pop();
                rightStk.push(cnt);
            }
            else if (opr == 'R')
            {
                // move right
                if (rightStk.empty())
                    continue;

                int cnt = rightStk.top();
                rightStk.pop();
                leftStk.push(cnt);

                suffixSum[leftStk.size()] = suffixSum[leftStk.size() - 1] + cnt;
                dp[leftStk.size()] = max(dp[leftStk.size() - 1], suffixSum[leftStk.size()]);
            }
            else if (opr == 'Q')
            {
                // query max prefix sum
                int pos;
                cin >> pos;
                cout << dp[pos] << endl;
            }
        }

    }
    return 0;
}