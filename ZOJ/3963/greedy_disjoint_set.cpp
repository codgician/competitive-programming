#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

int arr[SIZE], parent[SIZE];
set<pair<int, int> > st;
vector<int> vec[SIZE];

int getParent(int n) {
    if (parent[n] == n) {
        return n;
    } else {
        parent[n] = getParent(parent[n]);
        return parent[n];
    }
}

void merge(int fst, int snd) {
    fst = getParent(fst);
    snd = getParent(snd);
    if (fst != snd) {
        parent[snd] = fst;
    }
}

int main() {
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--) {
        st.clear();
        int len;
        scanf("%d", &len);
        for (int i = 0; i < len; i++) {
            parent[i] = i;
            vec[i].clear();
            scanf("%d", arr + i);
        }

        for (int i = len - 1; i >= 0; i--) {
            for (int j = 0; j < 2; j++) {
                set<pair<int, int> >::iterator it = st.lower_bound(make_pair(arr[i], -1)); 
                if (it != st.end()) {
                    int id = it -> second;
                    merge(id, i);
                    st.erase(it);
                }
            }
            st.insert(make_pair(arr[i], i));        
        }

        int num = 0;
        for (int i = 0; i < len; i++) {
            if (getParent(i) == i)
                num++;
            vec[getParent(i)].push_back(i);
        }

        printf("%d\n", num);
        for (int i = 0; i < len; i++) {
            if (vec[i].size() == 0)
                continue;
            printf("%d", (int)vec[i].size());
            for (int j = 0; j < (int)vec[i].size(); j++)
                printf(" %d", vec[i][j] + 1);
            printf("\n");
        }
    }

    return 0;
}