#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#define SIZE 200010
using namespace std;

typedef struct _Node
{
    char type;
    long long int cord;
} Node;

Node arr[SIZE];

bool cmpRule(Node &a, Node &b)
{
    return a.cord < b.cord;
}

int main()
{
    ios::sync_with_stdio(false);
    int nodeNum;
    cin >> nodeNum;
    for (int i = 0; i < nodeNum; i++)
        cin >> arr[i].cord >> arr[i].type;
    sort(arr + 0, arr + nodeNum, cmpRule);

    int fstRPt = -1, fstBPt = -1, fstPPt = -1, lstRPt = -1, lstBPt = -1;
    for (int i = 0; i < nodeNum; i++)
    {
        if (arr[i].type == 'P')
        {
            fstPPt = i;
            break;
        }
        else if (arr[i].type == 'R')
        {
            if (fstRPt == -1)
                fstRPt = i;
            lstRPt = i;
        }
        else if (arr[i].type == 'B')
        {
            if (fstBPt == -1)
                fstBPt = i;
            lstBPt = i;
        }
    }

    long long int ans = 0;
    if (fstPPt == -1)
    {
        ans = arr[lstRPt].cord - arr[fstRPt].cord + arr[lstBPt].cord - arr[fstBPt].cord;
        cout << ans << endl;
        return 0;
    }
    else
    {
        if (fstRPt > -1)
            ans += arr[fstPPt].cord - arr[fstRPt].cord;
        if (fstBPt > -1)
            ans += arr[fstPPt].cord - arr[fstBPt].cord;
    }

    int prevPPt = fstPPt, prevRPt = -1, prevBPt = -1;
    long long int maxRSegLen = -1, maxBSegLen = -1;

    for (int i = fstPPt + 1; i < nodeNum; i++)
    {
        if (arr[i].type == 'P')
        {
            long long int segLen = arr[i].cord - arr[prevPPt].cord;

            if (prevRPt == -1 && prevBPt == -1)
            {
                ans += segLen;
            }
            else
            {
                long long int ans2 = segLen;

                if (prevRPt > -1)
                {
                    maxRSegLen = max(maxRSegLen, arr[i].cord - arr[prevRPt].cord);
                    ans2 += segLen - maxRSegLen;
                }

                if (prevBPt > -1)
                {
                    maxBSegLen = max(maxBSegLen, arr[i].cord - arr[prevBPt].cord);
                    ans2 += segLen - maxBSegLen;
                }

                ans += min((segLen << 1), ans2);
            }

            prevPPt = i;
            prevRPt = -1;
            prevBPt = -1;
            maxRSegLen = -1;
            maxBSegLen = -1;
        }
        else if (arr[i].type == 'R')
        {
            if (prevRPt > -1)
                maxRSegLen = max(maxRSegLen, arr[i].cord - arr[prevRPt].cord);
            else
                maxRSegLen = max(maxRSegLen, arr[i].cord - arr[prevPPt].cord);
            prevRPt = i;
        }
        else if (arr[i].type == 'B')
        {
            if (prevBPt > -1)
                maxBSegLen = max(maxBSegLen, arr[i].cord - arr[prevBPt].cord);
            else
                maxBSegLen = max(maxBSegLen, arr[i].cord - arr[prevPPt].cord);
            prevBPt = i;
        }
    }

    if (prevRPt > prevPPt)
    {
        ans += arr[prevRPt].cord - arr[prevPPt].cord;
    }
    if (prevBPt > prevPPt)
    {
        ans += arr[prevBPt].cord - arr[prevPPt].cord;
    }

    cout << ans << endl;

    return 0;
}
