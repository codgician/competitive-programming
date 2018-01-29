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
using namespace std;

typedef struct _TrieNode
{
    int num;
    struct _TrieNode *next[26];
    bool isWord;
} TrieNode;

TrieNode *createTrieNode()
{
    TrieNode *pNode = (TrieNode *)malloc(sizeof(TrieNode));
    pNode -> num = 0;
    pNode -> isWord = false;
    for (int i = 0; i < 26; i++)
    {
        pNode -> next[i] = NULL;
    }
    return pNode;
}

void insertWord(TrieNode *rootNode, char* word)
{
    TrieNode *cntNode = rootNode;
    for (int i = 0; i < strlen(word); i++)
    {
        int cnt = word[i] - 'a';
        if (cntNode -> next[cnt] == NULL)
        {
            cntNode -> next[cnt] = createTrieNode();
        }
        cntNode = cntNode -> next[cnt];
        cntNode -> num += 1;
    }
    cntNode -> isWord = true;
}

int getNum(TrieNode *rootNode, char* word)
{
    TrieNode *cntNode = rootNode;
    for (int i = 0; i < strlen(word); i++)
    {
        int cnt = word[i] - 'a';
        cntNode = cntNode -> next[cnt];
        if (cntNode == NULL)
            return 0;
    }
    return cntNode -> num;
}

int main()
{
    ios::sync_with_stdio(false);
    TrieNode *rootNode = createTrieNode();
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
            insertWord(rootNode, str);
        }
        else
        {
            cout << getNum(rootNode, str) << endl;
        }
    }
    return 0;
}
