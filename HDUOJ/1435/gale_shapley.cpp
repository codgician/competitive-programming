#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <map>
#define SIZE 201
using namespace std;

typedef struct _Node
{
    int name;
    int capacity;
    double x;
    double y;
    double z;
} Node;

typedef struct _Edge
{
    int partnerId;
    int capacity;
    double distance;
} Edge;

Node sender[SIZE], receiver[SIZE];
Edge senderPref[SIZE][SIZE];
int receiverMatch[SIZE];
bool hasProposed[SIZE][SIZE];

queue<int> q;

double getDistance(Node a, Node b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

bool cmpRule(Edge a, Edge b)
{
    if (a.distance == b.distance)
        return a.capacity > b.capacity;
    else
        return a.distance < b.distance;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(receiverMatch, -1, sizeof(receiverMatch));
        memset(hasProposed, false, sizeof(hasProposed));
        int matchNum;
        cin >> matchNum;
        for (int i = 0; i < matchNum; i++)
        {
            cin >> sender[i].name >> sender[i].capacity >> sender[i].x >> sender[i].y >> sender[i].z;
            q.push(i);
        }
        for (int i = 0; i < matchNum; i++)
        {
            cin >> receiver[i].name >> receiver[i].capacity >> receiver[i].x >> receiver[i].y >> receiver[i].z;
        }

        for (int i = 0; i < matchNum; i++)
        {
            for (int j = 0; j < matchNum; j++)
            {
                senderPref[i][j].partnerId = j;
                senderPref[i][j].capacity = receiver[j].capacity;
                senderPref[i][j].distance = getDistance(sender[i], receiver[j]);
            }
            sort(senderPref[i] + 0, senderPref[i] + matchNum, cmpRule);
        }

        while (!q.empty())
        {
            int cntSenderId = q.front();
            q.pop();

            for (int i = 0; i < matchNum; i++)
            {
                int cntReceiverId = senderPref[cntSenderId][i].partnerId;
                if (hasProposed[cntSenderId][cntReceiverId])
                    continue;

                hasProposed[cntSenderId][cntReceiverId] = true;

                if (receiverMatch[cntReceiverId] == -1)
                {
                    receiverMatch[cntReceiverId] = cntSenderId;
                    break;
                }
                else
                {
                    int prevSenderId = receiverMatch[cntReceiverId];
                    int j;
                    for (int k = 0; k < matchNum; k++)
                    {
                        if (senderPref[prevSenderId][k].partnerId == cntReceiverId)
                        {
                            j = k;
                            break;
                        }
                    }
                    if (senderPref[cntSenderId][i].distance < senderPref[prevSenderId][j].distance || (senderPref[cntSenderId][i].distance == senderPref[prevSenderId][j].distance && sender[cntSenderId].capacity > sender[prevSenderId].capacity))
                    {
                        q.push(prevSenderId);
                        receiverMatch[cntReceiverId] = cntSenderId;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < matchNum; i++)
        {
            cout << sender[receiverMatch[i]].name << " " << receiver[i].name << endl;
        }
    }
    return 0;
}
