#include <bits/stdc++.h>
using namespace std;

#define SIZE 10010

int parent[SIZE];
bool vis[SIZE];

int getParent(int cntPt) {
    if (parent[cntPt] == cntPt) {
        return cntPt;
    } else {
        parent[cntPt] = getParent(parent[cntPt]);
        return parent[cntPt];
    }
}

bool merge(int fstPt, int sndPt) {
    fstPt = getParent(fstPt); sndPt = getParent(sndPt);
    if (fstPt == sndPt)
        return false;
    if (fstPt > sndPt)
        swap(fstPt, sndPt);
    parent[sndPt] = fstPt;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for (int i = 0; i < SIZE; i++)
        parent[i] = i, vis[i] = false;
    int num; cin >> num;
    for (int i = 0; i < num; i++) {
        int fstPt, sndPt;
        cin >> fstPt >> sndPt;
        fstPt--; sndPt--;
        vis[min(fstPt, sndPt)] = true;
        if (!merge(fstPt, sndPt))
            vis[max(fstPt, sndPt)] = true;
    }

    for (int i = 0; i < SIZE; i++) {
        if (!vis[i]) {
            cout << i << '\n';
            break;
        }
    }

    return 0;
}
