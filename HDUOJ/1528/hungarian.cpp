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
#include <set>
#include <map>
#define CARD_TYPE 4
#define SIZE 53
using namespace std;

bool hasTried[SIZE];
int adamCard[SIZE], eveCard[SIZE], adamMatch[SIZE];
int k;

int getType(char ch)
{
    switch (ch)
    {
        case 'H':
            return 3;
        case 'S':
            return 2;
        case 'D':
            return 1;
        case 'C':
            return 0;
    }
}

int getNum(char ch)
{
    if (ch >= '2' && ch <= '9')
        return ch - '2';
    else if (ch == 'T')
        return 8;
    else if (ch == 'J')
        return 9;
    else if (ch == 'Q')
        return 10;
    else if (ch == 'K')
        return 11;
    else if (ch == 'A')
        return 12;
}

int getId(char cardNum, char cardType)
{
    return getNum(cardNum) * CARD_TYPE + getType(cardType);
}

bool canFind(int eveId)
{
    for (int i = 0; i < k; i++)
    {
        if (eveCard[eveId] > adamCard[i] && !hasTried[i])
        {
            hasTried[i] = true;
            if (adamMatch[i] == -1 || canFind(adamMatch[i]))
            {
                adamMatch[i] = eveId;
                return true;
            }
        }
    }
    return false;
}

int hungarian()
{
    memset(adamMatch, -1, sizeof(adamMatch));
    int ans = 0;
    for (int i = 0; i < k; i++)
    {
        memset(hasTried, false, sizeof(hasTried));
        if (canFind(i))
            ans++;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> k;
        for (int i = 0; i < k; i++)
        {
            char cardNum, cardType;
            cin >> cardNum >> cardType;
            adamCard[i] = getId(cardNum, cardType);
        }
        for (int i = 0; i < k; i++)
        {
            char cardNum, cardType;
            cin >> cardNum >> cardType;
            eveCard[i] = getId(cardNum, cardType);
        }

        int ans = hungarian();
        cout << ans << endl;
    }
    return 0;
}
