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

#define SIZE 10010

typedef struct _Query
{
    int id;
    int qLeftPt, qRightPt;
} Query;

int arr[SIZE], posArr[SIZE];
long long int ans[SIZE]; 
Query qArr[SIZE];
int num;

vector<pair<int, int> > leftArr[SIZE], rightArr[SIZE];

void init()
{
    for (int i = 0; i < num; i++)
    {
        int cnt = arr[i];
        rightArr[i].push_back(make_pair(cnt, i));
        if (i == 0)
            continue;
        for (int j = 0; j < (int)rightArr[i - 1].size(); j++)
        {
            cnt = __gcd(cnt, rightArr[i - 1][j].first);
            if (cnt != rightArr[i].back().first)
                rightArr[i].push_back(make_pair(cnt, rightArr[i - 1][j].second));
            else
                rightArr[i].back().second = rightArr[i - 1][j].second;
        }
    }

    for (int i = num - 1; i >= 0; i--)
    {
        int cnt = arr[i];
        leftArr[i].push_back(make_pair(cnt, i));
        if (i == num - 1)
            continue;
        for (int j = 0; j < (int)leftArr[i + 1].size(); j++)
        {
            cnt = __gcd(cnt, leftArr[i + 1][j].first);
            if (cnt != leftArr[i].back().first)
                leftArr[i].push_back(make_pair(cnt, leftArr[i + 1][j].second));
            else
                leftArr[i].back().second = leftArr[i + 1][j].second;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> num;
        int blockSize = sqrt(num);
        for (int i = 0; i < num; i++)
        {
            cin >> arr[i];
            posArr[i] = i / blockSize;
            leftArr[i].clear();
            rightArr[i].clear();
        }

        init();

        int qNum;
        cin >> qNum;
        for (int i = 0; i < qNum; i++)
        {
            cin >> qArr[i].qLeftPt >> qArr[i].qRightPt;
            qArr[i].qLeftPt--;
            qArr[i].qRightPt--;
            qArr[i].id = i;
        }

        sort(qArr + 0, qArr + qNum, [](Query & fst, Query & snd){
            if (posArr[fst.qLeftPt] == posArr[snd.qLeftPt])
                return fst.qRightPt < snd.qRightPt;
            return posArr[fst.qLeftPt] < posArr[snd.qLeftPt];
        });

        int cntLeftPt = 0, cntRightPt = 0;
        long long int cntAns = arr[0];
        for (int i = 0; i < qNum; i++)
        {
            while (qArr[i].qLeftPt < cntLeftPt)
            {
                // Add left
                cntLeftPt--;
                int cntPt = cntLeftPt;
                for (auto it = leftArr[cntLeftPt].begin(); it != leftArr[cntLeftPt].end(); ++it)
                {
                    int cntGcd = it -> first;
                    int rightMostPt = min(it -> second, cntRightPt);
                    cntAns += (long long int)cntGcd * (rightMostPt - cntPt + 1);
                    cntPt = rightMostPt + 1;
                    if (cntPt > cntRightPt)
                        break;
                }
            }

            while (qArr[i].qRightPt > cntRightPt)
            {
                // Add right
                cntRightPt++;
                int cntPt = cntRightPt;
                for (auto it = rightArr[cntRightPt].begin(); it != rightArr[cntRightPt].end(); ++it)
                {
                    int cntGcd = it -> first;
                    int leftMostPt = max(it -> second, cntLeftPt);
                    cntAns += (long long int)cntGcd * (cntPt - leftMostPt + 1);
                    cntPt = leftMostPt - 1;
                    if (cntPt < cntLeftPt)
                        break;
                }
            }

            while (qArr[i].qLeftPt > cntLeftPt)
            {
                // Delete left
                int cntPt = cntLeftPt;
                for (auto it = leftArr[cntLeftPt].begin(); it != leftArr[cntLeftPt].end(); ++it)
                {
                    int cntGcd = it -> first;
                    int rightMostPt = min(it -> second, cntRightPt);
                    cntAns -= (long long int)cntGcd * (rightMostPt - cntPt + 1);
                    cntPt = rightMostPt + 1;
                    if (cntPt > cntRightPt)
                        break;
                }
                cntLeftPt++;
            }

            while (qArr[i].qRightPt < cntRightPt)
            {
                // Delete right
                int cntPt = cntRightPt;
                for (auto it = rightArr[cntRightPt].begin(); it != rightArr[cntRightPt].end(); ++it)
                {
                    int cntGcd = it -> first;
                    int leftMostPt = max(it -> second, cntLeftPt);
                    cntAns -= (long long int)cntGcd * (cntPt - leftMostPt + 1);
                    cntPt = leftMostPt - 1;
                    if (cntPt < cntLeftPt)
                        break;
                }
                cntRightPt--;
            }

            ans[qArr[i].id] = cntAns;
        }

        for (int i = 0; i < qNum; i++)
            cout << ans[i] << endl;
    }
    return 0;
}