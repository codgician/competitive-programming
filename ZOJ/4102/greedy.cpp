#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010
#define DIGIT_SIZE 10

int arr[SIZE], orig[SIZE], ava[SIZE];
int ans[SIZE], ansPt;
bool lazy[SIZE];
priority_queue<pair<int, int> > pq;
set<int> avaList;

void updatePq() {
    int cntPt = pq.top().second;
    pq.pop();
    if (ava[cntPt] > 0)
        pq.push(make_pair(ava[cntPt] + orig[cntPt], cntPt));
    lazy[cntPt] = false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        memset(orig, 0, sizeof(orig));
        memset(ava, 0, sizeof(ava));
        memset(lazy, false, sizeof(lazy));
        avaList.clear();
        pq = priority_queue<pair<int, int> >();

        int len;
        cin >> len;
        for (int i = 0; i < len; i++) {
            cin >> arr[i]; arr[i]--;
            orig[arr[i]]++; ava[arr[i]]++;
        }

        for (int i = 0; i < len; i++) {
            if (ava[arr[i]] > 0) {
                pq.push(make_pair(orig[i] + ava[i], i));
                avaList.insert(i);
            }
        }

        bool hasAns = true; int ansPt = 0;
        for (int i = 0; i < len; i++) {
            while (!pq.empty() && lazy[pq.top().second])
                updatePq();

            if (pq.empty() || pq.top().first > len - i) {
                hasAns = false;
                break;
            }

            int dangPt = pq.top().second, dangSum = pq.top().first;
            if (dangSum == len - i && dangPt != arr[i]) {
                // Can't decrease orig(dangPt), must decrease ava(dangPt)
                ans[ansPt++] = dangPt;
                ava[dangPt]--; lazy[dangPt] = true;
                orig[arr[i]]--; lazy[arr[i]] = true;
            } else {
                // Select smallest available
                auto it = avaList.begin();
                while (it != avaList.end()) {
                    if (ava[*it] == 0) {
                        ++it;
                        avaList.erase(prev(it));
                    } else if (*it == arr[i]) {
                        ++it;
                    } else {
                        break;
                    }
                }

                if (it == avaList.end()) {
                    hasAns = false;
                    break;
                }

                ans[ansPt++] = *it;
                ava[*it]--; lazy[*it] = true;
                orig[arr[i]]--; lazy[arr[i]] = true;
            }
        }

        if (hasAns) {
            cout << ans[0] + 1;
            for (int i = 1; i < ansPt; i++)
                cout << " " << ans[i] + 1;
            cout << '\n';
        } else {
            cout << "Impossible\n";
        }
    }

    return 0;
}