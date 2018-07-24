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

#define SIZE 100010

int reqArr[SIZE];
int ansArr[SIZE];

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        int len, reqNum;
        scanf("%d%d", &len, &reqNum);
        for (int i = 0; i < len; i++)
            reqArr[i] = i;
        for (int i = 0; i < reqNum; i++)
        {
            int leftPt, rightPt;
            scanf("%d%d", &leftPt, &rightPt);
            leftPt--;
            rightPt--;
            reqArr[leftPt] = max(reqArr[leftPt], rightPt); 
        }

        set<int> st;
        for (int i = 1; i <= len; i++)
            st.insert(i);

        int cntLeft = 0, cntRight = -1;
        for (int i = 0; i < len; i++)
        {
            if (reqArr[i] <= cntRight)
                continue;
            while (cntLeft < i)
            {
                st.insert(ansArr[cntLeft]);
                cntLeft++;
            }
            while (cntRight < reqArr[i])
            {
                ansArr[++cntRight] = *st.begin();
                st.erase(st.begin());
            }
        }

        for (int i = 0; i < len; i++)
        {
            printf("%d", ansArr[i]);
            if (i < len - 1)
                putchar(' ');
            else
                putchar('\n');
        }
    }
    return 0;
}