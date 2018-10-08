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

typedef struct _TrieNode
{
    bool isFile; 
    int size;
    map<string, int> nextMp;
} TrieNode;

TrieNode trieArr[SIZE];
int triePt, threshold;

string cntPath;

int newTrieNode()
{
    trieArr[triePt].isFile = false;
    trieArr[triePt].size = 0;
    trieArr[triePt].nextMp.clear();
    return triePt++;
}

void insertFile(string & filePath, int fileSize)
{
    int cntPt = 0;
    trieArr[cntPt].size += fileSize;

    string cntFolder;
    for (int i = 1; i <= (int)filePath.size(); i++)
    {
        if (filePath[i] == '/' || i == (int)filePath.size())
        {
            if (trieArr[cntPt].nextMp.find(cntFolder) == trieArr[cntPt].nextMp.end())
                trieArr[cntPt].nextMp[cntFolder] = newTrieNode();
            cntPt = trieArr[cntPt].nextMp[cntFolder];
            trieArr[cntPt].size += fileSize;
            cntFolder.clear();
        }
        else
        {
            cntFolder.push_back(filePath[i]);
        }
    }
    trieArr[cntPt].isFile = true;
}

void printDirTree(int cntPt)
{
    cntPath.push_back('/');

    bool shouldExpand = false, hasDirectory = false;
    for (auto it = trieArr[cntPt].nextMp.begin(); it != trieArr[cntPt].nextMp.end(); ++it)
    {
        if (!trieArr[it -> second].isFile)
        {
            hasDirectory = true;
            if (trieArr[it -> second].size >= threshold)
            {
                shouldExpand = true;
                break;
            }
        }
    }

    if (!shouldExpand)
    {
        if (hasDirectory)
            cout << "+ ";
        else
            cout << "  ";

        cout << cntPath << " " << trieArr[cntPt].size << endl;
    }
    else
    {
        cout << "- " << cntPath << " " << trieArr[cntPt].size << endl;
        for (auto it = trieArr[cntPt].nextMp.begin(); it != trieArr[cntPt].nextMp.end(); ++it)
        {
            if (trieArr[it -> second].isFile)
                continue;

            cntPath += it -> first;
            printDirTree(it -> second);
            cntPath.erase(cntPath.size() - (it -> first).size());
        }
    }

    cntPath.pop_back();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num;
    while (cin >> num)
    {
        triePt = 0;
        newTrieNode();

        for (int i = 0; i < num; i++)
        {
            string cntPath;
            int cntSize;
            cin >> cntPath >> cntSize;
            insertFile(cntPath, cntSize);
        }

        cin >> threshold;
        cntPath.clear();
        printDirTree(0);
    }
    return 0;
}