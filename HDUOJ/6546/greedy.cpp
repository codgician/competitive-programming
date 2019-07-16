#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

typedef struct _Node {
    int a, b, c, peak;
    long long int work(long long int x) {
        return a * x * x + b * x + c;
    }
} Node;

Node arr[SIZE];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int num, sum;
    while (cin >> num >> sum) {
        long long int cntAns = 0; int cntSum = 0;
        for (int i = 0; i < num; i++) {
            cin >> arr[i].a >> arr[i].b >> arr[i].c;
            int peak = 1;
            if (arr[i].b < 0) {
                peak = (-arr[i].b) / (arr[i].a << 1); 
                int tmp1 = peak + 1, tmp2 = peak - 1;
                if (arr[i].work(peak) > arr[i].work(tmp1))
                    peak = tmp1;
                if (arr[i].work(peak) > arr[i].work(tmp2))
                    peak = tmp2;
            }
            peak = max(peak, 1);
            cntAns += arr[i].work(peak); cntSum += peak;
            arr[i].peak = peak;
        }

        if (cntSum == sum) {
            cout << cntAns << '\n';
            continue;
        }

        priority_queue<
            pair<long long int, int>,
            vector<pair<long long int, int> >,
            greater<pair<long long int, int> >
        > pq;

        int inc = (cntSum > sum ? -1 : 1);
        for (int i = 0; i < num; i++)
            if (arr[i].peak + inc > 0)
                pq.push(make_pair(arr[i].work(arr[i].peak + inc) - arr[i].work(arr[i].peak), i));
        
        while (cntSum != sum) {
            pair<long long int, int> p = pq.top(); pq.pop();
            cntSum += inc; cntAns += p.first; arr[p.second].peak += inc;
            if (arr[p.second].peak + inc > 0) {
                pair<long long int, int> p1 = make_pair(arr[p.second].work(arr[p.second].peak + inc) - arr[p.second].work(arr[p.second].peak), p.second);
                pq.push(p1);
            }
        }

        cout << cntAns << '\n';
    }

    return 0;
}