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
#include <set>
#include <map>
#include <stack>
#include <iterator>
#include <functional>
#define SIZE 200100
using namespace std;

char str[SIZE];
int nextArr[SIZE];

inline void initNext(char *str)
{
    nextArr[0] = 0;
    int strLen = strlen(str);
    for (register int i = 1, matchNum = 0; i < strLen; i++)
    {
        while (matchNum > 0 && str[i] != str[matchNum])
            matchNum = nextArr[matchNum - 1];
        if (str[i] == str[matchNum])
            matchNum++;
        nextArr[i] = matchNum;
    }
}

int main()
{
	int caseNum;
	scanf("%d", &caseNum);
	getchar();
	while (caseNum--)
	{
		gets(str);
		initNext(str);

		int strLen = strlen(str);
		int cycleLen = strLen - nextArr[strLen - 1];
		int ans = 0;

		if (cycleLen > 0 && (strLen % cycleLen > 0 || strLen / cycleLen < 2))
		{
			ans = cycleLen - strLen % cycleLen;
		}

		printf("%d\n", ans);
	}
	return 0;
}
