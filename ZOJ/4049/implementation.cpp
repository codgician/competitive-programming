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

#define SIZE 10100

#define ADD 0
#define BEQ 1
#define BNE 2
#define BLT 3
#define BGT 4

typedef struct _Ins
{
	int opr;
	int val, k;
} Ins;

Ins arr[SIZE];

bool hasVisited[SIZE][300];

int main()
{
    int caseNum;
   	scanf("%d", &caseNum);
    while (caseNum--)
    {
    	int insNum;
    	scanf("%d", &insNum);
    	for (int i = 0; i < insNum; i++)
    	{
    		char buf[5];
    		scanf("%s %d", buf, &arr[i].val);

    		if (buf[0] == 'b')
    		{
    			scanf("%d", &arr[i].k);
    			arr[i].k--;
    			if (buf[1] == 'e')
    				arr[i].opr = BEQ;
    			else if (buf[1] == 'n')
    				arr[i].opr = BNE;
    			else if (buf[1] == 'l')
    				arr[i].opr = BLT;
    			else if (buf[1] == 'g')
    				arr[i].opr = BGT;
    		}
    		else
    		{
    			arr[i].opr = ADD;
    		}
    	}

    	memset(hasVisited, false, sizeof(hasVisited));
    	bool ans = true;
    	int cntPt = 0, reg = 0;
    	while (cntPt < insNum)
    	{
    		if (hasVisited[cntPt][reg])
    		{
    			ans = false;
    			break;
    		}
    		hasVisited[cntPt][reg] = true;

    		if (arr[cntPt].opr == ADD)
    		{
    			reg = (reg + arr[cntPt].val) % 256;
    			cntPt++;
    		}
    		else if (arr[cntPt].opr == BEQ)
    		{
    			if (reg == arr[cntPt].val)
    				cntPt = arr[cntPt].k;
    			else
    				cntPt++;
    		}
    		else if (arr[cntPt].opr == BNE)
    		{
    			if (reg != arr[cntPt].val)
    				cntPt = arr[cntPt].k;
    			else
    				cntPt++;
    		}
    		else if (arr[cntPt].opr == BLT)
    		{
    			if (reg < arr[cntPt].val)
    				cntPt = arr[cntPt].k;
    			else
    				cntPt++;
    		}
    		else if (arr[cntPt].opr == BGT)
    		{
    			if (reg > arr[cntPt].val)
    				cntPt = arr[cntPt].k;
    			else
    				cntPt++;
    		}
    	}

    	if (ans)
    		cout << "Yes" << endl;
    	else
    		cout << "No" << endl;
    }

    return 0;
}