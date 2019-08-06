#include <bits/stdc++.h>
using namespace std;

#define SIZE 100010

class Frac {
public:
    long long int a, b;

    Frac(long long int a1, long long int b1) {
        if (a1 == 0) {
            a = 0, b = 1;
        } else {
            if (b1 < 0) 
                b1 *= -1, a1 *= -1;
            long long int gcd = llabs(__gcd(llabs(a1), llabs(b1)));
            a = a1 / gcd, b = b1 / gcd;
        } 
    }

    bool operator > (const Frac & snd) const {
        return a * snd.b > b * snd.a;
    }

    bool operator == (const Frac & snd) const {
        return a * snd.b == b * snd.a;
    }

    bool operator < (const Frac & snd) const {
        return a * snd.b < b * snd.a;
    }

    void print() {
        cout << a << '/' << b;
    }
};

const Frac zero(0, 1);

pair<long long int, long long int> arr[SIZE];

vector<pair<Frac, int> > vec;
set<Frac> ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        ans.clear();
        int len; long long int c; cin >> len >> c;
        long long int asum = 0, bsum = 0, bAbsSum = 0;
        for (int i = 0; i < len; i++) {
            cin >> arr[i].first >> arr[i].second;
            asum += arr[i].first; bsum += arr[i].second; bAbsSum += llabs(arr[i].second);
        }

        if (bAbsSum == c)
            ans.insert(Frac(0, 1));
        sort(arr + 0, arr + len, [](const pair<int, int> & fst, const pair<int, int> & snd) {
            return fst.second < snd.second;
        });
        bool flag = false;

        // x > 0
        long long int asum1 = asum, bsum1 = bsum; vec.clear();
        for (int i = 0; i < len && arr[i].second < 0; i++)
            vec.push_back(make_pair(Frac(-arr[i].second, arr[i].first), i));
        sort(vec.begin(), vec.end(), greater<pair<Frac, int>>());
        int siz = vec.size();
        for (int i = 0; i < siz + 1; i++) {
            if (asum1 == 0) {
                if (bsum1 == c) {
                    flag = true; break;
                }
                asum1 -= 2 * arr[vec[i].second].first, bsum1 -= 2 * arr[vec[i].second].second;
                continue;
            }

            Frac ret(c - bsum1, asum1);
            Frac upperLim = {1, 0}, lowerLim = {0, 1};
            if (i > 0)
                upperLim = vec[i - 1].first;
            if (i < siz)
                lowerLim = vec[i].first;

            if (ret > zero && (ret > lowerLim || ret == lowerLim) && ret < upperLim)
                ans.insert(ret);
            if (i < siz) 
                asum1 -= 2 * arr[vec[i].second].first, bsum1 -= 2 * arr[vec[i].second].second;
        } 

        if (flag) {
            cout << -1 << '\n';
            continue;
        }
        
        // x < 0
        asum1 = -1ll * asum, bsum1 = -1ll * bsum; vec.clear();
        for (int i = len - 1; i >= 0 && arr[i].second > 0; i--)
            vec.push_back(make_pair(Frac(-arr[i].second, arr[i].first), i));
        sort(vec.begin(), vec.end(), less<pair<Frac, int>>());
        siz = vec.size();
        for (int i = 0; i < siz + 1; i++) {
            if (asum1 == 0) {
                if (bsum1 == c) {
                    flag = true; break;
                }
                asum1 += 2 * arr[vec[i].second].first, bsum1 += 2 * arr[vec[i].second].second;
                continue;
            }

            Frac ret(c - bsum1, asum1);
            Frac upperLim = {0, 1}, lowerLim = {-1, 0};
            if (i > 0)
                lowerLim = vec[i - 1].first;
            if (i < siz)
                upperLim = vec[i].first;

            if (ret < zero && ret > lowerLim && (ret < upperLim || ret == upperLim))
                ans.insert(ret);
            if (i < siz) 
                asum1 += 2 * arr[vec[i].second].first, bsum1 += 2 * arr[vec[i].second].second;
        }

        if (flag) {
            cout << -1 << '\n';
            continue;
        }

        if (ans.empty()) {
            cout << 0 << '\n';
            continue;
        }

        cout << ans.size();
        for (auto fr : ans) {
            cout << ' '; fr.print();
        }
        cout << '\n';
    }

    return 0;
}