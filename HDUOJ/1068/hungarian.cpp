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
#define SIZE 501
using namespace std;

bool arr[SIZE][SIZE], hasTried[SIZE];
int partnerMatch[SIZE];
int stuNum;

bool canFind(int stuId)
{
    for (int i = 0; i < stuNum; i++)
    {
        if (arr[stuId][i] && !hasTried[i])
        {
            hasTried[i] = true;
            if (partnerMatch[i] == -1 || canFind(partnerMatch[i]))
            {
                partnerMatch[i] = stuId;
                return true;
            }
        }
    }
    return false;
}

int hungarian()
{
    memset(partnerMatch, -1, sizeof(partnerMatch));
    int ans = 0;
    for (int i = 0; i < stuNum; i++)
    {
        memset(hasTried, false ,sizeof(hasTried));
        if (canFind(i))
            ans++;
    }
    return ans;
}

int main()
{
    while (scanf("%d", &stuNum) != EOF)
    {
        memset(arr, false, sizeof(arr));
        for (int i = 0; i < stuNum; i++)
        {
            int stuId, relationNum;
            scanf("%d: (%d)", &stuId, &relationNum);
            for (int j = 0; j < relationNum; j++)
            {
                int partnerId;
                scanf("%d", &partnerId);
                arr[stuId][partnerId] = true;
            }
        }

        int ans = hungarian();
        printf("%d\n", stuNum - (ans >> 1));
    }
    return 0;
}

