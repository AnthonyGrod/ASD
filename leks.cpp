#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, a, b, c, d, p = 421, q = 1000000007;
    cin >> n >> m;
    vector<long long> h(n), powers(n + 1, 1);
    char s[n];
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        powers[i + 1] = (powers[i] * p) % q;
    }

    h[n - 1] = s[n - 1] - 'a';
    for (int i = n - 2; i >= 0; i--)
        h[i] = (h[i + 1] * p + s[i] - 'a') % q;

    auto hash = [&](int i, int j) -> long long {
        long long res = (h[i] - (h[j + 1] * powers[j - i + 1]) % q + q) % q;
        return res;
    };

    auto binsearch = [&](int beg1, int end1, int beg2, int end2) -> int {
        int beg = 0;
        int length1 = end1 - beg1 + 1;
        int length2 = end2 - beg2 + 1;
        int end = min(length1, length2) - 1;
        while (beg != end) {
            int mid = (beg + end) / 2;
            if (hash(beg1, beg1 + mid) == hash(beg2, beg2 + mid)) {
                beg = mid + 1;
            } else {
                end = mid;
            }
        }
        if (end + 1 == length1 && end + 1 == length2) {
            if (s[beg1 + end] > s[beg2 + end]) {
                return -1;
            } else if (s[beg1 + end] < s[beg2 + end]) {
                return 1;
            }
            return 0;
        }
        if (end + 1 == length1) {
            if (s[beg1 + end] > s[beg2 + end]) {
                return -1;
            }
            return 1;
        }
        if (end + 1 == length2) {
            if (s[beg1 + end] < s[beg2 + end]) {
                return 1;
            }
            return -1;
        }
        if (s[beg1 + end] < s[beg2 + end]) return 1;
        return -1;
    };

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        int res = binsearch(a, b, c, d);
        if (res == -1) cout << ">\n";
        else if (res == 0) cout << "=\n";
        else cout << "<\n";
    }

    return 0;
}