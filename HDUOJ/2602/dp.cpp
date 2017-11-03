#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define SIZE 1005
using namespace std;

typedef struct Node {
    int value;
    int volume;
} bone;

bone arr[SIZE];
int dp[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        int boneNum, bagVolume;
        cin >> boneNum >> bagVolume;
        for (int i = 0; i < boneNum; i++)
        {
            cin >> arr[i].value;
        }
        int totVolume = 0;
        for (int i = 0; i < boneNum; i++)
        {
            cin >> arr[i].volume;
            totVolume += arr[i].volume;
        }

        for (int j = 0; j <= bagVolume; j++)
        {
            dp[j] = 0;
        }

        for (int i = 0; i < boneNum; i++)
        {
            for (int j = bagVolume; j >= max(arr[i].volume, bagVolume - totVolume); j--)
            {
                dp[j] = max(dp[j], dp[j - arr[i].volume] + arr[i].value);
            }
            totVolume -= arr[i].volume;
        }
        cout << dp[bagVolume] << endl;
    }
    return 0;
}
