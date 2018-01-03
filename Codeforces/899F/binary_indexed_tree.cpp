#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <queue>
#include <vector>
#include <set>
#define SIZE 200001
using namespace std;

set<int> pos[233]; // Record position of each char
string str;
int bit[SIZE]; // Use BIT to maintain prefix sum
int len;

int getLowBit(int n)
{
    return n & (-n);
}

void add(int x, int val)
{
    while (x <= len)
    {
        bit[x] += val;
        x += getLowBit(x);
    }
}

int getSum(int x)
{
    int ans = 0;
    while (x)
    {
        ans += bit[x];
        x -= getLowBit(x);
    }
    return ans;
}

int binarySearch(int x)
{
    int leftPt = 1, rightPt = len;
    int midPt = (leftPt + rightPt) >> 1;
    while (leftPt < rightPt)
    {
        int midSum = getSum(midPt);

        // Find the first that equals
        if (midSum >= x)
            rightPt = midPt;
        else
            leftPt = midPt + 1;
        midPt = (leftPt + rightPt) >> 1;
    }
    return midPt;
}

int main()
{
    ios::sync_with_stdio(false);
    int oprNum;
    cin >> len >> oprNum;
    cin >> str;
    for (int i = 1; i <= len; i++)
    {
        add(i, 1);
        pos[str[i - 1]].insert(i);
    }
    while (oprNum--)
    {
        int leftPt, rightPt;
        char ch;
        cin >> leftPt >> rightPt >> ch;

        // Get real position in original string
        leftPt = binarySearch(leftPt);
        rightPt = binarySearch(rightPt);

        // Erase ch in given period and update prefix sum
        set<int>::iterator posIt = pos[ch].lower_bound(leftPt);
        while (*posIt <= rightPt && posIt != pos[ch].end())
        {
            add(*posIt, -1);
            pos[ch].erase(posIt++);
            /* Can't write this way:
                pos[ch].erase(posIt);
                posIt++;
            Since posIt becomes a wild pointer after erasing it,
            posIt++ will lead to undefined behavior.
            */
        }
    }
    for (int i = 1; i <= len; i++)
    {
        if (getSum(i) - getSum(i - 1))
            cout << str[i - 1];
    }
    cout << endl;
    return 0;
}
