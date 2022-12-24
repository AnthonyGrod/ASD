#include <iostream>
using namespace std;

int main() {
    int MODULO = 1e9;
    int n;
    cin >> n;
    int L[n][n], R[n][n];
    int s[n];

    for (int i = 0; i < n; i++) {
        cin >> s[i];
        L[i][i] = 1;
        R[i][i] = 1;
    }
    for (int j = 0; j < n - 1; j++) {
        L[j][j + 1] = (s[j] < s[j + 1]);
        R[j][j + 1] = (s[j] < s[j + 1]);
    }

    int first_dim = 0;
    int second_dim = 0;
    int k = 2;
    for (int i = 0; i < n; i++) {
        first_dim = 0;
        second_dim = k;
        for (int j = 0; j < n && first_dim < n && second_dim < n; j++) {
            if (first_dim - second_dim <= 2) {
                L[first_dim][second_dim] = (L[first_dim + 1][second_dim] * (s[first_dim] < s[first_dim + 1]) + R[first_dim + 1][second_dim] * (s[first_dim] < s[second_dim])) % MODULO;
                R[first_dim][second_dim] = (L[first_dim][second_dim - 1] * (s[second_dim] > s[first_dim]) + R[first_dim][second_dim - 1] * (s[second_dim] > s[second_dim - 1])) % MODULO;
            }
            first_dim++;
            second_dim++;
        }
        k++;
    }
    int add = 0;
    if (n == 1) {
        add = 1;
    }
    cout << ((n > 1) * (L[0][n - 1] + R[0][n - 1])) % MODULO + add << endl;
}