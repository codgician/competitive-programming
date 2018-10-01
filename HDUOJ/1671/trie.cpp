#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 9999999
using namespace std;

typedef struct _TrieNode
{
    int num;
    int next[10];
    int isPhone;
} TrieNode;

TrieNode arr[SIZE];
int nextFreePt = 0;
bool ans = true;

int createTrieNode()
{
    arr[nextFreePt].num = 0;
    arr[nextFreePt].isPhone = false;
    for (int i = 0; i < 10; i++)
    {
        arr[nextFreePt].next[i] = -1;
    }
    nextFreePt++;
    return nextFreePt - 1;
}

void insertPhone(string phone)
{
    int cntNodePt = 0;
    for (int i = 0; i < phone.length(); i++)
    {
        int cnt = phone[i] - '0';
        if (arr[cntNodePt].next[cnt] == -1)
        {
            arr[cntNodePt].next[cnt] = createTrieNode();
        }
        cntNodePt = arr[cntNodePt].next[cnt];
        arr[cntNodePt].num++;
    }
    arr[cntNodePt].isPhone = true;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        nextFreePt = 0;
        createTrieNode();
        int phoneNum;
        cin >> phoneNum;
        while (phoneNum--)
        {
            string phone;
            cin >> phone;
            insertPhone(phone);
        }

        bool ans = true;
        for (int i = 0; i < nextFreePt; i++)
        {
            if (arr[i].isPhone && arr[i].num > 1)
            {
                ans = false;
                break;
            }
        }
        if (ans)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
    return 0;
}
