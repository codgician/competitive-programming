#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define STU_SIZE 151
#define UNI_SIZE 51
using namespace std;

typedef struct _Student
{
    int region;
    int score;
    int prefNum;
} Student;

typedef struct _RegInfo
{
    int stuId;
    int uniId;

    _RegInfo(int pStuId, int pUniId)
    {
        stuId = pStuId;
        uniId = pUniId;
    }
} RegInfo;

typedef struct _University
{
    int region;
    int capacity;
    priority_queue<RegInfo> pq;
} University;

Student stu[STU_SIZE];
University uni[UNI_SIZE];
int stuPrefOrder[STU_SIZE][UNI_SIZE], stuMatch[STU_SIZE];
bool hasProposed[STU_SIZE][UNI_SIZE];

queue<int> q;

bool operator < (const RegInfo &a, const RegInfo &b)
{
    if (stu[a.stuId].region != stu[b.stuId].region)
    {
        if (stu[a.stuId].region == uni[a.uniId].region)
        {
            return 10 * stu[a.stuId].score > 7 * stu[b.stuId].score;
        }
        if (stu[b.stuId].region == uni[a.uniId].region)
        {
            return 7 * stu[a.stuId].score > 10 * stu[b.stuId].score;
        }
    }
    return stu[a.stuId].score > stu[b.stuId].score;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(hasProposed, false, sizeof(hasProposed));
        memset(stuMatch, -1, sizeof(stuMatch));
        int stuNum, uniNum;
        cin >> stuNum >> uniNum;
        for (int i = 0; i < stuNum; i++)
        {
            cin >> stu[i].region >> stu[i].score >> stu[i].prefNum;
            for (int j = 0; j < stu[i].prefNum; j++)
            {
                cin >> stuPrefOrder[i][j];
                stuPrefOrder[i][j]--;
            }
            q.push(i);
        }
        for (int i = 0; i < uniNum; i++)
        {
            cin >> uni[i].region >> uni[i].capacity;
            while (!uni[i].pq.empty())
                uni[i].pq.pop();
        }

        while (!q.empty())
        {
            int cntStuId = q.front();
            q.pop();

            for (int i = 0; i < stu[cntStuId].prefNum; i++)
            {
                int cntUniId = stuPrefOrder[cntStuId][i];
                if (hasProposed[cntStuId][cntUniId])
                    continue;
                hasProposed[cntStuId][cntUniId] = true;

                if (uni[cntUniId].pq.size() < uni[cntUniId].capacity)
                {
                    RegInfo cntRegInfo(cntStuId, cntUniId);
                    uni[cntUniId].pq.push(cntRegInfo);
                    stuMatch[cntStuId] = cntUniId;
                    break;
                }
                else
                {
                    RegInfo cntRegInfo(cntStuId, cntUniId);
                    uni[cntUniId].pq.push(cntRegInfo);
                    int popStuId = uni[cntUniId].pq.top().stuId;
                    uni[cntUniId].pq.pop();
                    if (popStuId == cntStuId)
                        continue;

                    q.push(popStuId);
                    stuMatch[popStuId] = -1;
                    stuMatch[cntStuId] = cntUniId;
                    break;
                }
            }
        }

        for (int i = 0; i < stuNum; i++)
        {
            if (stuMatch[i] == -1)
                cout << "not accepted" << endl;
            else
                cout << stuMatch[i] + 1 << endl;
        }
        cout << endl;
    }
    return 0;
}
