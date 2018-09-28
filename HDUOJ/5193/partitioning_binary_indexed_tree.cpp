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

#define SIZE 20100
#define BLOCK_SIZE 2020

typedef struct _Node
{
    int num[BLOCK_SIZE], bit[SIZE];
    int len;
    int nextPt, prevPt;

    void init()
    {
        memset(bit, 0, sizeof(bit));
        len = 0;
        prevPt = -1, nextPt = -1;
    }
} Node;

Node arr[BLOCK_SIZE];

int blockNum, blockSize;
int len, ans;

int getLowbit(int n)
{
    return n & (-n);
}

void add(int * bitArr, int pos, int val)
{
    for (int i = pos; i <= len; i += getLowbit(i))
    {
        bitArr[i] += val;
    }
}

int getPrefixSum(int * bitArr, int pos)
{
    int ans = 0;
    for (int i = pos; i > 0; i -= getLowbit(i))
    {
        ans += bitArr[i];
    }
    return ans;
}

int getRangeSum(int * bitArr, int qLeftPt, int qRightPt)
{
    return getPrefixSum(bitArr, qRightPt) - getPrefixSum(bitArr, qLeftPt - 1);
}

int getBlockId(int & pos)
{
    int i = 0;
    while (arr[i].len <= pos && arr[i].nextPt != -1)
    {
        pos -= arr[i].len;
        i = arr[i].nextPt;
    }
    return i;
}

int workInvPair(int pos)
{
    int ret = 0;
    int blockId = getBlockId(pos);

    for (int i = 0; i < pos; i++)
    {
        if (arr[blockId].num[i] > arr[blockId].num[pos])
            ret++;
    }
    for (int i = pos + 1; i < arr[blockId].len; i++)
    {
        if (arr[blockId].num[i] < arr[blockId].num[pos])
            ret++;
    }

    for (int i = 0; i != blockId; i = arr[i].nextPt)
        ret += getRangeSum(arr[i].bit, arr[blockId].num[pos] + 1, len);
    for (int i = arr[blockId].nextPt; i != -1; i = arr[i].nextPt)
        ret += getPrefixSum(arr[i].bit, arr[blockId].num[pos] - 1);
    
    return ret;
}

void insert(int pos, int val)
{
    int globalPos = pos;
    if (blockNum == 0)
    {
        arr[blockNum].init();
        arr[blockNum].num[arr[0].len++] = val;
        add(arr[blockNum].bit, val, 1);
        blockNum++;
        return;
    }

    int blockId = getBlockId(pos);

    arr[blockId].len++;
    for (int i = arr[blockId].len - 1; i > pos; i--)
    {
        arr[blockId].num[i] = arr[blockId].num[i - 1];
    }
    arr[blockId].num[pos] = val;
    add(arr[blockId].bit, val, 1);

    if (arr[blockId].len - 1 == blockSize)
    {
        // New block
        arr[blockNum].init();

        int newLen = (arr[blockId].len >> 1) + 1, pt = 0;
        for (int i = newLen; i < arr[blockId].len; i++)
        {
            arr[blockNum].num[pt++] = arr[blockId].num[i];
            add(arr[blockNum].bit, arr[blockId].num[i], 1);
            add(arr[blockId].bit, arr[blockId].num[i], -1);
        }

        arr[blockNum].len = pt;
        arr[blockNum].prevPt = blockId;
        arr[blockNum].nextPt = arr[blockId].nextPt;

        arr[blockId].nextPt = blockNum;
        arr[blockId].len = newLen;

        blockNum++;
    }

    ans += workInvPair(globalPos);
}

void remove(int pos)
{
    ans -= workInvPair(pos);

    int blockId = getBlockId(pos);
    add(arr[blockId].bit, arr[blockId].num[pos], -1);

    for (int i = pos + 1; i < arr[blockId].len; i++)
    {
        arr[blockId].num[i - 1] = arr[blockId].num[i];
    }
    arr[blockId].len--;

    if (arr[blockId].len == 0)
    {
        // Delete block
        int prevBlock = arr[blockId].prevPt;
        int nextBlock = arr[blockId].nextPt;
        if (prevBlock != -1)
            arr[prevBlock].nextPt = nextBlock;
        if (nextBlock != -1)
            arr[nextBlock].prevPt = prevBlock;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int qNum;
    while (cin >> len >> qNum)
    {
        blockSize = sqrt(len) * log2(len);
        ans = 0;
        blockNum = 0;

        for (int i = 0; i < len; i++)
        {
            int cnt;
            cin >> cnt;
            insert(i, cnt);
        }

        while (qNum--)
        {
            int opr, pos;
            cin >> opr >> pos;
            pos--;

            if (opr == 0)
            {
                // insert
                int val;
                cin >> val;
                insert(pos + 1, val);
            }
            else
            {
                // remove
                remove(pos);
            }
            cout << ans << endl;
        }
    }
    return 0;
}