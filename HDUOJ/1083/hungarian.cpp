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
#define COURSE_SIZE 101
#define STU_SIZE 301
using namespace std;

bool arr[COURSE_SIZE][STU_SIZE], hasTried[STU_SIZE];
int stuMatch[STU_SIZE];
int stuNum, courseNum;

bool canFind(int courseId)
{
    for (int i = 0; i < stuNum; i++)
    {
        if (arr[courseId][i] && !hasTried[i])
        {
            hasTried[i] = true;
            if (stuMatch[i] == -1 || canFind(stuMatch[i]))
            {
                stuMatch[i] = courseId;
                return true;
            }
        }
    }
    return false;
}

bool hungarain()
{
    memset(stuMatch, -1, sizeof(stuMatch));
    int ans = 0;
    for (int i = 0; i < courseNum; i++)
    {
        memset(hasTried, false, sizeof(hasTried));
        if (canFind(i))
            ans++;
    }

    if (ans == courseNum)
        return true;
    else
        return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(arr, false, sizeof(arr));
        cin >> courseNum >> stuNum;
        for (int i = 0; i < courseNum; i++)
        {
            int cntStuNum;
            cin >> cntStuNum;
            for (int j = 0; j < cntStuNum; j++)
            {
                int cntStu;
                cin >> cntStu;
                arr[i][--cntStu] = true;
            }
        }

        if (hungarain())
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
