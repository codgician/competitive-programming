#include <bits/stdc++.h>
using namespace std;

#define SIZE 330010
const double pi = acos(-1.0);

class Complex {
public:
    double real, imag;
    Complex operator + (const Complex & snd) & { return Complex{real + snd.real, imag + snd.imag}; };
    Complex operator - (const Complex & snd) & { return Complex{real - snd.real, imag - snd.imag}; };
    Complex operator * (const Complex & snd) & { return Complex{real * snd.real - imag * snd.imag, real * snd.imag + imag * snd.real}; };
    Complex conj() & { return Complex{real, -imag}; }
};

Complex fst[SIZE], snd[SIZE], omg[SIZE], inv[SIZE];
int pos[SIZE], fstLen, sndLen, len, lim, num;

void init() {
    len = 1, lim = 0; double cnt = 0;
    while (len < fstLen + sndLen - 1)
        len <<= 1, lim++;
    for (int i = 0; i < len; i++, cnt += pi + pi) {
        omg[i] = {cos(cnt / len), sin(cnt / len)};
        inv[i] = omg[i].conj(); pos[i] = (pos[i >> 1] >> 1) | ((i & 1) << (lim - 1)) ;
    }
}

void fft(Complex * arr, Complex * omg) {
    for (int i = 0; i < len; i++) 
        if (i < pos[i])
            swap(arr[i], arr[pos[i]]);
    for (int l = 2; l <= len; l <<= 1) {
        int midPt = l >> 1, step = len / l;
        for (Complex * p = arr; p != arr + len; p += l) {
            for (int i = 0, cnt = 0; i < midPt; i++, cnt += step) {
                Complex t = omg[cnt] * p[i + midPt];
                p[i + midPt] = p[i] - t; p[i] = p[i] + t;
            }
        }
    }
}

void multiply() {
    init(); fft(fst, omg); fft(snd, omg);
    for (int i = 0; i < len; i++)
        fst[i] = fst[i] * snd[i];
    fft(fst, inv);
}

int arr[3][SIZE], app[3][SIZE]; long long int twos[SIZE];

long long int work1(int thdId) {
    fill(fst + 0, fst + SIZE, Complex{0, 0});
    fill(snd + 0, snd + SIZE, Complex{0, 0});
    int fstId = (thdId + 1) % 3, sndId = (thdId + 2) % 3;
    fstLen = arr[fstId][num - 1] + 1, sndLen = arr[sndId][num - 1] + 1;
    for (int i = 0; i < num; i++)
        fst[arr[fstId][i]].real++, snd[arr[sndId][i]].real++;
    multiply();

    for (int i = 0; i < fstLen + sndLen - 1; i++)
        twos[i] = fst[i].real / len + 0.5;
    for (int i = 1; i < fstLen + sndLen - 1; i++)
        twos[i] += twos[i - 1];

    long long int ret = 0; int fstPt = 0, sndPt = 0;
    for (int i = 0; i < num; i++) {
        ret += twos[fstLen + sndLen - 2] - twos[arr[thdId][i] - 1];
        while (fstPt < num && arr[fstId][fstPt] <= arr[thdId][i])
            fstPt++;
        while (sndPt < num && arr[sndId][sndPt] <= arr[thdId][i])
            sndPt++;
        ret -= 1ll * (num - fstPt) * (num - sndPt);
        ret -= 1ll * fstPt * (num - sndPt) + 1ll * sndPt * (num - fstPt);
    }
    return ret;
}

long long int work2(int fstId, int sndId) {
    vector<pair<int, long long int> > vec; int thdId = 3 - fstId - sndId;
    int siz = min(arr[fstId][num - 1], arr[sndId][num - 1]);
    for (int i = 1; i <= siz; i++)
        if (app[fstId][i] > 0 && app[sndId][i] > 0)
            vec.push_back(make_pair(i, 1ll * app[fstId][i] * app[sndId][i]));
    long long int ret = 0, cnt = 0; int j = 0;
    for (const auto & p : vec) {
        for (; j < num && arr[thdId][j] <= p.first; j++)
            cnt++;
        ret += cnt * p.second;
    }
    return ret;
}

long long int work3() {
    int siz = min({arr[0][num - 1], arr[1][num - 1], arr[2][num - 1]});
    long long int ret = 0;
    for (int i = 1; i <= siz; i++)
        ret += 1ll * app[0][i] * app[1][i] * app[2][i];
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int caseNum; cin >> caseNum;
    for (int t = 1; t <= caseNum; t++) {
        cin >> num;
        for (int id = 0; id < 3; id++) {
            fill(app[id] + 0, app[id] + SIZE, 0);
            for (int i = 0; i < num; i++)
                cin >> arr[id][i], app[id][arr[id][i]]++;
            sort(arr[id] + 0, arr[id] + num);
        }

        if (num <= 1000) {
            // Brute force
            long long int ans = 0; 
            int siz = max({arr[0][num - 1], arr[1][num - 1], arr[2][num - 1]});
            for (int i = 1; i <= siz; i++)
                app[2][i] += app[2][i - 1];
            for (int i = 0; i < num; i++) {
                for (int j = 0; j < num; j++) {
                    int lb = max(1, abs(arr[0][i] - arr[1][j]));
                    int ub = min(siz, arr[0][i] + arr[1][j]);
                    ans += app[2][ub] - app[2][lb - 1];
                }
            }
            cout << "Case #" << t << ": " << ans << '\n';
            continue;
        }

        long long int ans = work1(0) + work1(1) + work1(2);
        ans -= work2(0, 1) + work2(0, 2) + work2(1, 2);
        ans += work3();

        cout << "Case #" << t << ": " << ans << '\n';
    }

    return 0;
}