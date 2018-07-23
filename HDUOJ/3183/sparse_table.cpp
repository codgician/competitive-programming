#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

string str;
int st[SIZE][SIZE];
int ans[SIZE], ansPt;
int len;

int getMin(int fst, int snd)
{
    return str[fst] <= str[snd] ? fst : snd;
}

void init()
{
    for (int i = 0; i < len; i++)
        st[i][0] = i;
    int step = log2(len) + 1;
    for (int j = 1; j < step; j++)
    {
        for (int i = 0; i < len - (1 << j) + 1; i++)
        {
            st[i][j] = getMin(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int leftPt, int rightPt)
{
    int k = log2(rightPt - leftPt + 1);
    return getMin(st[leftPt][k], st[rightPt - (1 << k) + 1][k]);
}

int main()
{
    ios::sync_with_stdio(false);
    int num;
    while (cin >> str >> num)
    {
        len = str.size();
        init();
        ansPt = 0;

        int leftPt = 0, rightPt = num;
        int selectNum = len - num;
        while (selectNum > 0)
        {
            int cntPos = query(leftPt, rightPt);
            ans[ansPt++] = str[cntPos] - '0';
            leftPt = cntPos + 1;
            rightPt++;
            selectNum--;
        }

        bool hasNonZero = false;
        for (int i = 0; i < ansPt; i++)
        {
            if (hasNonZero)
            {
                cout << ans[i];
            }
            else if (ans[i] != 0)
            {
                cout << ans[i];
                hasNonZero = true;
            }
        }
        if (!hasNonZero)
            cout << 0;
        cout << endl;
    }
    return 0;
}
