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
#include <bitset>
#include <functional>
#include <iterator>
using namespace std;

#define SIZE 31

int arr[SIZE];

inline int getHighestOne(int n)
{
    int ret = 0;
    while (n > 1)
    {
        n <<= 1;
        ret++;
    }
    return ret;
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        memset(arr, 0, sizeof(arr));
    	int num;
    	scanf("%d", &num);

        int ans = 0;
        for (int i = 0; i < num; i++)
        {
            int cnt;
            scanf("%d", &cnt);
            int cat = getHighestOne(cnt);
            ans = max(ans, ++arr[cat]);
        }

    	printf("%d\n", ans);
    }
    return 0;
}