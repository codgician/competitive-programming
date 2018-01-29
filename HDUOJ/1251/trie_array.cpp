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
#define SIZE 999999
using namespace std;

typedef struct _TrieNode
{
    int num;
    int next[26];
    bool isWord;
} TrieNode;

TrieNode arr[SIZE];
int nextFreePt = 0;

int createTrieNode()
{
    arr[nextFreePt].num = 0;
    arr[nextFreePt].isWord = false;
    for (int i = 0; i < 26; i++)
    {
        arr[nextFreePt].next[i] = -1;
    }
    nextFreePt++;
    return nextFreePt - 1;
}

void insertWord(char* word)
{
    int cntNodePt =  0;
    for (int i = 0; i < strlen(word); i++)
    {
        int cnt = word[i] - 'a';
        if (arr[cntNodePt].next[cnt] == -1)
        {
            arr[cntNodePt].next[cnt] = createTrieNode();
        }
        cntNodePt = arr[cntNodePt].next[cnt];
        arr[cntNodePt].num++;
    }
    arr[cntNodePt].isWord = true;
}

int getNum(char* word)
{
    int cntNodePt = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        int cnt = word[i] - 'a';
        cntNodePt = arr[cntNodePt].next[cnt];
        if (cntNodePt == -1)
            return 0;
    }
    return arr[cntNodePt].num;
}

int main()
{
    ios::sync_with_stdio(false);
    createTrieNode();
    char str[12];
    bool isTable = true;
    while (cin.getline(str, 11))
    {
        if (strlen(str) == 0)
        {
            isTable = false;
        }
        else if (isTable)
        {
            insertWord(str);
        }
        else
        {
            cout << getNum(str) << endl;
        }
    }
    return 0;
}
