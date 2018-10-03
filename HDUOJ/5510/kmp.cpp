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

#define SIZE 2010

string arr[SIZE];
int nextArr[SIZE];

void initNext(string & str)
{
    nextArr[0] = 0;
    for (int i = 1, matchNum = 0; i < (int)str.size(); i++)
    {
        while (matchNum > 0 && str[i] != str[matchNum]) // (matchNum + 1) - 1
            matchNum = nextArr[matchNum - 1];
        if (str[i] == str[matchNum])
            matchNum++;
        nextArr[i] = matchNum;
    }
}

bool kmp(string & origStr, string & matchStr)
{
    for (int i = 0, matchNum = 0; i < (int)origStr.size(); i++)
    {
        while (matchNum > 0 && (matchNum== (int)matchStr.size() || origStr[i] != matchStr[matchNum]))
            matchNum = nextArr[matchNum - 1];
        if (origStr[i] == matchStr[matchNum])
            matchNum++;
        if (matchNum == (int)matchStr.size())
            return true;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int num;
        cin >> num;
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i];
        }
        
        int ans = -1; 
        int fstPt = 0, sndPt = 1;
        initNext(arr[fstPt]);
        while (sndPt < num)
        {
            if (kmp(arr[sndPt], arr[fstPt]))
            {
                fstPt++;
                initNext(arr[fstPt]);
                if (fstPt == sndPt)
                    sndPt++;
            }
            else
            {
                ans = sndPt + 1;
                sndPt++;
            }
        }

        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}
