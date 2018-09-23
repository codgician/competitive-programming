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
#include <cassert>
using namespace std;

#define CARD_SIZE 20
#define PLAYER_SIZE 7

int arr[PLAYER_SIZE][CARD_SIZE];
int table[CARD_SIZE];

int lexiOrder[CARD_SIZE] = {9, 1, 2, 3, 4, 5, 6, 7, 8, 0, 10, 12, 11};

int getCardId(char buf[5])
{
    if (buf[0] == 'A')
        return 0;
    if (buf[0] >= '2' && buf[0] <= '9')
        return buf[0] - '1';
    if (buf[0] == '1')
        return 9;
    if (buf[0] == 'J')
        return 10;
    if (buf[0] == 'Q')
        return 11;
    if (buf[0] == 'K')
        return 12;
    return -1;
}

void printCard(int id)
{
    if (id >= 1 && id <= 8)
        printf("%d", id + 1);
    else if (id == 0)
        printf("A");
    else if (id == 9)
        printf("10");
    else if (id == 10)
        printf("J");
    else if (id == 11)
        printf("Q");
    else if (id == 12)
        printf("K");
}

bool isEmpty(int playerId)
{
    for (int i = 0; i < 13; i++)
    {
        if (arr[playerId][i] > 0)
            return false;
    }
    return true;
}

int nextPlayer(int playerId)
{
    return (playerId + 1) % 4;
}

int nextCard(int cardId)
{
    return (cardId + 1) % 13;
}

int getLexiMinCard(int playerId)
{
    for (int i = 0; i < 13; i++)
    {
        if (arr[playerId][lexiOrder[i]] > 0)
        {
            return lexiOrder[i];
        }
    }

    return -1;
}

int getNumMinCard(int playerId)
{
    int minNum = INT_MAX, cardId = -1;
    for (int i = 0; i < 13; i++)
    {
        if (arr[playerId][lexiOrder[i]] > 0 && arr[playerId][lexiOrder[i]] < minNum)
        {
            minNum = arr[playerId][lexiOrder[i]];
            cardId = lexiOrder[i];
        }
    }

    return cardId;
}

