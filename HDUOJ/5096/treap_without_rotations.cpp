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
#define PROB_SIZE 11

typedef struct _Score
{
    int acNum;
    int penalty;

    bool operator < (const struct _Score & snd) const
    {
        if (this -> acNum == snd.acNum)
            return this -> penalty < snd.penalty;
        return this -> acNum > snd.acNum;
    }

    bool operator == (const struct _Score & snd) const
    {
        return this -> acNum == snd.acNum && this -> penalty == snd.penalty;
    }
} Score;

Score teamArr[SIZE];

bool hasSolved[SIZE][PROB_SIZE];
int lastSubTime[SIZE], lastAcOrder[SIZE], tryNum[SIZE][PROB_SIZE];

struct cmp
{
    bool operator()(const int & fst, const int & snd) const
    {
        if (lastAcOrder[fst] == -1 && lastAcOrder[snd] == -1)
            return fst < snd;
        if (lastAcOrder[fst] == -1 || lastAcOrder[snd] == -1)
            return lastAcOrder[snd] == -1;
        return lastAcOrder[fst] < lastAcOrder[snd];
    }
};

typedef struct _TreapNode
{
    Score value;
    set<int, cmp> st;
    int key;
    int size;
    int leftSon, rightSon;
} TreapNode;

TreapNode treap[SIZE];
int treapPt, rootPt;

void update(int cntPt)
{
    treap[cntPt].size = treap[treap[cntPt].leftSon].size + treap[treap[cntPt].rightSon].size + treap[cntPt].st.size();
}

int newNode(Score & val)
{
    treapPt++;
    treap[treapPt].size = 0;
    treap[treapPt].value = val;
    treap[treapPt].st.clear();
    treap[treapPt].key = rand();
    treap[treapPt].leftSon = 0;
    treap[treapPt].rightSon = 0;
    return treapPt;
}

int merge(int fst, int snd)
{
    if (!fst)
        return snd;
    if (!snd)
        return fst;

    if (treap[fst].key < treap[snd].key)
    {
        treap[fst].rightSon = merge(treap[fst].rightSon, snd);
        update(fst);
        return fst;
    }
    else
    {
        treap[snd].leftSon = merge(fst, treap[snd].leftSon);
        update(snd);
        return snd;
    }
}

void split(int cntPt, Score & val, int & fst, int & snd)
{
    if (!cntPt)
    {
        fst = 0;
        snd = 0;
        return;
    }

    if (treap[cntPt].value < val || treap[cntPt].value == val)
    {
        fst = cntPt;
        split(treap[cntPt].rightSon, val, treap[cntPt].rightSon, snd);
    }
    else
    {
        snd = cntPt;
        split(treap[cntPt].leftSon, val, fst, treap[cntPt].leftSon);
    }
    update(cntPt);
}

int findValByRank(int cntPt, int rnk)
{
    while (rnk > 0 && cntPt > 0)
    {
        if (rnk <= treap[treap[cntPt].leftSon].size)
            cntPt = treap[cntPt].leftSon;
        else if (rnk == treap[treap[cntPt].leftSon].size + 1)
            return cntPt;
        else
        {
            rnk -= treap[treap[cntPt].leftSon].size + treap[cntPt].st.size();
            cntPt = treap[cntPt].rightSon;
        }
    }

    return -1;
}

void insertTeam(int teamId, Score & val)
{
    teamArr[teamId] = val;
    int fst = 0, snd = 0, thd = 0;
    split(rootPt, val, fst, snd);
    Score tmp = teamArr[teamId];
    tmp.penalty--;
    split(fst, tmp, fst, thd);

    if (thd == 0)
        thd = newNode(val);
        
    treap[thd].st.insert(teamId);
    treap[thd].size++;
    rootPt = merge(merge(fst, thd), snd);
}

Score deleteTeam(int teamId)
{
    int fst = 0, snd = 0, thd = 0;
    split(rootPt, teamArr[teamId], fst, snd);
    Score tmp = teamArr[teamId];
    tmp.penalty--;
    split(fst, tmp, fst, thd);
    Score ans = treap[thd].value;

    treap[thd].st.erase(teamId);
    treap[thd].size--;

    if (treap[thd].size == 0)
    {
        rootPt = merge(fst, snd);
    }
    else
    {
        rootPt = merge(merge(fst, thd), snd);
    }
    return ans;
}

int queryRank(int teamId)
{
    int fst = 0, snd = 0;
    Score tmp = teamArr[teamId];
    tmp.penalty--;
    split(rootPt, tmp, fst, snd);
    int ans = treap[fst].size + 1;
    rootPt = merge(fst, snd);
    return ans;
}

int queryTeamByRank(int rnk)
{
    int ansPt = findValByRank(rootPt, rnk);
    if (ansPt == -1)
        return 0;

    return *treap[ansPt].st.begin();
}

int main()
{
    int teamNum, probNum;
    while (scanf("%d%d", &teamNum, &probNum) != EOF)
    {
        treapPt = 0;
        rootPt = 0;
        memset(hasSolved, false, sizeof(hasSolved));
        memset(lastSubTime, -1, sizeof(lastSubTime));
        memset(lastAcOrder, -1, sizeof(lastAcOrder));
        memset(tryNum, 0, sizeof(tryNum));
        memset(teamArr, 0, sizeof(teamArr));

        Score initScr = {0, 0};
        for (int i = 1; i <= teamNum; i++)
        {
            insertTeam(i, initScr);
        }

        char opr[20];
        int orderPt = 0;
        while (scanf("%s", opr) != EOF)
        {
            if (opr[0] == 'S')
            {
                orderPt++;
                // Submission
                int subTime, teamId, probId, res;
                char probChar;
                scanf("%d:%d:%c:%d", &subTime, &teamId, &probChar, &res);
                probId = probChar - 'A';
                teamId++;

                // Judge if submission is valid
                if (hasSolved[teamId][probId] || (lastSubTime[teamId] != -1 && subTime - lastSubTime[teamId] < 5))
                    continue;
                lastSubTime[teamId] = subTime;

                if (res == 0)
                {
                    // Not accepted
                    tryNum[teamId][probId]++;
                }
                else
                {
                    // Accepted
                    printf("[%d][%c]\n", teamId - 1, probChar);
                    Score prevScr = deleteTeam(teamId);
                    prevScr.acNum++;
                    prevScr.penalty += subTime + 20 * tryNum[teamId][probId];
                    lastAcOrder[teamId] = orderPt;
                    hasSolved[teamId][probId] = true;
                    insertTeam(teamId, prevScr);
                }
            }
            else if (opr[0] == 'R')
            {
                // Query rank by teamId
                int teamId;
                scanf("%d", &teamId);
                teamId++;
                printf("%d\n", queryRank(teamId));
            }
            else if (opr[0] == 'T')
            {
                // Query teamId by rank
                int rnk;
                scanf("%d", &rnk);
                printf("%d\n", queryTeamByRank(rnk) - 1);
            }
            else if (opr[0] == 'C')
            {
                // Contest ends
                scanf("%s", opr);
                printf("\n");
                break;
            }
        }
    }
    return 0;
}