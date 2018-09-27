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
#include <cassert>
using namespace std;

#define SIZE 50010
#define BLOCK_SIZE 240

const long long int mod = 1e9 + 7;

int arr[SIZE], valArr[SIZE], tmpNum[SIZE];
long long int blockAns[BLOCK_SIZE][BLOCK_SIZE], sfxNum[BLOCK_SIZE][SIZE];

long long int quickPow(long long int a, long long int n)
{
    long long int ans = 1;
    a %= mod;
    while (n > 0)
    {
        if (n & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
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
        int len, qNum;
        cin >> len >> qNum;

        map<int, int> dscMp;

        int blockSize = sqrt(len);
        for (int i = 0; i < len; i++)
        {
            cin >> arr[i];
            dscMp[arr[i]] = -1;
        }

        int dscPt = 0;
        for (auto it = dscMp.begin(); it != dscMp.end(); ++it)
        {
            it -> second = dscPt;
            valArr[dscPt] = it -> first;
            dscPt++;
        }

        for (int i = 0; i < len; i++)
        {
            arr[i] = dscMp[arr[i]];
        }

        memset(sfxNum, 0, sizeof(sfxNum));
        for (int i = 0; i < len; i += blockSize)
        {
            int blockPt = i / blockSize;
            for (int j = i; j < len; j++)
            {
                if (j % blockSize == 0)
                {
                    if (j / blockSize == 0)
                        blockAns[blockPt][j / blockSize] = 0;
                    else
                        blockAns[blockPt][j / blockSize] = blockAns[blockPt][j / blockSize - 1]; 
                }

                if (sfxNum[blockPt][arr[j]] == 0)
                {
                    blockAns[blockPt][j / blockSize] += valArr[arr[j]];
                    blockAns[blockPt][j / blockSize] %= mod;
                }
                else
                {
                    blockAns[blockPt][j / blockSize] += quickPow(valArr[arr[j]], sfxNum[blockPt][arr[j]]) * (valArr[arr[j]] - 1) % mod;
                    blockAns[blockPt][j / blockSize] %= mod;
                }

                sfxNum[blockPt][arr[j]]++;
            }
        }

        int lastAns = 0;
        while (qNum--)
        {
            int qLeftPt, qRightPt;
            cin >> qLeftPt >> qRightPt;

            qLeftPt = (qLeftPt ^ lastAns) % len;
            qRightPt = (qRightPt ^ lastAns) % len;
            if (qLeftPt > qRightPt)
                swap(qLeftPt, qRightPt);

            int leftPt = qLeftPt / blockSize + (qLeftPt % blockSize > 0);
            int rightPt = qRightPt / blockSize - ((qRightPt + 1) % blockSize > 0);

            long long int ans = 0;

            if (leftPt > rightPt)
            {
                for (int i = qLeftPt; i <= qRightPt; i++)
                    tmpNum[arr[i]] = 0;
                for (int i = qLeftPt; i <= qRightPt; i++)
                {
                    if (tmpNum[arr[i]] == 0)
                        ans += valArr[arr[i]];
                    else
                        ans += quickPow(valArr[arr[i]], tmpNum[arr[i]]) * (valArr[arr[i]] - 1) % mod;
                    ans %= mod;
                    tmpNum[arr[i]]++;
                }
            }
            else
            {
                ans = blockAns[leftPt][rightPt];

                for (int i = qLeftPt; i < blockSize * leftPt; i++)
                    tmpNum[arr[i]] = sfxNum[leftPt][arr[i]] - sfxNum[rightPt + 1][arr[i]];
                for (int i = blockSize * (rightPt + 1); i <= qRightPt; i++)
                    tmpNum[arr[i]] = sfxNum[leftPt][arr[i]] - sfxNum[rightPt + 1][arr[i]];

                // Left
                for (int i = qLeftPt; i < blockSize * leftPt; i++)
                {
                    if (tmpNum[arr[i]] == 0)
                        ans += valArr[arr[i]];
                    else
                        ans += quickPow(valArr[arr[i]], tmpNum[arr[i]]) * (valArr[arr[i]] - 1) % mod;
                    ans %= mod;
                    tmpNum[arr[i]]++;
                }
                // Right
                for (int i = blockSize * (rightPt + 1); i <= qRightPt; i++)
                {
                    if (tmpNum[arr[i]] == 0)
                        ans += valArr[arr[i]];
                    else
                        ans += quickPow(valArr[arr[i]], tmpNum[arr[i]]) * (valArr[arr[i]] - 1) % mod;
                    ans %= mod;
                    tmpNum[arr[i]]++;
                }
            }

            cout << ans << endl;
            lastAns = ans;
        }
    }

    return 0;
}