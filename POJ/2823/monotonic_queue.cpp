// POJ - 2823
// Maintain a monotonic queue.

#include <cstdio>
#define SIZE 1000010
#define HEAD true
#define TAIL false
#define MAXQ true
#define MINQ false
using namespace std;

struct MonotonicQueue {
    int value;
    int index;
} q[SIZE];

int a[SIZE];
int n, k, head, tail;

void pop(bool loc)
{
    if (head <= tail)
    {
        if (loc == HEAD)
            head++;
        else if (loc == TAIL)
            tail--;
    }
    return;
}

void push(int value, int index, bool type)
{
    if (type == MAXQ)
    {
        while (tail > head && q[tail - 1].value < value)
        {
            pop(TAIL);
        }
    }
    else if (type == MINQ)
    {
        while (tail > head && q[tail - 1].value > value)
        {
            pop(TAIL);
        }
    }

    q[tail].value = value;
    q[tail].index = index;

    tail++;

    while (tail > head && q[head].index < index - k + 1)
    {
        pop(HEAD);
    }

}

int main()
{
    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // Get minimum.
    head = 0;
    tail = 0;
    for (int i = 0; i < n; i++)
    {
        push(a[i], i, MINQ);
        if (i > k - 2)
        {
            printf("%d", q[head].value);
            if (i < n - 1)
                printf(" ");
            else
                printf("\n");
        }
    }

    // Get maximum.
    head = 0;
    tail = 0;
    for (int i = 0; i < n; i++)
    {
        push(a[i], i, MAXQ);
        if (i > k - 2)
        {
             printf("%d", q[head].value);
            if (i < n - 1)
                printf(" ");
        }
    }

    return 0;
}
