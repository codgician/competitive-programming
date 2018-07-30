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

#define SIZE 10010000

int num, qLen, k;
int p, q, r, mod;
long long int arr[SIZE];

typedef struct _MQNode
{
    int value;
    int index;
} MQNode;

MQNode mq[SIZE];
int headPt, tailPt;

inline void pop_front()
{
    headPt++;
}

inline void pop_back()
{
    tailPt--;
}

inline void push_back(int value, int index)
{
    while (headPt < tailPt && mq[tailPt - 1].value <= value)
        pop_back();

    mq[tailPt++] = {value, index};
    
    while (headPt < tailPt && mq[headPt].index >= index + qLen)
        pop_front();
}

inline void initArr(int num)
{
    for (int i = k + 1; i <= num; i++)
    {
        arr[i] = (p * arr[i - 1] + (long long int)q * i + r) % mod;
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
        cin >> num >> qLen >> k >> p >> q >> r >> mod;
        for (int i = 1; i <= k; i++)
        {
            cin >> arr[i];
        }
        initArr(num);
        headPt = 0;
        tailPt = 0;

        long long int fst = 0, snd = 0;
        for (int i = num ; i > 0; i--)
        {
            push_back(arr[i], i);
            if (i <= num - qLen + 1)
            {
                int cntMaxRating = mq[headPt].value;
                int cntCount = tailPt - headPt;
                fst += (cntMaxRating ^ i);
                snd += (cntCount ^ i);
            }
        }
        cout << fst << " " << snd << endl;
    }
    return 0;
}