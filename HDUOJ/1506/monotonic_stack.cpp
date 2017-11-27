#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <climits>
#define SIZE 100010
using namespace std;

typedef struct Node {
    int height;
    int startPos;
} rec;

rec arr[SIZE];

int arrPt = 0;

void push(int height, int startPos)
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

int getLength()
{
    return arrPt;
}

int main()
{
    ios::sync_with_stdio(false);
    int recNum;
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
            int height;
            cin >> height;

            int startPos = i;

            while (getHead().height > height)
            {
                ans = max(ans, (long long int)(i - getHead().startPos) * getHead().height);
                startPos = getHead().startPos;
                pop();
            }

            push(height, startPos);

        }

        while (getLength() > 1)
        {
            ans = max(ans, (long long int)(recNum - getHead().startPos) * getHead().height);
            pop();
        }

        cout << ans << endl;
    }
    return 0;
}
