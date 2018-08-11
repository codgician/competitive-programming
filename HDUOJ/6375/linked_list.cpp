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

#define SIZE 300020

class Node
{
public:
    Node *prev, *next;
    int val;
};
Node *head[SIZE], *tail[SIZE];

bool isEmpty(int qId) {
    if (head[qId] == nullptr && tail[qId] == nullptr) {
        return true;
    }
    return false;
}

void push_back(int qId, int val) {
    Node *cntNode = new Node();
    cntNode -> val = val;
    cntNode -> next = nullptr;
    cntNode -> prev = tail[qId];

    if (tail[qId] != nullptr) {
        tail[qId] -> next = cntNode;
    }

    if (isEmpty(qId)) {
        head[qId] = cntNode;
    }

    tail[qId] = cntNode;
}

void push_front(int qId, int val) {
    Node *cntNode = new Node();
    cntNode -> val = val;
    cntNode -> prev = nullptr;
    cntNode -> next = head[qId];

    if (head[qId] != nullptr) {
        head[qId] -> prev = cntNode;
    }

    if (isEmpty(qId)) {
        tail[qId] = cntNode;
    }

    head[qId] = cntNode;
}

int pop_back(int qId) {
    if (isEmpty(qId)) {
        return -1;
    }

    Node *delNode = tail[qId];
    int res = delNode -> val;
    tail[qId] = tail[qId] -> prev;

    if (tail[qId] == nullptr) {
        head[qId] = nullptr;
    } else {
        tail[qId] -> next = nullptr;
    }

    delete delNode;
    return res;
}

int pop_front(int qId) {
    if (isEmpty(qId)) {
        return -1;
    }

    Node *delNode = head[qId];
    int res = delNode -> val;
    head[qId] = head[qId] -> next;

    if (head[qId] == nullptr) {
        tail[qId] = nullptr;
    } else {
        head[qId] -> prev = nullptr; 
    }

    delete delNode;
    return res;
}

void mergeQueue(int fstId, int sndId) {
    // Check if empty
    if (isEmpty(sndId)) {
        return;
    }
    if (isEmpty(fstId)) {
        head[fstId] = head[sndId];
        tail[fstId] = tail[sndId];

        head[sndId] = nullptr;
        tail[sndId] = nullptr;
        return; 
    }

    head[sndId] -> prev = tail[fstId];
    tail[fstId] -> next = head[sndId];
    tail[fstId] = tail[sndId];

    head[sndId] = nullptr;
    tail[sndId] = nullptr;
}

template<class T>
bool read(T &num) {
    int ch;
    while (1) {
        ch = getchar();
        if (ch == EOF) return false;
        if (ch >= '0'&&ch <= '9') {
            num = T(ch - '0');
            break;
        }
    }
    while (1) {
        ch = getchar();
        if (ch == EOF) return false;
        if (ch >= '0'&&ch <= '9') num = num*T(10) + T(ch - '0');
        else break;
    }
    return true;
}

int main()
{
    int num, oprNum;
    while (read(num) && read(oprNum)) {
        for (int i = 0; i <= (num << 1); i++) {
            head[i] = nullptr;
            tail[i] = nullptr;
        }

        while (oprNum--) {
            int opr;
            read(opr);
            if (opr == 1) {
                int qId, where, val;
                read(qId);
                read(where);
                read(val);
                qId--;

                if (where == 0) {
                    push_front(qId << 1, val);
                    push_back(qId << 1 | 1, val);
                } else {
                    push_back(qId << 1, val);
                    push_front(qId << 1 | 1, val);
                }
            }
            else if (opr == 2)
            {
                int qId, where;
                read(qId);
                read(where);
                qId--;

                int ans = -1;
                if (where == 0) {
                    ans = pop_front(qId << 1);
                    pop_back(qId << 1 | 1);
                } else {
                    ans = pop_back(qId << 1);
                    pop_front(qId << 1 | 1);
                }

                printf("%d\n", ans);
            }
            else if (opr == 3)
            {
                int fstId, sndId, where;
                read(fstId);
                read(sndId);
                read(where);
                fstId--;
                sndId--;
                if (where == 0) {
                    mergeQueue(fstId << 1, sndId << 1);
                    mergeQueue(sndId << 1 | 1, fstId << 1 | 1);
                    swap(head[sndId << 1 | 1], head[fstId << 1 | 1]);
                    swap(tail[sndId << 1 | 1], tail[fstId << 1 | 1]);
                } else {
                    mergeQueue(fstId << 1, sndId << 1 | 1);
                    mergeQueue(sndId << 1, fstId << 1 | 1);
                    swap(head[sndId << 1], head[fstId << 1 | 1]);
                    swap(tail[sndId << 1], tail[fstId << 1 | 1]);
                }
            }
        }
    }
    return 0;
}