int main()
{
    char buf[5];
    while (scanf("%s", buf) != EOF)
    {
        memset(arr, 0, sizeof(arr));
        memset(table, 0, sizeof(table));

        int fstVal = getCardId(buf);
        arr[0][fstVal]++;

        for (int i = 0; i < 4; i++)
        {
            for (int j = (i == 0 ? 1 : 0); j < 13; j++)
            {
                scanf("%s", buf);
                int cardId = getCardId(buf);
                arr[i][cardId]++;
            }   
        }

        int winner = -1;
        bool isTruth = true;
        int roundHolder = 0, statCard = 0;
        while (winner == -1)
        {
            int dlcNum = 0;
            // Round holder start the round
            if (roundHolder == 0)
            {
                if (arr[roundHolder][statCard] > 0)
                {
                    arr[roundHolder][statCard]--;
                    table[statCard]++;
                    dlcNum++;
                    isTruth = true;
                }
                else
                {
                    int cardId = getLexiMinCard(roundHolder);
                    if (cardId != -1)
                    {
                        arr[roundHolder][cardId]--;
                        table[cardId]++;
                        dlcNum++;
                    }
                        
                    isTruth = false;
                }
            }
            else if (roundHolder == 1)
            {
                if (arr[roundHolder][statCard] > 0)
                {
                    dlcNum += arr[roundHolder][statCard];
                    table[statCard] += arr[roundHolder][statCard];
                    arr[roundHolder][statCard] = 0;
                    isTruth = true;
                }
                else
                {
                    int cardId = getLexiMinCard(roundHolder);
                    if (cardId != -1)
                    {
                        arr[roundHolder][cardId]--;
                        table[cardId]++;
                        dlcNum++;
                    }           

                    isTruth = false;
                }
            }
            else if (roundHolder == 2)
            {
                if (arr[roundHolder][statCard] > 0)
                {
                    dlcNum += arr[roundHolder][statCard];
                    table[statCard] += arr[roundHolder][statCard];
                    arr[roundHolder][statCard] = 0;
                    isTruth = true;
                }
                else
                {
                    int cardId = getNumMinCard(roundHolder);
                    if (cardId != -1)
                    {
                        dlcNum += arr[roundHolder][cardId];
                        table[cardId] += arr[roundHolder][cardId];
                        arr[roundHolder][cardId] = 0;
                    }

                    isTruth = false;
                }
            }
            else if (roundHolder == 3)
            {
                if (arr[roundHolder][statCard] == 3 || arr[roundHolder][statCard] == 4)
                {
                    dlcNum += arr[roundHolder][statCard];
                    table[statCard] += arr[roundHolder][statCard];
                    arr[roundHolder][statCard] = 0;
                    isTruth = true;
                }
                else
                {
                    dlcNum += arr[roundHolder][statCard];
                    table[statCard] += arr[roundHolder][statCard];
                    arr[roundHolder][statCard] = 0;

                    int cardId = getLexiMinCard(roundHolder);
                    if (cardId != -1)
                    {
                        arr[roundHolder][cardId]--;
                        table[cardId]++;
                        dlcNum++;
                        isTruth = false;
                    }
                    else
                    {
                        isTruth = true;
                    }
                }
            }

            if (dlcNum == 0)
            {
                winner = roundHolder;
                break;
            }

            // Challengers try to challenge
            int challengerId = -1;
            int cntPlayer = nextPlayer(roundHolder);
            for (int i = 0; i < 3; i++)
            {
                if (cntPlayer == 0)
                {
                    if (
                        (cntPlayer == nextPlayer(roundHolder) && arr[cntPlayer][nextCard(statCard)] == 0) ||
                        (dlcNum + arr[cntPlayer][statCard] > 4)
                    )
                    {
                        challengerId = cntPlayer;
                        break;
                    }
                }
                else if (cntPlayer == 1)
                {
                    if (cntPlayer == nextPlayer(roundHolder) && arr[cntPlayer][nextCard(statCard)] == 0)
                    {
                        challengerId = cntPlayer;
                        break;
                    }
                }
                else if (cntPlayer == 2)
                {
                    if (arr[cntPlayer][statCard] == 4)
                    {
                        challengerId = cntPlayer;
                        break;
                    }
                }
                else if (cntPlayer == 3)
                {
                    if (isEmpty(roundHolder))
                    {
                        challengerId = cntPlayer;
                        break;
                    }
                }

                cntPlayer = nextPlayer(cntPlayer);
            }

            if (challengerId == -1)
            {
                if (isEmpty(roundHolder))
                {
                    winner = roundHolder;
                    break;
                }
            }
            else
            {
                if (isTruth)
                {
                    for (int i = 0; i < 13; i++)
                    {
                        arr[challengerId][i] += table[i];
                        table[i] = 0;
                    }

                    if (isEmpty(roundHolder))
                    {
                        winner = roundHolder;
                        break;
                    }
                }
                else
                {
                    for (int i = 0; i < 13; i++)
                    {
                        arr[roundHolder][i] += table[i];
                        table[i] = 0;
                    }
                }
            }

            statCard = nextCard(statCard);
            roundHolder = nextPlayer(roundHolder);
        }

        for (int i = 0; i < 4; i++)
        {
            if (winner == i)
            {
                printf("WINNER\n");
                continue;
            }

            bool isFirst = true;
            for (int j = 0; j < 13; j++)
            {
                while (arr[i][j] > 0)
                {
                    if (isFirst)
                        isFirst = false;
                    else
                        printf(" ");

                    printCard(j);
                    arr[i][j]--;
                }
            }
            printf("\n");
        }
    }

    return 0;
}