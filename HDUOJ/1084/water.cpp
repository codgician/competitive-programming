#include <iostream>
#include <cstdio>
#include <algorithm>
#define SIZE 200
using namespace std;

typedef struct Node {
    int solved;
    int position;
    long long int time;
} hath;

hath arr[SIZE];
int ans[SIZE];
int score[6] = {50, 60, 70, 80, 90, 100};

bool cmpRule(hath a, hath b)
{
    if (a.solved == b.solved)
        return a.time < b.time;
    else
        return a.solved > b.solved;
}

int main()
{
    ios::sync_with_stdio(false);
    int stuNum;
    while (cin >> stuNum)
    {
        if (stuNum < 0)
            break;
        for (int i = 0; i < stuNum; i++)
        {
            int hour, minute, second;
            scanf("%d %d:%d:%d", &arr[i].solved, &hour, &minute, &second);
            arr[i].time = 3600 * hour + 60 * minute + second;
            arr[i].position = i;
        }
        sort(arr, arr + stuNum, cmpRule);
        int cntLevel = 5, cntNum = 0;
        for (int i = 0; i <= stuNum; i++)
        {
            if (i == stuNum || arr[i].solved < cntLevel)
            {
                if (cntLevel == 0 || cntLevel == 5)
                {
                    for (int j = i - cntNum; j < i; j++)
                        ans[arr[j].position] = score[cntLevel];
                }
                else
                {
                    int worseNum = 0;
                    if (cntNum > 1)
                        worseNum = (cntNum + 1) / 2;
                    for (int j = i - cntNum; j < i - worseNum; j++)
                    {
                        ans[arr[j].position] = score[cntLevel] + 5;
                    }

                    for (int j = i - worseNum; j < i; j++)
                    {
                        ans[arr[j].position] = score[cntLevel];
                    }
                }
                if (i < stuNum)
                {
                    cntLevel = arr[i].solved;
                    cntNum = 1;
                }
            }
            else
            {
                cntNum++;
            }
        }
        for (int i = 0; i < stuNum; i++)
            cout << ans[i] << endl;
        cout << endl;
    }
    return 0;
}
