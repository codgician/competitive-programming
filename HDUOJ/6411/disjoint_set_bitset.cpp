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

#define SIZE 100100

const int mod = 1e9 + 7;

int parent[SIZE];
long long int valArr[SIZE];

int sccId[SIZE];
vector<int> sccVec[SIZE];

int bitSuffixSum[SIZE];

int vertexNum, edgeNum;
 
int getParent(int n)
{
    if (parent[n] == n)
        return n;
    else
    {
        parent[n] = getParent(parent[n]);
        return parent[n];
    }
}

void mergeNode(int fst, int snd)
{
    int fstParent = getParent(fst);
    int sndParent = getParent(snd);

    if (fstParent > sndParent)
        swap(fstParent, sndParent);

    if (fstParent != sndParent)
    {
        parent[sndParent] = fstParent;
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
        cin >> vertexNum >> edgeNum;
        for (int i = 0; i < vertexNum; i++)
        {
            parent[i] = i;
            cin >> valArr[i];
        }

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;

            if (from == to)
                continue;

            mergeNode(from, to);
        }

        int sccNum = 0;
        for (int i = 0; i < vertexNum; i++)
        {
            if (getParent(i) == i)
            {
                sccVec[sccNum].clear();
                sccId[i] = sccNum++;
            }
        }

        for (int i = 0; i < vertexNum; i++)
        {
            sccVec[sccId[getParent(i)]].push_back(i);
        }

        long long int ans = 0;
        for (int i = 0; i < sccNum; i++)
        {
            sort(sccVec[i].begin(), sccVec[i].end(), [](int fst, int snd) {
                return valArr[fst] > valArr[snd];
            });

            for (int k = 0; k < 31; k++)
            {
                bitSuffixSum[(int)sccVec[i].size()] = 0;
                for (int j = (int)sccVec[i].size() - 1; j >= 0; j--)
                {
                    bitSuffixSum[j] = bitSuffixSum[j + 1] + ((valArr[sccVec[i][j]] & (1 << k)) > 0 ? 1 : 0); 
                }

                for (int j = 0; j < (int)sccVec[i].size() - 1; j++)
                {
                    if (valArr[sccVec[i][j]] & (1 << k))
                    {
                        ans += (long long int)valArr[sccVec[i][j]] * (1ll << k) % mod * bitSuffixSum[j + 1] % mod;
                        if (ans >= mod)
                            ans %= mod;
                    }
                }
            }
        }

        cout << ans << endl;
    }
    return 0;
}