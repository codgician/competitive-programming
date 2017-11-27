#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <climits>
#define SIZE 100010
using namespace std;

typedef struct Node {
    long long int height;
    long long int startPos;
} rec;

rec arr[SIZE];

long long int arrPt = 0;

void push(long long int height, long long int startPos)
{
    arr[arrPt].height = height;
    arr[arrPt].startPos = startPos;
    arrPt++;
}

void pop()
{
    arrPt--;
}

rec getHead()
{
    return arr[arrPt - 1];
}

long long int getLength()
{
    return arrPt;
}

long long int getMax(long long int a, long long int b)
{
    return a > b ? a : b;
}

int main()
{
    ios::sync_with_stdio(false);
    long long int recNum;
    while (cin >> recNum)
    {
        if (recNum == 0)
            break;

        long long int ans = 0;
        arrPt = 0;
        // Refrain from considering empty stack situation.
        push(-1, 0);

        for (long long int i = 0; i < recNum; i++)
        {
            long long int height;
            cin >> height;

            int startPos = i;

            while (getHead().height > height)
            {
                ans = getMax(ans, (i - getHead().startPos) * getHead().height);
                startPos = getHead().startPos;
                pop();
            }

            push(height, startPos);

        }

        while (getLength() > 1)
        {
            ans = getMax(ans, (recNum - getHead().startPos) * getHead().height);
            pop();
        }

        cout << ans << endl;
    }
    return 0;
}
